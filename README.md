## floodit-allegro

Simple flood it using pure C and allegro library

## Why?

Actually, this was an assignment on my BIT degree, but it was much simpler. As I had already worked with allegro before (though not with pure C, only C++), I decided to go beyond. Hopefully, I'll finish it before the day I have to turn it in. Hopefully.

Update: Yeeeah, that didn't happen (which means that this is incomplete). My professor said he'd give me a perfect score anyway because I made much more than what was needed from the beginning.

Things I had intended to do if I had had the time:

 * Mouse support
 * Cool menus
 * Sound (I actually had composed a simple track for this at the time)
 * Config menu
 * Pause menu
 * Ranking


## What has been done

 * Incomplete object-orientation with structs and pointer to functions (nothing fancy)

 * Structs to represent states of the game. Each of them have a draw function that dictates how to do the drawing on the ALLEGRO_DISPLAY 
    * A Scenario is an abstraction of a game, with blocks, moves, and the game state (lost, won, running). The drawing routine do some obscure math to calculate proportionally the space for the squares (even if you resize the window) and iterate through all the blocks to draw them.
    * A Menu is an abstraction of a menu, with the options that can be selected. It has a varargs constructor that receives null-terminated string literals for the options on the menu and MUST end with a NULL after the strings to mark the end of the arguments. If the arguments are passed without NULL at the end, the behavior is undefined.

 * Some other structs to abstract more stuff. There's one for a Block, holding information about that block, its color, and a poiner to a block for every direction. There is NO matrix on the Scenario, only the first block. The matrix is formed as a linked matrix of sorts through these pointers. This was done on purpose (like a lot of the weird design decisions I made for this project) because I wanted to learn more about it. The same can be said about the color being stored in an enum. It wasn't because it was necessarily a good way, just because I wanted to do things I haven't done before.

 * There's also a struct for Display, it encapsulates an ALLEGRO_DISPLAY and has a function pointer for the current drawing routine, this way I can just call draw at the end of the loop without worrying about the states of the game, which are managed somewhere else.

Third-party code:

 * mtwist for pseudo-random number generation

 * FindAllegro5.cmake

## Installation

This depends on cmake and allegro.
Allegro version used was 5.0.8, but any version 5.x should do the trick.

If you're using Ubuntu, this should work:

```bash
   sudo apt-get install liballegro5-dev cmake
```

ArchLinux:
```bash
   sudo pacman -S allegro cmake
```

Then it's a matter of running cmake and make. I recommend an out-of-source build:

```bash
   git clone https://github.com/mateusmedeiros/floodit-allegro.git
   cd floodit-allegro 
   mkdir build
   cd build
   cmake ..
   make
   ./floodit-allegro
```

----

If you're using Windows, you'll suffer more, probably. I made a very improvised workaround for this to compile on Windows without manual intervention. You should install MinGW and then cmake, and cmake should be on PATH. 

Clone this repository somewhere, or extract from the zip file github provides.
You shall then download allegro for windows. Pre-compiled binaries can be found here https://www.allegro.cc/files/ . (Download a MinGW one, preferably the most recent).

Extract the contents of the zip or 7z on the repository folder, and rename it to "allegro".
You should now have a floodit-allegro/allegro/bin (and lib) folder.

After that, on cmd:
```
   cd floodit-allegro
   mkdir build
   cd build
   cmake -G "MinGW Makefiles" ..
   \MinGW\bin\mingw32-make.exe
```

**Update:** I recently tried this to see if I could show it quickly to a friend of mine and it didn't work, so yeah, if you're on windows you'll have to figure it out, sorry. :confused:


## License

Licensed under MIT License.


## Timeline  (This was required by the assignment)

##### November 26, 2014

Load and save game working ok (using allegro native_dialog).


##### November 7, 2014

Struct to hold global configuration and a prototype for storing it. Also a function to read it. 

Added the colors to be selected on the left side of the board, and the main menu is now navigable (though only new game can be selected for now).

![screenshot number three](/screenshots/screenshot3.png?raw=true "Updated Matrix")

##### November 1, 2014

Menu struct with varying size. If I do have the time later, I intend to implement mouse support, resizing, relative positioning and relative size and stuff like that. Since I didn't want to use something more besides allegro, I'll have to do some gymnastics with bitmaps for that, and the menu won't be super high quality, but at least it will resize with the window. For now it's absolute positioning though. Beauty come later, functionalities first.

![screenshot number two](/screenshots/screenshot2.png?raw=true "Menus")

##### October 7, 2014

Made a matrix with colors and a simple structure to add colors and some structs to encapsulate everything.

![screenshot number one](/screenshots/screenshot1.png?raw=true "Matrix")
