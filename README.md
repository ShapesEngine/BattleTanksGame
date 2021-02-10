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

# Editing game
### Editing or adding map
1. Go to [resources.json](https://github.com/yernar/BattleTanksGame/blob/b8690431d58d44e3942207643deb439318d47ba0/res/resources.json#L806)

2. Edit `levels/description` or add another `description` using the table:
![image](https://user-images.githubusercontent.com/46201281/107474973-9348ee80-6b9d-11eb-84fe-ada6f18e241b.png)
