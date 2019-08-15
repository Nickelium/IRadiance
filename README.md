# IRadiance - RayTracer

IRadiance Engine is an open-source graphics engine written in C++11 and currently built on top of OpenGL 4.3. 

One of the main focus in the development process is building a clear architecture and providing a simple but also nice API to use.
The Radiance API allows the user to build their graphics application quickly, while the engine handles all the other low-level necessities. The engine strives to be as platform independent as possible.

This project is still in development, therefore the codebase tend to fluctuate a lot.

<p float="left">                                                   
    <img width="99%" src="https://raw.githubusercontent.com/Nickelium/IRadiance/master/Sandbox/output/image_6.jpg">
</p> 

## Features
* Material System
* Support Custom Shaders

## Dependencies
* GLFW : Window Creattion and Context 
* GLAD : OpenGL Function Binding
* glm : Math library
* ImGui : Immediate mode UI
* spdlog : Logging
* stbi_image : Textures loading
* assimp : Asset Loader

## Render Samples         
 
## References
* [RTFGU, Kevin Suffern](http://www.raytracegroundup.com/)
* [PBRT, Matt Pharr and Wenzel Jakob](http://www.pbr-book.org/)
* [Radiance Engine](https://github.com/Nickelium/Radiance)
