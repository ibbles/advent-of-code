#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

constexpr int maxRed {12};
constexpr int maxGreen {13};
constexpr int maxBlue {14};

char* find(char const c, char* string)
{
	char* it;
	for (it = string; *it != c; ++it)
	{
	}
	return it;
}

char* findEither(char const c1, char const c2, char* string)
{
	char* it;
	for (it = string; *it != c1 && *it != c2; ++it)
	{
	}
	return it;
}

char* findAndSkip(char const c, char* string)
{
	return find(c, string) + 1;
}

int main()
{
	std::unordered_map<std::string, int> maxAllowed;
	maxAllowed["red"] = maxRed;
	maxAllowed["green"] = maxGreen;
	maxAllowed["blue"] = maxBlue;

	int sum {0};

	std::string line;
	while (std::getline(std::cin, line))
	{
		char* it = &line[0];

		// std::cout << "Game: " << it << '\n';

		it = it + strlen("Game ");
		int const gameId = (int)std::strtol(it, &it, 10);
		// std::cout << "Game ID = " << gameId << '\n';

		++it; // Skip past ':'.
		++it; // Skip past ' '.

		bool allPossible {true};

		std::stringstream roundStream(it);
		std::string round;
		while (std::getline(roundStream, round, ';'))
		{
			// std::cout << "  Round: " << round << "\n";

			std::stringstream cubeStream(round);
			std::string cube;
			while (std::getline(cubeStream, cube, ','))
			{
				// std::cout << "    Cube: " << cube << '\n';
				std::stringstream colorStream(cube);
				int count;
				std::string color;
				colorStream >> count >> color;
				// std::cout << "    Found " << count << " " << color << " cubes.\n";
				if (maxAllowed.find(color) == maxAllowed.end())
				{
					std::cerr << "maxAllowed does not have a limit for '" << color << "'\n";
				}

				if (count > maxAllowed[color])
				{
//					// std::cout << "TOO MANY!\n";
					allPossible = false;
				}
			}
		}

		if (allPossible)
		{
			sum += gameId;
		}

		// std::cout << '\n';
	}

	std::cout << sum << '\n';
}
