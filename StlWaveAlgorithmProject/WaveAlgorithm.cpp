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
	std::cout << this->mazeFileName << "\n";
}
