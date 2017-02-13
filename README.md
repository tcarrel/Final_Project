
#Untitled 3D Graphics Engine 

A 3D graphics engine that can be used as a component of a larger game engine.
Primary features/goals:
* Be operating system agnostic.
* Use the most modern variant of OpenGL available today. (OpenGL 4.5)  If time
permits and everthing else is working, I will add in compatability for earlier
versions of the <abbr title="Application Program Interface">API</abbr>, and, by
extension, older hardware.

##Additional Goals

If time permits, these additional feature will be added.
* Provide basic scripting system through either Lua or a custom byte-code based
language.
* Add collision detection and response.
* Change to or add a Vulkan®-based rendering system.
* Add support for multithreading.
* Create a simple demo "game".

##Technologies, Libraries, and Languages Used
* [C](http://en.cppreference.com/w/c/)/[C++](http://en.cppreference.com/w/cpp/),
primarily C with some C++.
* [OpenGL 4.5](https://www.opengl.org/about/), Open Graphics Library, for rendering.
* [SDL2](https://www.libsdl.org/index.php), Simple Direct Media Layer 2, for
operating system agnostic windowing system and controls.
* [SFML](https://www.sfml-dev.org/), Simple and Fast Multimedia Library, for
2D image file manipulation.
* [GLEW](http://glew.sourceforge.net/), OpenGL Extension Wrangler.
* [GLM](http://glm.g-truc.net/0.9.4/) OpenGL Mathematics, library.
* git and [github](https://github.com/) Version control and backup.
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) Documentation.  View
program documentation
[here](http://www.ecst.csuchico.edu/~tcarrel/Senior_Project/html/index.html).

##Additional Technologies
If time provide, these additional libraries may be used for additional goals
listed above.
* [OpenMP](http://www.openmp.org/) Multithreading.
* [Lua](https://www.lua.org/) A scripting language.
* [Vulkan®](https://www.khronos.org/vulkan/)
