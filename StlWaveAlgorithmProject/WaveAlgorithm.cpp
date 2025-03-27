#include "WaveAlgorithm.h"

namespace fs = std::filesystem;

void WaveAlgorithm::SetMazeFileName()
{
	fs::path currentPath{ fs::current_path() };
	
	std::vector<std::string> mazeFiles;

	for (auto dirEntry : fs::directory_iterator(currentPath))
		if (dirEntry.path().extension().string() == ".maze")
			mazeFiles.push_back(dirEntry.path().filename().string());

	std::cout << "Maze\'s files:\n";
	for (int i{}; i < mazeFiles.size(); i++)
		std::cout << i + 1 << ": " << mazeFiles[i] << "\n";

	int selectedPosition;
	std::cout << "Input number of file: ";
	std::cin >> selectedPosition;

	this->mazeFileName = mazeFiles[selectedPosition - 1];
	//std::cout << this->mazeFileName << "\n";
}

void WaveAlgorithm::CreateMaze()
{
	std::ifstream inFileStream(this->mazeFileName, std::ios_base::in);

	int sizeMazeLine{ 1024 };
	char* mazeLine{ new char[sizeMazeLine] };

	while (!inFileStream.eof())
	{
		inFileStream.getline(mazeLine, sizeMazeLine);
		maze.push_back(std::vector<int>());
		int indexLast = maze.size() - 1;

		//std::cout << std::setw(2) << mazeLine << "\n";

		for (auto s : std::string(mazeLine))
		{
			CharType symbol = (CharType)std::tolower(s);
			switch (symbol)
			{
			case CharType::Space:
				maze[indexLast].push_back((int)CellType::Space);
				break;
			case CharType::Wall:
				maze[indexLast].push_back((int)CellType::Wall);
				break;
			case CharType::Start:
				maze[indexLast].push_back((int)CellType::Start);
				startCell.row = indexLast;
				startCell.column = maze[indexLast].size() - 1;
				break;
			case CharType::Finish:
				maze[indexLast].push_back((int)CellType::Finish);
				finishCell.row = indexLast;
				finishCell.column = maze[indexLast].size() - 1;
				break;
			default:
				break;
			}
		}
	}

	inFileStream.close();
}

bool WaveAlgorithm::MoveWave()
{
	Fronts fronts;
	bool isFinish{};
	bool currentFront{};

	fronts[currentFront].push_back(startCell);
	int currentNumber{};

	while (true)
	{
		currentNumber++;
		fronts[!currentFront].clear();

		for (auto frontCell : fronts[currentFront])
		{
			for (auto offset : offsets)
			{
				Cell candidat{ frontCell.row + offset.row,
								frontCell.column + offset.column };

				if (maze[candidat.row][candidat.column] == (int)CellType::Space ||
					maze[candidat.row][candidat.column] == (int)CellType::Finish)
				{
					maze[candidat.row][candidat.column] = currentNumber;
					fronts[!currentFront].push_back(candidat);
				}

				if (candidat == finishCell)
				{
					isFinish = true;
					break;
				}
			}
			if (isFinish) break;
		}
		if (isFinish) break;

		if (!fronts[!currentFront].size())
			break;

		currentFront = !currentFront;
	}

	return isFinish;
}

void WaveAlgorithm::CreatePath()
{
	path.push_back(finishCell);

	int currentNumber = maze[finishCell.row][finishCell.column];

	while (currentNumber)
	{
		Cell currentCell = path[path.size() - 1];
		for (auto offset : offsets)
		{
			Cell candidat{ currentCell.row + offset.row,
						   currentCell.column + offset.column };
			if (maze[candidat.row][candidat.column] == currentNumber - 1)
			{
				path.push_back(candidat);
				break;
			}
		}
		currentNumber--;
	}

	std::reverse(path.begin(), path.end());
}

void WaveAlgorithm::ShowMaze()
{
	for (auto line : maze)
	{
		for (auto i : line)
		{
			CellType item = (CellType)i;
			switch (item)
			{
			case CellType::Space:
				std::cout << (char)MazeType::Space
						  << (char)MazeType::Space;
				break;
			case CellType::Wall:
				std::cout << (char)MazeType::Wall
						  << (char)MazeType::Wall;
				break;
			case CellType::Start:
				std::cout << std::setw(2) << (char)MazeType::Start;
				break;
			case CellType::Finish:
				std::cout << std::setw(2) << (char)MazeType::Finish;
				break;
			default:
				std::cout << std::setw(2) << i;
			}
		}
		std::cout << "\n";
	}
}

void WaveAlgorithm::ShowPath()
{
	std::cout << "\n";
	for (auto cell : path)
		std::cout << cell << " | ";
	std::cout << "\n";
}
