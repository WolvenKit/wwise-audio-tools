# Wwise Audio Tools  
This repository is for a static and dynamic library as well as a simple command line tool used to convert Wwise WEM files to OGG files instead.

## About  
Both `ww2ogg` and `revorb` are relatively old and annoying to use repetitively so this project is aimed to keep supporting them and making them easy to use and integrate.

## Building
This is meant to be build with CMake, which generates both a static and dynamic library, as well as a simple POC command line tool.  

Example build workflow:
```
git clone https://github.com/WolvenKit/wwise-audio-tools
cmake -S . -B build
cd build
make
```  
This will create the command-line tool in the `bin/` directory and the libraries in `lib/`.

## Usage
The command-line tool can be run with `./wwise-audio-converter [NAME].wem` which will generate an easily usable `[NAME].ogg` in the same directory. No need to use `revorb`, no need to have a `packed_codebooks.bin`. The library usage will have further documentation soon.

## Credits
Credit for the `ww2ogg` code goes to [`@hcs64`](https://github.com/hcs64), and [`Jiri Hruska`](https://hydrogenaud.io/index.php/topic,64328.0.html)
