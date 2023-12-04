#include <algorithm>
#include <optional>
#include <iostream>

std::optional<int> try_parse(char const* const string)
{
	// clang-format off
	static std::string_view digit_names[] =
	{
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine"
	};
	// clang-format on

	// Detect plain digits.
	if (string[0] >= '0' && string[0] <= '9')
	{
		return string[0] - '0';
	}

	// Detect named digits.
	for (size_t i = 0; i < std::size(digit_names); ++i)
	{
		std::string_view digit_name = digit_names[i];
		if (std::string_view(string, digit_name.length()) == digit_name)
		{
			return i + 1; // + 1 because digit_names[0] holds "one".
		}
	}

	return {};
}

int main()
{
	size_t sum {0};
	std::string line;
	while (std::getline(std::cin, line))
	{
		for (size_t i = 0; i < line.length(); ++i)
		{
			std::optional<int> digit = try_parse(&line[i]);
			if (digit.has_value())
			{
				sum += digit.value() * 10;
				break;
			}
		}

		for (size_t i = line.length(); i > 0; i--)
		{
			std::optional<int> digit = try_parse(&line[i - 1]);
			if (digit.has_value())
			{
				sum += digit.value();
				break;
			}
		}
	}
	std::cout << "Final result: " << sum << '\n';
	return 0;
}
