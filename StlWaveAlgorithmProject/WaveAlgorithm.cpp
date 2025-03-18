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
				break;
			case CharType::Finish:
				maze[indexLast].push_back((int)CellType::Finish);
				break;
			default:
				break;
			}
		}
	}

	inFileStream.close();

	/*std::cout << "\n";
	for (auto v : maze)
	{
		for (auto item : v)
			std::cout << std::setw(2) << item;
		std::cout << "\n";
	}*/
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
				std::cout << (char)MazeType::Space;
				break;
			case CellType::Wall:
				std::cout << (char)MazeType::Wall;
				break;
			case CellType::Start:
				std::cout << (char)MazeType::Start;
				break;
			case CellType::Finish:
				std::cout << (char)MazeType::Finish;
				break;
			default:
				break;
			}
		}
		std::cout << "\n";
	}
}
