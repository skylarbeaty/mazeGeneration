#ifndef NODE_HPP
#define NODE_HPP
#include "maze.hpp" //for vec2

class node{
public:
    node()                      {init();};
    //getters
    bool northWallExists()const {return walls[0];}
    bool eastWallExists()const  {return walls[1];}
    bool southWallExists()const {return walls[2];}
    bool westWallExists()const  {return walls[3];}
    //setters
    void northWallBreak()       {walls[0] = false;}
    void eastWallBreak()        {walls[1] = false;}
    void southWallBreak()       {walls[2] = false;}
    void westWallBreak()        {walls[3] = false;}
    void init()                 {walls[0] = true;
                                 walls[1] = true;
                                 walls[2] = true;
                                 walls[3] = true;}
    void dirWallBreak(int x, int y) {if (x == 0 && y == -1)  northWallBreak();
                                     if (x == 1 && y == 0)  eastWallBreak();
                                     if (x == 0 && y == 1) southWallBreak();
                                     if (x == -1 && y == 0) westWallBreak();}
private:
    bool walls[4]; //NESW starts {1,1,1,1}
};
#endif