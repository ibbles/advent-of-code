#include <algorithm>
#include <iostream>

int main()
{
	size_t sum {0};
	std::string line;
	while (std::getline(std::cin, line))
	{
		std::string::const_iterator const firstIt =
			std::find_if(std::begin(line), std::end(line), &::isdigit);
		sum += (*firstIt - '0') * 10;

		std::string::const_reverse_iterator const lastIt =
			std::find_if(std::rbegin(line), std::rend(line), &::isdigit);
		sum += (*lastIt - '0');
	}
	std::cout << "Final result: " << sum << '\n';
	return 0;
}

