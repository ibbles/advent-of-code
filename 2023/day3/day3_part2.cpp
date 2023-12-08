#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

using Row = size_t;
using Column = size_t;
using PartNumber = long;
using Coordinate = std::pair<Row, Column>;

struct PairHasher
{
	size_t operator()(Coordinate const& pair) const
	{
		return (pair.first << 5) + pair.second;
	}
};

std::unordered_map<Coordinate, std::vector<PartNumber>, PairHasher> gears;

void registerGear(Row const row, Column const column, long const partNumber)
{
	gears[Coordinate(row, column)].push_back(partNumber);
}

Column findNumberStart(std::string const& string, Column const start)
{
	Column i {start};
	while (i < string.length() && !std::isdigit(string[i]))
	{
		++i;
	}
	return i;
}

Column findNumberEnd(std::string const& string, Column const start)
{
	Column i {start};
	while (i < string.length() && std::isdigit(string[i]))
	{
		++i;
	}
	return i;
}

bool isGear(char const c)
{
	return c == '*';
}

void parseNextPartNumber(
	std::string const& above, std::string const& current, std::string const& below, Row const row,
	Column const start, Column const end)
{
	PartNumber const partNumber = std::strtol(&current[start], nullptr, 10);

	if (start > 0)
	{
		if (isGear(above[start - 1]))
		{
			registerGear(row - 1, start - 1, partNumber);
		}

		if (isGear(current[start - 1]))
		{
			registerGear(row, start - 1, partNumber);
		}

		if (isGear(below[start - 1]))
		{
			registerGear(row + 1, start - 1, partNumber);
		}
	}

	for (size_t j = start; j < end; ++j)
	{
		if (isGear(above[j]))
		{
			registerGear(row - 1, j, partNumber);
		}
		if (isGear(below[j]))
		{
			registerGear(row + 1, j, partNumber);
		}
	}

	if (end < current.length() - 1)
	{
		if (isGear(above[end]))
		{
			registerGear(row - 1, end, partNumber);
		}
		if (isGear(current[end]))
		{
			registerGear(row, end, partNumber);
		}
		if (isGear(below[end]))
		{
			registerGear(row + 1, end, partNumber);
		}
	}
}

void parsePartNumbers(
	std::string const& above, std::string const& current, std::string const& below, Row const row)
{
	for (Column column = 0; column < current.length();)
	{
		Column const start = findNumberStart(current, column);
		if (start >= current.length())
		{
			break;
		}

		Column const end = findNumberEnd(current, start);
		parseNextPartNumber(above, current, below, row, start, end);
		column = end;
	}
}

int main()
{
	std::string above;
	std::string current;
	std::string below;

	std::getline(std::cin, current);
	above.resize(current.length(), '.');
	std::getline(std::cin, below);

	Row row = 0;
	parsePartNumbers(above, current, below, row++);

	above = std::move(current);
	current = std::move(below);
	while (std::getline(std::cin, below))
	{
		parsePartNumbers(above, current, below, row++);
		above = std::move(current);
		current = std::move(below);
	}
	below.resize(current.length(), '.');
	parsePartNumbers(above, current, below, row++);

	size_t sum {0};
	for (std::pair<std::pair<Row, Column>, std::vector<PartNumber>> const& gear : gears)
	{
		std::cout << "(" << gear.first.first << ", " << gear.first.second << "): ";
		for (PartNumber const partNumber : gear.second)
		{
			std::cout << partNumber << ", ";
		}
		std::cout << '\n';

		if (gear.second.size() == 2)
		{
			sum += gear.second[0] * gear.second[1];
		}
	}

	std::cout << sum << '\n';
}
