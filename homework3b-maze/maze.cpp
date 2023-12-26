#include <iostream>
#include <string>
#include <fstream>

#include <fstream>
#include <string>
#include "Grid.h"

using namespace std;

bool solveMaze(int x,int y,int z,Grid &maze, vector <int> &solution) {
//    Base Cases
//    cout << x << ", " << y << ", " << z <<  endl;
    //    out of bounds cases
    if (x < 0 || y < 0 || z < 0 || x > maze.height()-1 || y > maze.width()-1 || z > maze.depth()-1) {
        return false;
    }
    if (maze.at(x,y,z) == 0) {
        return false;
    }
//    Check if we have been there before
    if (maze.at(x,y,z) == 2) {
        return false;
    }
//   Our maze is solved

    if(x == maze.height()-1 && y == maze.width()-1 && z == maze.depth()-1) {
        solution.push_back(x);
        solution.push_back(y);
        solution.push_back(z);
        return true;
    }
//    base case for no possible movement in any direction
//    if(maze.at(x +1, y, z) == 1) {
//        solution.push_back(x+1);
//        solution.push_back(y);
//        solution.push_back(z);
//        solveMaze(x+1,y,z,maze,solution);
//
//    }
    maze.at(x,y,z) = 2;
//    Recursive Step
    if (solveMaze(x+1, y, z, maze,solution) ||
        solveMaze(x-1, y, z,maze,solution) ||
        solveMaze(x, y+1, z,maze, solution) ||
        solveMaze(x, y-1, z,maze, solution) ||
        solveMaze(x, y, z+1,maze,solution) ||
        solveMaze(x, y, z-1,maze,solution) ){
        solution.push_back(x);
        solution.push_back(y);
        solution.push_back(z);
        return true;
    }
    return false;
}



int main(int argc, char* argv[]) {
    Grid maze;
    vector <int> solution;

    ofstream fOut(argv[2]);
    ifstream in(argv[1]);
    in >> maze;




//    cout << maze.height() << endl;
//    cout << maze.width() << endl;
//    cout << maze.depth() << endl;

   bool mazeSolved = solveMaze(0,0,0,maze,solution);

    if(!mazeSolved) {
        fOut << "NO SOLUTION" << endl;
    }
    else {
        //    My Solution
        int i = solution.size();
//    cout << i << endl;
        fOut << "SOLUTION" << endl;
        for (i = solution.size() - 1; i >= 0; i = i - 3) {
            cout << solution.at(i -2) << " ";
            cout << solution.at(i - 1) << " ";
            cout << solution.at(i) << endl;
            fOut << solution.at(i - 2) << " ";
            fOut << solution.at(i - 1) << " ";
            fOut << solution.at(i) << endl;
        }
    }

    in.close();
    fOut.close();

    return 0;
}
