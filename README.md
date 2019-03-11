# mazeGeneration
c++ program that generates mazes and exports them as an image

This program defines a maze but looking at each walkable space as a node. 
Each node holds whether you can traverse to the adjacent spaces. 
Changing the nodes effects where the walls will be drawn.

The image of the maze is drawn in the ppm format, which is consists of a list of every pixel and some formatting. 
In the github viewer this image will just be the text data that makes it up, however it renders as an image in photo viewers.
This format was chosen because it could be made in raw c++ without using a library.

The current executable will create a maze.ppm with a random maze generated each time you run it.
You can also give it arguments to rename the maze, and to make multiple at once.

Possible future feature:
Size of maze changed from const to variable, and can be given as input
