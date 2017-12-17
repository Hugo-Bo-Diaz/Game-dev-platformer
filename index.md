<br><img src="https://github.com/Hugo-Bo-Diaz/Game-dev-platformer/blob/master/platformer/Game/gui/title.png?raw=true" width = "338" height = "163" alt="Error loading img"><br>
## by Hugo Bó and Albert Mas
Platformer game assignment for the video game development subject (CITM-UPC).

*Where Is My Plane?* is a platformer game which shows the adventures of a lost pilot, who will have to go through several maps where he will encounter deadly traps and enemies who will try to take him out before he escapes with his red biplane.

In this game you will have to show your jumping and precission skills to jump on tricky platforms surrounded by lava and avoid getting killed by deadly enemies.

You can watch a video of the game here:

(video)

## Team Members
<br><img src="https://github.com/Hugo-Bo-Diaz/Game-dev-platformer/blob/master/platformer/Game/GroupPhoto.jpg?raw=true" width = "330" height = "226" alt="Error loading img"><br>

+ **Hugo Bó**(Left)

(individual work explanation)

Github: https://github.com/Hugo-Bo-Diaz

+ **Albert Mas**(Right)

(individual work explanation)

Github: https://github.com/albertmas

## Explanation of the core subsystems and innovations

**UI**

The UI subsystem works with a class named UIelement, which derives into other subclasses such as buttons, text, images, textboxes, etc… these UIelements are controlled by the module responsible for the UI, as they are all in a list that this module takes care of, calling the updates, the mouse events and other important functions.

**Physics**

This subsystem manages structures called objects, which hold a tiny portion of the variables needed for a simulation but they are enough for a platformer, these elements’ positions are updated every frame with their normalization corresponding to the FPS. Entities that have properties of a physical object have one of these attached to them which makes them follow the physical laws of the world.

**Entities**

This subsystem, while similar to the UI one (both have a list with all the elements and update/draw them) is for another use and has a lot of different properties such as having more interactions with the physics and collision modules to make sure the player doesn’t fall off the world. These entities are all the elements in the game that are not inanimated objects and are usually interactive such as enemies, coins, the player...

**Innovations**

As an innovation we have implemented ramps in our project, which make a collider appear under your character, that will go higher or lower depending on your position of the ramp so that when you move forward the ramp will lift you, and if you go backwards the ramp will go down with you.

We have also implemented a highscore system that will save the best runs you have made in an xml, so that you can see your highest scores even after restarting the aplication.

## Controls
+ *D* = Move forwards
+ *A* = Move backwards
+ *W* = Jump
+ *Space*  = Hover. Press it rapidly to maximize its effect.

## Debug features
+ *F1* = Return to main menu
+ *F2* = Restart actual level
+ *F5* = Save game
+ *F6* = Load game
+ *F8* = Debug UI
+ *F9* = Visible colliders and pathfinding
+ *F10* = Godmode. Invincible and able to fly pressing *Space* repeatedly
+ *F11* = Enable/Disable 30 FPS cap

## Download the latest version of *Where Is My Plane?* [here](https://github.com/Hugo-Bo-Diaz/Game-dev-platformer/releases/tag/v1.2.1)!
## Chech out our Github repository [here](https://github.com/Hugo-Bo-Diaz/Game-dev-platformer)!

## License
MIT License

Copyright (c) 2017 Hugo Bó, Albert Mas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
