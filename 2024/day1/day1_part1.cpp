/*
Input: two lists of location IDs.
Compare the two lists.
Pair up elements in ascending order.
Pair-wise distance is the absolute value of the difference between two elements at the same ordered
location.
The total distance is the sum of the pair-wise distances.

Can we assume the lists have the same length?
How large can a a location ID be?
Is int large enough?
Can location IDs be negative?

Idea 1: Sort the lists, then zip them computing the distance for each pair.
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

	std::sort(std::begin(left_list), std::end(left_list));
	std::sort(std::begin(right_list), std::end(right_list));

	int total_distance {0};
	for (size_t i = 0; i < left_list.size(); ++i)
	{
		total_distance += std::abs(left_list[i] - right_list[i]);
	}

	std::cout << total_distance << '\n';
}
