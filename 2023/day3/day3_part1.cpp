#include <string>
#include <iostream>

size_t findNumberStart(std::string const& string, size_t const start)
{
	size_t i {start};
	while (i < string.length() && !std::isdigit(string[i]))
	{
		++i;
	}
	return i;
}

size_t findNumberEnd(std::string const& string, size_t const start)
{
	size_t i {start};
	while (i < string.length() && std::isdigit(string[i]))
	{
		++i;
	}
	return i;
}

bool isSymbol(char const c)
{
	return !std::isdigit(c) && c != '.';
}

long parseNextPartNumber(
	std::string const& above, std::string const& current, std::string const& below,
	size_t const start, size_t const end)
{
	if (start > 0)
	{
		if (isSymbol(above[start - 1]) || isSymbol(current[start - 1]) ||
			isSymbol(below[start - 1]))
		{
			std::cout << "Part number " << std::string_view(&current[start], end - start)
					  << " should be included.\n";
			return std::strtol(&current[start], nullptr, 10);
		}
	}

	for (size_t j = start; j < end; ++j)
	{
		if (isSymbol(above[j]) || isSymbol(below[j]))
		{
			std::cout << "Part number " << std::string_view(&current[start], end - start)
					  << " should be included.\n";
			return std::strtol(&current[start], nullptr, 10);
		}
	}

	if (end < current.length() - 1)
	{
		if (isSymbol(above[end]) || isSymbol(current[end]) || isSymbol(below[end]))
		{
			std::cout << "Part number " << std::string_view(&current[start], end - start)
					  << " should be included.\n";
			return std::strtol(&current[start], nullptr, 10);
		}
	}

	return 0;
}

long parsePartNumbers(
	std::string const& above, std::string const& current, std::string const& below)
{
	long sum {0};
	for (size_t i = 0; i < current.length();)
	{
		size_t const start = findNumberStart(current, i);
		if (start >= current.length())
		{
			break;
		}

		size_t const end = findNumberEnd(current, start);
		sum += parseNextPartNumber(above, current, below, start, end);
		i = end;
	}
	return sum;
}

int main()
{
	std::string above;
	std::string current;
	std::string below;

	std::getline(std::cin, current);
	above.resize(current.length(), '.');
	std::getline(std::cin, below);

	long sum = parsePartNumbers(above, current, below);

	above = std::move(current);
	current = std::move(below);
	while (std::getline(std::cin, below))
	{
		sum += parsePartNumbers(above, current, below);
		above = std::move(current);
		current = std::move(below);
	}
	below.resize(current.length(), '.');
	sum += parsePartNumbers(above, current, below);
	std::cout << "Sum = " << sum << '\n';
}
