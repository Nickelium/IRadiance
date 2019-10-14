# IRadiance - RayTracer

IRadiance Engine is an open-source software raytraced renderer written in C++11.

This project is still in development, therefore the codebase tends to fluctuate a lot.

<p float="left">                                                   
    <img width="70%" src="https://raw.githubusercontent.com/Nickelium/IRadiance/master/Sandbox/output/HiRes5000SPP_NoBorder.jpg">
</p> 

## Features
* Whitted Raytracer
* Unidirectional Pathtracing
* Soft Shadows
* Area Lights
* Environment Light
* Visualize Render Progress
* Save Render to File
* MultiCore Rendering

## Dependencies
* GLFW : Window Creattion and Context 
* GLAD : OpenGL Function Binding
* glm : Math library
* ImGui : Immediate mode UI
* spdlog : Logging
* stbi_image : Textures loading
* assimp : Asset Loader
* OpenMP : MultiCore Processing

## Render Samples         
 
## References
* [Radiance Engine](https://github.com/Nickelium/Radiance)
* [RTFGU, Kevin Suffern](http://www.raytracegroundup.com/)
* [PBRT, Matt Pharr and Wenzel Jakob](http://www.pbr-book.org/)
* [Robust Monte Carlo Methods for Light Transport Simulation, Veach](http://graphics.stanford.edu/papers/veach_thesis/)