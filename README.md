# Custom C++ engine

This project combines a custom C++ engine built from scratch on top of Minigin with a prototype of the burger time game. The goal is to use reusable engine architecture.
The engine is component-based and applies patterns including Game Loop, Update Method, Commander, Observer, Component, State, Singleton, Object Pooling and Service Locator. It also includes external level data and a threaded sound system.


 
 # Minigin

Minigin is a very small project using [SDL3](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.
As a student this was used to recreate our own engine, using programming patterns from Bob Nystrom.

