
#Untitled 3D Graphics Engine 

A 3D graphics engine that can be used as a component of a larger game engine.
Primary features/goals:
* Be operating system agnostic.  Will be initially programmed on Linux, but
should only require minor changes to make it compile and run on Windows.  (And,
OS-X as well, although I have no way of testing this.
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
* [SOIL](http://www.lonesock.net/soil.html) Simple OpenGL Image Library.
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

##Screenshots

Here are some screenshots of some Wavefront .obj file that have been rendered
using the program thus far.

![A Cube](/.Images/cube.png)
A cube with randomly colored verticies.

![A Torus](/.Images/torus.png)
A torus with randomly colored vertices.

![Two linked toruses.](/.Images/toruses.png)
Two intersecting toruses with randomly colored vertices.

![Normal Colored Torus](/.Images/torus_normals.png)
A torus with vertices colored according to their normal vector.

![Utah Teapot 1](/.Images/utah_teapot.2.jpg)
The Utah Teapot with randomly colored vertices.

![Utah Teapot 2](/.Images/utah_teapot.1.jpg)
The Utah Teapot with vertices colored according to their normal vector.

![Stanford Bunny](/.Images/stanford_bunny.png)
The Stanford Bunny with vertices colored according to their normal vector.

##Works cited:
* [Pyarelal Knowles](http://goanna.cs.rmit.edu.au/~pknowles/models.html): 
Watertight Utah Teapot Model
* [Christopher Batty](https://cs.uwaterloo.ca/~c2batty/): Watertight Stanford
Bunny Model
* The basics of the code for handling errors in the shader compilation process
came from the book "OpenGL 4 Shading Language Cookbook" 2nd Ed. by
[David Wolff](https://github.com/daw42/glslcookbook).
* [Custom Map Makers](http://www.custommapmakers.org/skyboxes.php) All cube maps.
