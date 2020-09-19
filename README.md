# BattleTanksGame
Remake of a 2D retro Battle City game made with OpenGL

# How to build  
### CMake as most universal way

    mkdir build && cd build
    cmake ../
    
### Crosscompiling using mingw:

    mkdir build-mingw && cd build-mingw
    TOOLCHAIN_PREFIX=i686-w64-mingw32 # check up the actual mingw prefix of your mingw installation
    cmake ../ -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_C_COMPILER="$TOOLCHAIN_PREFIX-gcc" -DCMAKE_CXX_COMPILER="$TOOLCHAIN_PREFIX-g++"

You may enable or disable some build options by `-Dkey=value`.

### How to compile
### Simple
    cmake --build .

### Debug or Release(Windows)
    cmake --build . --config Debug|Release
