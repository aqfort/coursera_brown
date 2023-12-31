#include <iostream>
#include <vector>
#include <ranges>

namespace rng = std::ranges;
namespace view = rng::views;

int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int x : numbers | view::take(5))
    {
        std::cout << x << ' ';
    }

    std::cout << std::endl;

    return 0;
}
