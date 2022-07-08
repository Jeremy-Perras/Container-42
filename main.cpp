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
    // std::vector<int>            std_vec;
    std::list<std::string>      std_lis;
    std::stack<char>            std_sta;
    std::stack<double>          std_que;
    std::map<int, std::string>  std_map;
    ft::vector<int>::iterator it;

    ft::vector<int>  std_vec(4,100);
    ft::vector<int> ft_vec(4,100);
    std::vector<int>::const_iterator it2;
    ft_vec.pop_back();
    it = ft_vec.begin();
    std::cout << *it <<std::endl;
    for (ft::vector<int>::const_iterator it2 = std_vec.begin(); it2 != std_vec.end(); ++it2)
    {

            std::cout << ' ' << *it2 <<"\n";
            std::cout << ' ' << *(it2 -  1)  <<"\n";

              // *it2 = 200;
    }
    for (ft::vector<int>::iterator it = ft_vec.begin(); it != ft_vec.end(); ++it)
    {

            std::cout << ' ' << *it <<"\n";
            std::cout << ' ' << *(it - 1)  <<"\n";

             *it = 200;
    }
    std::cout << '\n';


    return(0);
}
