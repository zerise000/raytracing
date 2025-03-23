# Simple Raytracing algorithm

![image displayed in the program](./window.png)

This is a simple raytracing implementation made just to understand how 
graphics rendering works. In order to make the program as simple as possible
I've decided to use a single red sphere, however it is possible to render
multiple spheres at the same time, but it should require some adjustments
about camera

## resources

Mainly two:
- [raytracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html): first resource 
  I've encountered during the writing, I tried to keep the overall structure of the project but reducing 
  the amount of OOP required. It's been useful especially for anti-aliasing

- [computer graphics from scratch](https://www.gabrielgambetta.com/computer-graphics-from-scratch/): illustrated
  concepts of viewport convertion, canvas and diffuse lights, the shadows however haven't been implemented


## how the project is structured
All C++ source files are stored in `src` folder. The two main files are:
- *definitions*: contains the main entities involved in the raytracing process,
  like lights and spheres. Generally I've used tuples and structs when there
  was no need of information hiding, except for lights.

- *raytracing*: where the main rendering process happens, the program simply
  check if the ray hits an object then render the intersection point, otherwise
  simply shows the background. Here you can also find the main method for 
  antialiasing, however unlike `raytracing in one weekend` the subpixels
  aren't picked randomly

## how to compile

You need to install [https://wiki.libsdl.org/SDL2/Installation](SDL2) as a dependency, then exec
the command 'make' in order to get the final executable
