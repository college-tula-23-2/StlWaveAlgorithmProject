#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

/*
read txt map => create digit map
create waves
create path
*/
enum class CellType
{
	Space  = -1,
	Wall   = -2,
	Start  = 0,
	Finish = -3
};

struct Cell
{
	int row;
	int column;
};

typedef std::vector<std::vector<int>> Maze;
typedef std::array<std::vector<Cell>, 2> Fronts;
typedef std::vector<Cell> Path;



class WaveAlgorithm
{
	Maze maze;

	Cell startCell;
	Cell finishCell;

	Fronts fronts;

	bool currentFront{};

	Path path;

	std::string mazeFileName;

public:
	void SetMazeFileName();
	void CreateMaze();
	void MoveWave();
	void CreatePath();

	void ShowMaze();
};

