#include <vector>
#include "vector.hpp"
#include <math.h>
#include <algorithm>

int main()
{
    ft::vector<int> ft_c0;
    std::vector<int> std_c0;
    int testSize = 42;

    for (int i = 0; i < testSize; i++)
    {
        ft_c0.insert(ft_c0.end(), i);
        std_c0.insert(std_c0.end(), i);
    }

    ft::vector<int>::reverse_iterator ft_it0;
    std::vector<int>::reverse_iterator std_it0;

    ft_it0 = ft_c0.rbegin();
    std_it0 = std_c0.rbegin();

    ft::vector<int>::reverse_iterator ft_it1(ft_it0);
    std::vector<int>::reverse_iterator std_it1(std_it0);

    {
        ft::vector<int>::reverse_iterator ft_it1(ft_c0.begin());
        std::vector<int>::reverse_iterator std_it1(std_c0.begin());
    }
    ft_it0++;
    std_it0++;
    ft_it0 += 21;
}