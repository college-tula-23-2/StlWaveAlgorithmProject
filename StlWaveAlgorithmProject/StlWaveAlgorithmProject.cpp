// StlWaveAlgorithmProject.cpp 
//
#include <iostream>
#include "WaveAlgorithm.h"

int main()
{
    WaveAlgorithm wa;
    wa.SetMazeFileName();
    wa.CreateMaze();
    wa.ShowMaze();
    std::cout << "\n";

    wa.MoveWave();
    wa.ShowMaze();
    
    wa.CreatePath();
    wa.ShowPath();
}
