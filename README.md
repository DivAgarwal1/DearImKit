# DearImKit
DearImKit is a C++ GUI library designed to simplify writing [Dear ImGui](https://github.com/ocornut/imgui) applications by handling the rendering, ImGui window management, and OS window management, allowing developers to easily write GUIs with ImGui graphics logic.

DearImKit uses Dear ImGui with [GLFW](https://github.com/glfw/glfw) and [OpenGL3](https://www.opengl.org/) backend as well [GLAD](https://github.com/Dav1dde/glad) to manage OpenGL functions. Dependencies are already included. You only need to include DearImKit in your applications.

## Installation and Linking
Include this project in one of the following ways. Visit https://cmake.org/ for help with CMake.
- [Using Git Submodules + CMake (Recommended)](#using-git-submodules--cmake-recommended)
- [Using Source + CMake](#using-source--cmake)
- [Using Prebuilt Binaries (Not Recommended)](#using-prebuilt-binaries-not-recommended)

### Using Git Submodules + CMake (Recommended)
First [create a repository](https://docs.github.com/en/migrations/importing-source-code/using-the-command-line-to-import-source-code/adding-locally-hosted-code-to-github#initializing-a-git-repository) for your code.
Then run the following commands in your terminal to include DearImKit as a submodule.
```
git submodule add --name <NAME> https://github.com/DivAgarwal1/DearImKit <PATH>
git submodule update --init --recursive
```
For example:
```
git submodule add --name DearImKit https://github.com/DivAgarwal1/DearImKit extern/dearimkit
git submodule update --init --recursive
```
This creates an extern folder at your project root and clones DearImKit into it. You should also have a .gitmodules file with the submodule configuration. You may choose any name or path you wish but it's common practice to have a designated folder with submodules.

In your CMakeLists.txt, include the following.
```
add_subdirectory(<PATH>)
```
In the case of my example:
```
add_subdirectory(extern/dearimkit)
```
You will now have access to the `dearimkit` target which you can link against your targets using
```
target_link_libraries(<TARGET> <PRIVATE|PUBLIC|INTERFACE> dearimkit) 
```
If you wish to build DearImKit as a shared library, add `set(DEARIMKIT_BUILD_SHARED ON)` before adding the sub_directory. If you add `set(DEARIMKIT_INSTALL_LOCATION <PATH>)`, running install with CMake will add the `libdearimkit` shared object to `<PATH>` relative to your CMake install prefix. Make sure to include this in the RPATH of your target.

Move on to [Getting Started](#getting-started).

### Using Source + CMake 
First clone the repository (or download and move the code) into your project.
For example:
```
git clone https://github.com/DivAgarwal1/DearImKit lib/dearimkit
```
Next move into the directory you just cloned into (`cd lib/dearimkit` in my example) and run the following.
```
git submodule update --init --recursive
```

In your CMakeLists.txt, include the following.
```
add_subdirectory(<PATH>)
```
In the case of my example:
```
add_subdirectory(lib/dearimkit)
```
You will now have access to the `dearimkit` target which you can link against your targets using
```
target_link_libraries(<TARGET> <PRIVATE|PUBLIC|INTERFACE> dearimkit) 
```
If you wish to build DearImKit as a shared library, add `set(DEARIMKIT_BUILD_SHARED ON)` before adding the sub_directory. If you add `set(DEARIMKIT_INSTALL_LOCATION <PATH>)`, running install with CMake will add the `libdearimkit` shared object to `<PATH>` relative to your CMake install prefix. Make sure to include this in the RPATH of your target.

Move on to [Getting Started](#getting-started).

### Using Prebuilt Binaries (Not Recommended)
Coming Soon!

## Getting Started
**At the top of your files, make sure to add `#include "DearImKit/dearimkit.h"`.**

The most useful guide to using DearImKit will likely be the [examples](examples/). In particular, the [Hello World](examples/hello_world.cpp) example is a good guide to starting a DearImKit application. Direct documentation for the API can be found in the project header files.

### Launching the Application
Launch application by running `DearImKit::SetupApp(...)` once when you want to create the application (usually in `main()`). The first parameter to this function is a `std::function` that allows you to specify code to run at startup of your application, after setup and before the application loop. Use this to add windows at startup like home windows or menu bars. Check out the [Hello World](examples/hello_world.cpp) example.

If you wish to create multiple windows, existing windows can add new ones by calling `DearImKit::AddPanel<T>(...)`. Check out the [Multiple Windows](examples/multiple_windows.cpp) example.

### Creating a Window
We mention adding startup windows at launch, but how do we actually create a window? Each window we write will be a class extending the base `DearImKit::Panel` class. 

The derived class should call the base constructor to set the name of the window and override the `draw()` function to render content. Place ImGui drawing logic in `draw()`; you may in general use all ImGui drawing logic, except use `DearImKit::Begin(...)` instead of `ImGui::Begin(...)`. `draw()` should return `true` if the window should stay open and `false` if the window should close. Using `p_open` in `DearImKit::Begin(...)` is very useful for this task: to have windows close by a close button in the top right corner, set a variable to `true` at the start of `draw()`, pass the variable's address to `p_open`, and return the variable at the end of `draw()`.

Check out the [Hello World](examples/hello_world.cpp) example to see a guide.

### Displaying Errors
If you wish to display errors, windows can call `DearImKit::QueueError(...)` to capture user attention with an error popup. Check out the [Error Popups](examples/error_popups.cpp) example.

### Images
Coming Soon!

## Licensing
Check out The MIT License for this project [here](LICENSE).

See licensing for dependencies (Dear ImGui, GLFW, and GLAD with OpenGL3) [here](LICENSES)
