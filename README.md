# Custom C++ engine
A custom component-based C++20 game engine built from the ground up, featuring a playable arcade prototype of BurgerTime to test its architecture.


## Overview
The main objective of this project was to design and implement a flexible, decoupled game engine rather than just scripting a standalone game. The starting point was Minigin, a minimal base setup providing SDL3 and GLM integration. Every core system beyond that (GameObject/Component hierarchy, scene management, input actions, collision handling, and threaded audio) was designed and implemented from scratch.
Because the engine was the main focus, BurgerTime was developed as a prototype to test the engine in a real gameplay environment and is not fully polished. 
In this project we applied concepts from Game Programming Patterns and the C++ Core Guidelines for cleaner and better code.

### Tech Stack
Language: C++20

Libraries: SDL3, GLM

Build System: CMake

CI/CD: GitHub Actions (Automated builds + Emscripten WebGL deployment)


## Engine Architecture 
The engine uses composition more than inheritance to keep systems decoupled and efficient.
Any game object has as many components that you assign it. Game objects itself also has hierarchies, so you can parents objects to each other. This system takes a reference to unity. 
When parenting objects you can decide if you want to link their positions aswel, which would later be updated using the dirty flag pattern (the position is only recalculated when a parent/local position changes and the position is actively requested).

Instead of using a grid system, I've decided to go forward with a collision component which has OnEnter, OnStay, and OnExit functions.
The file reader class will create the map, and automatically assign them the collision components and a tag.

Input actions & bindings	input system	decouples raw hardware polling from gameplay code via action bindings ( Pressed, Just Pressed, Released, etc.). Uses the Pimpl Idiom internally to hide implementation details and keep headers clean.
Service Locator	Systems	are used to provide global access to the audio system.
Threaded sound system	audio loading and playback run on a dedicated background thread using a concurrent sound queue, ensuring sound effects never stall the main game loop.
Observers and even queues are used to notify certain game objects of events while decoupling everything neatly.
Object pooling	is used to manage enemy lifecycle allocations/deallocations and for optimization.

 
 # Minigin

Minigin is a very small project using [SDL3](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.
As a student this was used to recreate our own engine, using programming patterns from Bob Nystrom.

