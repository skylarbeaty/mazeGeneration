#ifndef MAZE_HPP
#define MAZE_HPP

#include <stack>
#include "node.hpp"

using std::stack;

struct vec2{
    vec2(){
        x = 0;
        y = 0;
    }
    vec2(int _x, int _y){
        x = _x;
        y = _y;
    }
    vec2 operator+(vec2 rhs) const{
        return vec2(x + rhs.x, y + rhs.y);
    }
    vec2 operator*(int scaler)const{
        return vec2(x * scaler, y * scaler);
    }
    bool operator==(vec2 rhs)const{
        return(x == rhs.x && y == rhs.y);
    }
    bool operator!=(vec2 rhs)const{
        return(x != rhs.x || y != rhs.y);
    }
    void operator=(vec2 rhs){
        x = rhs.x;
        y = rhs.y;
    }
    int x;
    int y;
};

const int WIDTH = 50;
const int HEIGHT = 50;

class maze{
    
public:
    maze();
    maze(bool createMaze);
    void init();// need to init each node!!
    void create();
    vec2 randomMove(vec2);
    bool isValid(vec2);
    void printMaze();
    std::ofstream& printImage(std::ofstream&);
private:
    node grid[WIDTH][HEIGHT];      // keeps track of walls knocked out by path
    bool traversed[WIDTH][HEIGHT]; // true anywhere the path has been
    stack<vec2> currentPath;       // path back to the start
    
};
#endif