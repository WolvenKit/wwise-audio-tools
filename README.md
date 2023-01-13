# Wwise Audio Tools  
This repository is for a static and dynamic library as well as a simple command line tool used to convert Wwise WEM files to OGG files instead.

## About  
Both `ww2ogg` and `revorb` are relatively old and annoying to use repetitively so this project is aimed to keep supporting them and making them easy to use and integrate.

## Building
This is meant to be built with CMake, which generates both a static and dynamic library, as well as a simple POC command line tool.  

Example build workflow:
```
git clone https://github.com/WolvenKit/wwise-audio-tools
cmake -B build
cmake --build build
```  
> Note: This project *does* require `libogg` and `libvorbis` to build, which can be downloaded [here](https://xiph.org/downloads/) or installed from Linux package managers under names something like `libogg-dev` and `libvorbis-dev` or `libogg-devel` and `libvorbis-devel`.  

This will create the command-line tool in the `bin/` directory and the libraries in `lib/`.

## Usage
The command-line tool can be run with `./wwise-audio-converter [NAME].wem` which will generate an easily usable `[NAME].ogg` in the same directory. No need to use `revorb`, no need to have a `packed_codebooks.bin`. The library usage will have further documentation soon.

## Credits
Credit for the `ww2ogg` code goes to [`@hcs64`](https://github.com/hcs64), and to [`Jiri Hruska`](https://hydrogenaud.io/index.php/topic,64328.0.html) for the creation of the original `revorb`.

## Licensing
Many files here are licensed individually and are taken from other projects, such as [ww2ogg](https://github.com/hcs64/ww2ogg) and [revorb](https://hydrogenaud.io/index.php/topic,64328.0.html). Other than the `ww2ogg` license, everything else is licensed under MIT.
