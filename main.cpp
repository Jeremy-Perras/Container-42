#include <list>
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <map>
#include <string>
#include "vector.hpp"


int main()
{
    std::vector<int>            std_vec;
    std::list<std::string>      std_lis;
    std::stack<char>            std_sta;
    std::stack<double>          std_que;
    std::map<int, std::string>  std_map;
    ft::vector<int>::iterator it;

    ft::vector<int> ft_vec(4,100);
    ft_vec.pop_back();
    it = ft_vec.begin();
    std::cout << *it <<std::endl;
    for (ft::vector<int>::iterator it = ft_vec.begin(); it != ft_vec.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return(0);
}
