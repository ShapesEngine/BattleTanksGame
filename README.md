# [BattleTanksGame](https://yernar.github.io/BattleTanksGame/)
<img src="https://user-images.githubusercontent.com/46201281/119520746-61e6de00-bd9c-11eb-87a8-af0c3248d27d.png" />

## Summary
Remake of a 2D retro Battle Tanks game made with OpenGL

## Getting Started 

The project has a single dependency: [cmake](http://www.cmake.org/download/), which is used to generate platform-specific makefiles or project files. Start by cloning this repository, making sure to pass the `--recursive` flag to grab all the dependencies. If you forgot, then you can `git submodule update --init` instead.

```bash
git clone --recursive https://github.com/yernar/BattleTanksGame
cd BattleTanksGame
mkdir Build && cd Build
```

If you are using <strong>Ubuntu</strong> you may need to do:
```bash
sudo apt-get install xorg-dev libglu1-mesa-dev
```

Now generate a project file or makefile for your platform. If you want to use a particular IDE, make sure it is installed.

```bash
# UNIX Makefile
cmake ..

# Mac OSX
cmake -G "Xcode" ..

# Microsoft Windows
cmake -G "Visual Studio 16" ..
cmake -G "Visual Studio 16 Win64" ..
...
```

## Libraries used
Functionality           | Library
----------------------- | ------------------------------------------
OpenGL Function Loader  | [glad](https://github.com/Dav1dde/glad)
Windowing and Input     | [glfw](https://github.com/glfw/glfw)
OpenGL Mathematics      | [glm](https://github.com/g-truc/glm)
Texture Loading         | [stb](https://github.com/nothings/stb)
RapidJSON               | [rapidjson](https://github.com/Tencent/rapidjson)

## Editing game
### Editing or adding map
1. Go to [resources.json](https://github.com/yernar/BattleTanksGame/blob/b8690431d58d44e3942207643deb439318d47ba0/res/resources.json#L806)

2. Edit `levels/description` or add another `description` using the table:
![image](https://user-images.githubusercontent.com/46201281/107474973-9348ee80-6b9d-11eb-84fe-ada6f18e241b.png)
