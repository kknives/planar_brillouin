# Planar Brillouin
A simple program to draw Brillouin zones of planar lattice.
Currently, only draws them for pre-defined lattice with basis (1,0) and (0,1), but
the approach is general enough to be applied to any lattice with some kind of planar
symmetry.

## Usage
```
pb zone 4 --scale=20 --size=120 -o zones.png
```
The above example draws 4 Brillouin zones, then scales them by a factor of 20,
and writes them to zones.png as a 120x120 image.

The more complete message:
```
  Usage:
    pb zone <zones> [--scale=<sf>] [--size=<sz>] [-o FILE]

  Options:
    -h --help       Show this screen
    --version       Show the version
    --scale=<sf>    Scale the image by this factor [default: 30]
    --size=<sz>     The output image is a square sz by sz [default: 240]
    -o FILE         Specify output image file [default: ./zones.png]
    
```

## Building
This project uses Meson and its Wrap dependency system.

- [ You can follow this guide to install Meson ]( https://mesonbuild.com/SimpleStart.html )
- After you have done that, clone this repo or download and extract the source.
- Then,
```
meson build
meson compile -C build
```
This compiles and produces the binary in the build folder
