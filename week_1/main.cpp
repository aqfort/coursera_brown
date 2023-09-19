#include <iostream>
#include <string>
#include <map>

int main()
{
    std::map<int, std::string> temp = {{1, "one"}, {2, "two"}};
    for (const auto& [key, value] : temp) {
        std::cout << key << ' ' << value << std::endl;
    }
    return 0;
}
    