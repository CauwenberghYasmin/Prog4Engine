# Custom C++ engine
A custom component-based C++20 game engine built from the ground up, featuring a playable arcade prototype of BurgerTime to test its architecture.


## Overview
The main objective of this project was to design and implement a flexible, decoupled game engine rather than just scripting a standalone game. The starting point was Minigin—a minimal base setup providing SDL3 and GLM integration. Every core system beyond that (GameObject/Component hierarchy, scene management, input actions, collision handling, and threaded audio) was designed and implemented from scratch.
Because the engine was the main focus, BurgerTime was developed as a prototype to test and validate the engine's capabilities in a real gameplay environment. Applying concepts from Game Programming Patterns and the C++ Core Guidelines made writing the gameplay logic significantly cleaner, proving the extensibility of the underlying architecture.

### Tech Stack
Language: C++20
Libraries: SDL3, GLM
Build System: CMake
CI/CD: GitHub Actions (Automated builds + Emscripten WebGL deployment)

## Engine Architecture & Key Patterns
The engine prioritizes composition over inheritance and relies heavily on established design patterns to keep systems decoupled and efficient.

System	Category	Architecture & Implementation
GameObjects & Components	Core Model	GameObjects hold any number of unique components. Component composition allows functionality to be attached dynamically without bloated class hierarchies.
Scene Graph & Transforms	Core Model	GameObjects can be parented, automatically linking transform hierarchies. Position updates use the Dirty Flag Pattern—world position is only recalculated when a parent/local position changes and the position is actively requested.
Collision System	Physics & Triggers	Replaced traditional grid-based arcade movement with a custom CollisionComponent featuring OnEnter, OnStay, and OnExit callback hooks.
Input Actions & Bindings	Input System	Decouples raw hardware polling from gameplay code via action bindings (supporting Pressed, Just Pressed, Released, etc.). Uses the PImpl Idiom internally to hide implementation details and keep headers clean.
Service Locator	Systems	A static registry providing global access to engine services like the audio system or a pre-seeded random number generator.
Threaded Sound System	Audio	Audio loading and playback run on a dedicated background thread using a concurrent sound queue, ensuring sound effects never stall the main game loop.
Hashed Events & Observers	Events	Events use lightweight SDBM hashed string IDs ("event"_h) passed to subscribers via the Observer Pattern for near-zero-cost event notifications.
Object Pool	Memory Management	Used to manage enemy lifecycle allocations/deallocations continuously during gameplay without hitting heap allocation overhead.

 
## BurgerTime Prototype Details
Building the game prototype exposed where the engine excelled and helped refine how systems interacted under gameplay conditions:

Strategy Pattern (InputProvider): Entities (players and enemies) read movement/action states through an abstract InputProvider rather than polling hardware directly.

A PlayerController polls keyboard/gamepad actions.

An EnemyAiController runs decision logic in the background and reports through the exact same interface.

Enemies use providers where attack actions always return false, while players use providers where stun states are disabled. This allowed one unified entity/state setup to drive player characters, AI enemies, and player-controlled enemies in PvP mode simply by swapping the attached provider.

State Pattern: Player and enemy behaviors (walking, climbing, dying, getting stunned) are split into discrete state objects derived from a shared base state. This completely eliminated giant conditional branches and kept state transitions self-contained.

Arcade High Score Persistence: Features a classic arcade initials entry system (cycling letters with Up/Down and confirming with Left/Right). Scores persist across sessions using a lightweight CSV parser.

## Lessons Learned & What I'm Proud Of
More than any individual feature, I’m proudest of the overall code quality and architectural flexibility. Writing this engine forced me to constantly think beyond immediate functionality: How can this system be extended without breaking existing code?

The combination of the scene loader pipeline, the dirty-flag transform tree, and the Strategy-driven entity controllers proved that investing time in thoughtful software design pays off directly when building actual game logic.

Where would you like to go from here?

Add CMake build and setup instructions

Add controls and game instructions

 
 # Minigin

Minigin is a very small project using [SDL3](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.
As a student this was used to recreate our own engine, using programming patterns from Bob Nystrom.

