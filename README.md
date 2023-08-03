# cub3D

## Table of Contents
- [Introduction](#introduction)
- [Installation and Run](#installation)
- [Controls](#controls)
- [Map](#map)
- [Animations](#animations)
- [Raycasting](#raycasting)
- [Screenshots](#screenshots)

## Introduction
This project is inspired by the very first FPS game Wolfenstein 3D. The goal is to create a 3D view by reading a 2D map.

The only graphical library we were allowed to use was miniLibX. This library is a very simple library mainly created to use in the school's projects and it's functionalities are limited to creating windows, handling input and drawing pixels in the window. The rest of the project is coded from scratch. We had to create our own functions to handle the textures/animations, the raycasting, the collisions, the movement, the rotation, the minimap, the HUD, the shadows, the colors, the floor and the ceiling, the error handling, etc.

It was by far the most joy that both of us had in a project. It's fun when you can see the results of your work in real time and it's even more fun when you can play it.

## Installation and Run
1. Clone the repository
```bash
git clone
```
2. Compile the project
```bash
make
```
3. Run the executable
```bash
./cub3D map.cub
```
or ( This way it will open a menu that we created to choose the map and whether or not you want to play with the mouse. )
```bash
./cub3D
```

If the game is a bit laggy, you can change the resolution in the top of header file in the macros of WINDOWSIZE_Y and WINDOWSIZE_X.
and 
```bash
make r
```

## Controls
The game can be played with the mouse and keyboard or with solo the keyboard. 

The way we implemented the input is that we have a struct that contains all the keys that we need to play the game. When a key is pressed, the value of the key is set to 1 and when it's released, the value is set to 0. The struct is updated every time the game loop is executed.
This was the only way we could implement the movement and rotation of the player at the same time, so the player can move diagonally and look around at the same time for example.

The controls are the following:

- The ESC key: exit the game

**For solo the keyboard:**
- W: move forward
- S: move backward
- A: look to the left side
- D: look to the right side

**For the mouse + keyboard:**
- W: move forward
- S: move backward
- A: move left
- D: move right

## Map

Every wall in the map is represented by the number 1. The player is represented by the letter N, S, E or W being this the selection of the side that the player will be facing in the start of the game. The doors are represented by the letter D. The floor in which the player walks is represented by the number 0.

The map must be closed/surrounded by walls. 

There is also the path to the textures and the colors of the floor and the ceiling in the map file. We treated this part using a key-value pair struct that stored the values for each key, so in case of repetitions it would not crash.
These can be a path to anywhere in the computer and we have to parse it accordingly. We also had to take into account the fact that the map file can have empty lines and spaces at the beginning, middle and end of the file. (Only having access to our beloved libft functions)

The map must be a .cub file.

## Animations

To make every animation have it's own timer and not be affected by the FPS, we created a struct that contains the time when the animation started and the time when it should end. This way we can have multiple animations at the same time and they will not be affected by the FPS.
Also every different "block" is an object. we found out that this would be the easiest way to handle the animations, the textures, and the collisions.

## Raycasting

In this section, we had a bit of difficulty implementing a radian system to handle the angle of the ray. Sometimes the ray would not hit the wall and we were stuck on that a lot of time. 

Thus, we followed a tutorial of Lodev.org to implement the raycasting. We had to adapt it to our code and to the miniLibX library, but it was of great help. (link: https://lodev.org/cgtutor/raycasting.html)

## Screenshots

Menu:

![Menu](https://github.com/dadoming/cub3D/blob/master/doc_images/Menu.png)

This menu uses a Circular Linked-List for map selection and a boolean for mouse selection.


Game:

![Game](https://github.com/dadoming/cub3D/blob/master/doc_images/show_game.mp4)

This is a video of the game. It shows the movement, the rotation, the minimap, the HUD, the colors of the floor and the ceiling and the animations.
