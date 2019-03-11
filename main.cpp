#include <fstream>
#include <iostream>
#include <string>
#include "maze.hpp"


int main(int argNum, char *argName[]){//[1] = name of maze output, [2] = number of mazes
    if (argNum == 3){    
        int length = argName[2][0] - '0';
        for (int i = 0; i < length; ++i){
            maze m;
            std::string fileS = argName[1];
            if (length > 1)
                fileS += ('0' + i);
            fileS += ".ppm";
            std::ofstream fileI(fileS);
            
            m.init();

            srand(time(nullptr) + i);

            m.create();
            m.printImage(fileI);
        }
    }
    else{
        maze m;
        std::ofstream image ("maze.ppm");
        m.create();
        m.printImage(image);
        system("open maze.ppm");
    }
    
    return 0;
}
