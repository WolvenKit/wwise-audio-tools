/*
 * REVORB - Recomputes page granule positions in Ogg Vorbis files.
 *   version 0.2 (2008/06/29)
 *
 * Copyright (c) 2008, Jiri Hruska <jiri.hruska@fud.cz>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*# INCLUDE=.\include #*/
/*# LIB=.\lib         #*/
/*# CFLAGS=/D_UNICODE #*/
/*# LFLAGS=/NODEFAULTLIB:MSVCRT /LTCG /OPT:REF /MANIFEST:NO #*/

#include <cstdio>
#include <cstring>
#include <cwchar>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <ogg/ogg.h>
#include <vorbis/codec.h>

bool g_failed;

bool copy_headers(std::stringstream &fi, ogg_sync_state *si,
                  ogg_stream_state *is, std::stringstream &outdata,
                  ogg_sync_state *so, ogg_stream_state *os, vorbis_info *vi) {
  char *buffer = ogg_sync_buffer(si, 4096);

  fi.read(buffer, 4096);
  auto numread = fi.gcount();

  ogg_sync_wrote(si, numread);

  ogg_page page;
  int result = ogg_sync_pageout(si, &page);
  if (result != 1) {
    return false;
  }

  ogg_stream_init(is, ogg_page_serialno(&page));
  ogg_stream_init(os, ogg_page_serialno(&page));

  if (ogg_stream_pagein(is, &page) < 0) {
    ogg_stream_clear(is);
    ogg_stream_clear(os);
    return false;
  }

  ogg_packet packet;
  if (ogg_stream_packetout(is, &packet) != 1) {
    ogg_stream_clear(is);
    ogg_stream_clear(os);
    return false;
  }

  vorbis_comment vc;
  vorbis_comment_init(&vc);
  if (vorbis_synthesis_headerin(vi, &vc, &packet) < 0) {
    vorbis_comment_clear(&vc);
    ogg_stream_clear(is);
    ogg_stream_clear(os);
    return false;
  }

  ogg_stream_packetin(os, &packet);

  int i = 0;
  while (i < 2) {
    int res = ogg_sync_pageout(si, &page);

    if (res == 0) {
      buffer = ogg_sync_buffer(si, 4096);
      fi.read(buffer, 4096);
      numread = fi.gcount();
      if (numread == 0 && i < 2) {
        ogg_stream_clear(is);
        ogg_stream_clear(os);
        return false;
      }
      ogg_sync_wrote(si, 4096);
      continue;
    }

    if (res == 1) {
      ogg_stream_pagein(is, &page);
      while (i < 2) {
        res = ogg_stream_packetout(is, &packet);
        if (res == 0)
          break;
        if (res < 0) {
          vorbis_comment_clear(&vc);
          ogg_stream_clear(is);
          ogg_stream_clear(os);
          return false;
        }
        vorbis_synthesis_headerin(vi, &vc, &packet);
        ogg_stream_packetin(os, &packet);
        i++;
      }
    }
  }

  vorbis_comment_clear(&vc);

  while (ogg_stream_flush(os, &page)) {
    outdata.write(reinterpret_cast<char *>(page.header), page.header_len);
    outdata.write(reinterpret_cast<char *>(page.body), page.body_len);
  }

  return true;
}

// Returns true if successful and false if not successful
bool revorb(std::istream &indata, std::stringstream &outdata) {
  std::stringstream indata_ss;
  indata_ss << indata.rdbuf();

  ogg_sync_state sync_in, sync_out;
  ogg_sync_init(&sync_in);
  ogg_sync_init(&sync_out);

  ogg_stream_state stream_in, stream_out;
  vorbis_info vi;
  vorbis_info_init(&vi);

  ogg_packet packet;
  ogg_page page;

  if (copy_headers(indata_ss, &sync_in, &stream_in, outdata, &sync_out,
                   &stream_out, &vi)) {
    ogg_int64_t granpos = 0, packetnum = 0;
    int lastbs = 0;

    while (true) {
      int eos = 0;
      while (!eos) {
        int res = ogg_sync_pageout(&sync_in, &page);
        if (res == 0) {
          char *buffer = ogg_sync_buffer(&sync_in, 4096);
          indata_ss.read(buffer, 4096);
          auto numread = indata_ss.gcount();
          if (numread > 0)
            ogg_sync_wrote(&sync_in, numread);
          else
            eos = 2;
          continue;
        }

        if (res < 0) {
          g_failed = true;
        } else {
          if (ogg_page_eos(&page))
            eos = 1;
          ogg_stream_pagein(&stream_in, &page);

          while (true) {
            res = ogg_stream_packetout(&stream_in, &packet);
            if (res == 0)
              break;
            if (res < 0) {
              g_failed = true;
              continue;
            }

            int bs = vorbis_packet_blocksize(&vi, &packet);
            if (lastbs)
              granpos += (lastbs + bs) / 4;
            lastbs = bs;

            packet.granulepos = granpos;
            packet.packetno = packetnum++;
            if (!packet.e_o_s) {
              ogg_stream_packetin(&stream_out, &packet);

              ogg_page opage;
              while (ogg_stream_pageout(&stream_out, &opage)) {
                outdata.write(reinterpret_cast<char *>(opage.header),
                              opage.header_len);
                outdata.write(reinterpret_cast<char *>(opage.body),
                              opage.body_len);
              }
            }
          }
        }
      }

      if (eos == 2)
        break;

      {
        packet.e_o_s = 1;
        ogg_stream_packetin(&stream_out, &packet);
        ogg_page opage;
        while (ogg_stream_flush(&stream_out, &opage)) {
          outdata.write(reinterpret_cast<char *>(opage.header),
                        opage.header_len);
          outdata.write(reinterpret_cast<char *>(opage.body), opage.body_len);
        }
        ogg_stream_clear(&stream_in);
        break;
      }
    }

    ogg_stream_clear(&stream_out);
  } else {
    g_failed = true;
  }

  vorbis_info_clear(&vi);

  ogg_sync_clear(&sync_in);
  ogg_sync_clear(&sync_out);

  return !g_failed;
}
