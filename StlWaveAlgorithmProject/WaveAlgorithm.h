#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iomanip>

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

enum class CharType
{
	Space  = ' ',
	Wall   = '#',
	Start  = 's',
	Finish = 'f'
};

enum class MazeType
{
	Space = ' ',
	Wall = 178,
	Start = 'S',
	Finish = 'F'
};

struct Cell
{
	int row;
	int column;

	friend bool operator==(const Cell& left, const Cell& right)
	{
		return left.row == right.row && left.column == right.column;
	}

	friend std::ostream& operator<<(std::ostream& out, const Cell& cell)
	{
		out << "[" << cell.row << ", " << cell.column << "]";
		return out;
	}
};



typedef std::vector<std::vector<int>> Maze;
typedef std::array<std::vector<Cell>, 2> Fronts;
typedef std::vector<Cell> Path;



class WaveAlgorithm
{
	std::array<Cell, 4> offsets{ {{-1, 0}, {0, 1}, {1, 0}, {0, -1}} };

	Maze maze;

	Cell startCell;
	Cell finishCell;

	Path path;

	std::string mazeFileName;

public:
	void SetMazeFileName();
	void CreateMaze();
	bool MoveWave();
	void CreatePath();

	void ShowMaze();
	void ShowPath();
};

