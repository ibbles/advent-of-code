/*
Compute a similarity score.
Count occurrences from the left list in the right list.
Multiply the number in the left list with the count of the number in the right list.
Duplicate numbers are counted multiple times so we don't need to keep a history of seen numbers.

Idea:
	Read the two lists.
	Sort the right list.
	Loop through the left list.
	Use std::equal_range to find the number of equal numbers.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::vector<int> left_list;
	std::vector<int> right_list;
	int left {0};
	int right {0};

	while (std::cin >> left && std::cin >> right)
	{
		left_list.push_back(left);
		right_list.push_back(right);
	}

	std::sort(std::begin(right_list), std::end(right_list));

	ptrdiff_t total_distance {0};
	for (int value : left_list)
	{
		std::pair<std::vector<int>::iterator, std::vector<int>::iterator> range {
			std::equal_range(std::begin(right_list), std::end(right_list), value)};
		ptrdiff_t num_in_right {range.second - range.first};
		total_distance += value * num_in_right;
	}

	std::cout << total_distance << '\n';
}
