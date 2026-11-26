#ifndef WWISE_AUDIO_TOOLS_EXPORT_H
#define WWISE_AUDIO_TOOLS_EXPORT_H

#if defined(_WIN32) && defined(WWTOOLS_LIBRARY)
#   define WWTOOLS_EXPORT __declspec(dllexport)
#else
#   define WWTOOLS_EXPORT
#endif

#endif //WWISE_AUDIO_TOOLS_EXPORT_H