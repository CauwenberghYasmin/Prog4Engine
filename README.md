# Minigin

Minigin is a very small project using [SDL3](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.

As a student this was used to recreate our own engine, using programming patterns from Bob Nystrom.

In the current version you can find back a recreation of the game 'Burger Time' in which a little chef runs around to make burgers stack while avoiding enemies such as hotdogMan, mister egg and pickle.
This version rather takes a creative approach in which the player needs to gather all the pickup items (fries and icecream) to be able to go to the next level.
Not only that, this version let's you play solo, Vs and co-op!


My proudest work in this project is de collision component, which takes inspiration from unity. This component takes in function and exectues them at a designed time(on enter, on exit and onStay).
It also holds a feature of setting your own collision block, tags and let's you debug draw. there is a differentiation between static and dynamic object for performance.

I congratualate you if you've read thsi far. This project will see lot's of improvement though the summer!


