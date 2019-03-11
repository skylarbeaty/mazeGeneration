#include "maze.hpp"
#include "node.hpp"

#include <random>
#include <iostream>
#include <fstream>
#include <ctime>


maze::maze(){
    init();
}
maze::maze(bool createMaze){
    init();
    if (createMaze)
        create();
}
void maze::init(){
    for(int i = 0; i < WIDTH; ++i){
        for(int j = 0; j < HEIGHT; ++j){
            traversed[i][j] = false;
            grid[i][j].init();
            srand(time(nullptr));
        }
    }
}
void maze::create(){
    vec2 startPos(0,0);
    vec2 pos = startPos, nextMove;
    traversed[startPos.x][startPos.y] = true;
    currentPath.push(startPos);
    do{
        nextMove = randomMove(pos);
        if (nextMove == vec2(0,0)){ //nowhere to go
            pos = currentPath.top();//go back one on the stack
            currentPath.pop();
        }
        else{//go to next move
            grid[pos.x][pos.y].dirWallBreak(nextMove.x, nextMove.y);//break wall on last pos
            pos = pos + nextMove;
            grid[pos.x][pos.y].dirWallBreak(-1 * nextMove.x, -1 * nextMove.y);//break wall on new pos
            traversed[pos.x][pos.y] = true;
            currentPath.push(pos);
        }
    }while (pos != vec2(0,0));
}
vec2 maze::randomMove(vec2 pos){
    vec2 ret;
    node n;
    int countInvalid = 0;
    vec2 north(0,-1);
    vec2 east(1,0);
    vec2 south(0,1);
    vec2 west(-1,0);
    while(countInvalid < 4 && ret == vec2(0,0)){// 4 possible directions
        int r = (rand() % 4);
        switch(r){//try a random direction
        case 0:
            if (isValid(pos + north))//check if 
                ret = north;//if possible, set as return
            if(n.northWallExists())
                countInvalid++;//if hasnt been tried, count as tried
            n.northWallBreak();
            break;
        case 1:
            if (isValid(pos + east))
                ret = east;
            if(n.eastWallExists())
                countInvalid++;
            n.eastWallBreak();
            break;
        case 2:
            if (isValid(pos + south))
                ret = south;
            if(n.southWallExists())
                countInvalid++;
            n.southWallBreak();
            break;
        default:
            if (isValid(pos + west))
                ret = west;
            if(n.westWallExists())
                countInvalid++;
            n.westWallBreak();
            break;
        }
    }
    return ret;
}
bool maze::isValid(vec2 p){
    return (p.x >=0 && p.y >=0 && p.x < WIDTH && p.y < HEIGHT //in range
            && !traversed[p.x][p.y]);//not visited
}
void maze::printMaze(){//transaltes maze data into print maze
    char printPage[WIDTH * 2 - 1][HEIGHT * 2 -1]; //room for walls
    char walkSpace = ' ', empty = '+', wallVert = '|', wallHor = '-';
    //translate maze data into char data
    for(int i = 0; i < WIDTH * 2 - 1; ++i){//fill in chars for path
        for(int j = 0; j < HEIGHT * 2 - 1; ++j){
            if (i % 2 == 0 && j % 2 == 0)//both even -> walk sapce
                printPage[i][j] = walkSpace;
            if (i % 2 == 0 && j % 2 == 1){//i even, j odd -> check wall hor
                int x = i / 2;
                int y = (j + 1) / 2 - 1;
                if (grid[x][y].southWallExists())
                    printPage[i][j] = wallHor;
                else
                    printPage[i][j] = walkSpace;
            }
            if (i % 2 == 1 && j % 2 == 0){//i odd, j even -> check wall vert
                int x = (i + 1) / 2 - 1;
                int y = j / 2;
                if (grid[x][y].eastWallExists())
                    printPage[i][j] = wallVert;
                else
                    printPage[i][j] = walkSpace;
            }
            if (i % 2 == 1 && j % 2 == 1)//both even -> empty
                printPage[i][j] = empty;
        }
    }
    //output char data
    std::cout << std::endl;
    for(int j = 0; j < HEIGHT * 2 - 1; ++j){
        for(int i = 0; i < WIDTH * 2 - 1; ++i)//add to stream
            std::cout << printPage[i][j] << ' ';
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
std::ofstream& maze::printImage(std::ofstream& img){//requires image input in .ppm
    //is hard coded to give each sapce a 4x4 area, with 2 wide lines for walls, with 2 wide boarder
    //settup
    using std::string;
    int scale = 50, pixelCounter;
    string black = "0 0 0\n";
    string white = "255 255 255\n";
    string whiteBlock = white + white + white + white;
    string vertBlackBlock = black + black;
    string vertWhiteBlock = white + white;
    string horBlackBlock = black + black + black + black;
    string horWhiteBlock = white + white + white + white;
    string horBlackBlockSmall = black + black;
    
    //file header
    int imgWidth = WIDTH * 6 + 2;
    int imgHeight = HEIGHT * 6 + 2;
    img << "P3" << std::endl;
    img << imgWidth << " " << imgHeight << std::endl;//width, heght: width * 6 - 2
    img << "255" << std::endl;

    //add first line
    string thisLine, midLine, fullText;
    for (int i = 0; i < WIDTH * 2; i++){
        img << vertBlackBlock << vertBlackBlock << vertBlackBlock; //6 blacks
    }
    img << vertBlackBlock << vertBlackBlock;//extra bit for left side line

    //fill maze into img
    for (int j = 0; j < HEIGHT; j++){
        thisLine += vertBlackBlock; //left side line
        midLine += vertBlackBlock; //left sdie line for midLines
        for (int i = 0; i < WIDTH; i++){
            node myNode = grid[i][j];
            thisLine += whiteBlock; //will always print blank block for the node itself
            if (myNode.eastWallExists()) //check for right side wall
                thisLine += vertBlackBlock;
            else
                thisLine += vertWhiteBlock;
            if (myNode.southWallExists()) //check for bottom wall
                midLine += horBlackBlock;
            else 
                midLine += horWhiteBlock;
            midLine += horBlackBlockSmall; // for point b/w 4 blocks
        }
        //push to image, line *4 for 4x4 blocks, mid *2 for two wide
        img << thisLine << thisLine << thisLine << thisLine << midLine << midLine;
        //reset lines
        thisLine = "";
        midLine = "";
    }
    return img;
}