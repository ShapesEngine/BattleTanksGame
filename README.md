# BattleTanksGame
Remake of a 2D retro Battle Tanks game made with OpenGL

# How to build  

1. Make sure to install [CMake](https://cmake.org/download/)<br>
1.1*. If you are using ***Ubuntu*** run:
```powershell
sudo apt-get install xorg-dev libglu1-mesa-dev
```

### CMake as most universal way

    mkdir build && cd build
    cmake ../

### How to compile
    cmake --build .

### Crosscompiling using mingw:

    mkdir build-mingw && cd build-mingw
    TOOLCHAIN_PREFIX=i686-w64-mingw32 # check up the actual mingw prefix of your mingw installation
    cmake ../ -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER="$TOOLCHAIN_PREFIX-gcc" -DCMAKE_CXX_COMPILER="$TOOLCHAIN_PREFIX-g++"

You may enable or disable some build options by `-Dkey=value`.

