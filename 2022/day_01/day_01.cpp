#include <iostream>
#include <string>

int main()
{
    int64_t max_so_far = 0;
    int64_t current = 0;
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            max_so_far = std::max(max_so_far, current);
            current = 0;
            std::cout << "End of elf.\n";
            continue;
        }

        std::cout << "Got line " << line << '\n';
        int64_t value = std::stoi(line);
        current += value;
        std::cout << " current is now " << current << '\n';
    }
    std::cout << max_so_far << '\n';
    return 0;
}
