## floodit-allegro

Simple flood it using pure C and allegro library

## Why?

Actually, this was an assignment on my BIT degree, but it was much simpler. As I had already worked with allegro before (though not with pure C, only C++), I decided to go beyond. Hopefully, I'll finish it before the day I have to turn it in. Hopefully.

## Installation

Well, I don't reeeally expect anyone to actually care about this, but if for some weird reason you do, so far I think the only thing you have to do is install allegro.

I used cmake but I'll organize it later. If your distro (or windows) don't use /usr/include for include files and /usr/lib for libraries, you'll have to change the dirs on CMakeFiles.txt. 

Hopefully I'll get the chance to do those things right before the end of the project.

PS: I recommend an out-of-tree build, and/or something like `mkdir build && cd build && cmake ..`

## License

Licensed under MIT License.


## Timeline

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
