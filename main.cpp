#include "map.hpp"
#include "utils.hpp"
#include "vector.hpp"
#include "stack.hpp"
#include "set.hpp"
#include <stack>
#include <iostream>       // std::cout
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <deque>
#include <map>
#include <ctime>
#include <iostream>
#include <chrono>
#include <unistd.h>

int main(void)
{
	std::cout << "=================================================================\n" <<
	"==============          vector          =========================\n" <<
	"=================================================================\n";

	std::cout << "\nTesting vector efficacity : \n\n"; 

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	std::vector<int> stdvector;
	for(int i = 0; i < 200000; i++)
		stdvector.push_back(i);
	for(int i = 0; i < 200000; i++)
  		stdvector.pop_back();
	std::chrono::time_point<std::chrono::system_clock> endstd = std::chrono::system_clock::now();
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(endstd - start).count();
	std::cout << "std::elapsed time: " << elapsed_seconds << "milliseconds" << std::endl;
	ft::vector<int> ftvector;
    for(int i = 0; i < 200000; i++)
	   ftvector.push_back(i);
    for(int i = 0; i < 200000; i++)
	   ftvector.pop_back();
   std::chrono::time_point<std::chrono::system_clock> endft = std::chrono::system_clock::now();
   elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(endft - endstd).count();
   std::cout << "ft::elapsed time: " << elapsed_seconds << "milliseconds" << std::endl;
	 

	std::cout << "=================================================================\n" <<
	"==============      iterator_vector     =========================\n" <<
	"=================================================================\n";
   
   for(int i = 0; i < 20; i++)
		ftvector.push_back(i);

	std::cout << "\nIterating on  the vector using a ITERATOR : \n\n"; 
   for(ft::vector<int>::iterator ftiter = ftvector.begin(); ftiter < ftvector.end(); ftiter++)
	   std::cout << *ftiter << std::endl ;


	std::cout << "=================================================================\n" <<
	"==============  const_iterator_vector   =========================\n" <<
	"=================================================================\n";

	std::cout << "\nIterating on  the vector using a CONSTANT ITERATOR : \n\n"; 

   for(ft::vector<int>::const_iterator ftiter = ftvector.begin(); ftiter < ftvector.end(); ftiter++)
   {

	   std::cout << *ftiter << std::endl ;
	    //*ftiter = 1;
   }

	std::cout << "===============================================================================\n" <<
	"==============          surcharge des operteurs       =========================\n" <<
	"===============================================================================\n";

	std::cout << "\nIncrementing and decrementing iterators on FT VECTOR : \n\n"; 
   ft::vector<int>::const_iterator ftiter = ftvector.end();
   ftiter--;
   std::cout << *(ftiter) << std::endl ;
   ++ftiter;
   std::cout << *(ftiter) << std::endl ;
   --ftiter;
   std::cout << *(ftiter) << std::endl ;
   for(int i = 0; i < 20; i++)
		stdvector.push_back(i);

	std::cout << "\nIncrementing and decrementing iterators on STD VECTOR : \n\n"; 
	std::vector<int>::const_iterator stditer = stdvector.end();
	stditer--;
    std::cout << *(stditer) << std::endl ;
    ++stditer;
    std::cout << *(stditer) << std::endl ;
    --stditer;
	std::cout << *(ftiter) << std::endl ;
   
   	std::cout << "=================================================================\n" <<
	"==============           swap           =========================\n" <<
	"=================================================================\n";
	
	std::cout << "\nSWAPing two vectors and printing the result : \n\n"; 
	ft::vector<int> foo (3,100);
	foo.swap(ftvector);
	std::cout << "swap : " << std::endl ;
	for(ft::vector<int>::iterator ftiter = ftvector.begin(); ftiter < ftvector.end(); ftiter++)
 	   std::cout << *ftiter << std::endl ;

	std::cout << "=================================================================\n" <<
	"==============           map            =========================\n" <<
	"=================================================================\n";

	std::cout << "\nTesting map efficacity : \n\n"; 

	std::chrono::time_point<std::chrono::system_clock> mapstdstart = std::chrono::system_clock::now();
	std::map<int, int> stdmap;
	for(int i = 0; i <10000000; i++)
		stdmap.insert ( std::pair<int,int>(i, i+1) );
	// for(int i = 0; i <10000000; i++)
	// 	stdmap.erase(i);
	std::chrono::time_point<std::chrono::system_clock> mapstdend = std::chrono::system_clock::now();
	elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(mapstdend - mapstdstart).count();
	std::cout << "std::elapsed time: " << elapsed_seconds << " milliseconds" << std::endl;
	std::chrono::time_point<std::chrono::system_clock> mapftstart = std::chrono::system_clock::now();
	ft::map<int,int> ftmap;
	for(int i = 0; i <10000000; i++)
		ftmap.insert ( ft::pair<int,int>(i, i+1) );
	// for(int i = 0; i <10000000; i++)
	// 	ftmap.erase(i);
	std::chrono::time_point<std::chrono::system_clock> mapftend = std::chrono::system_clock::now();
	elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(mapftend - mapftstart).count();
	std::cout << "ft::elapsed time: " << elapsed_seconds << " milliseconds" << std::endl;

	std::chrono::time_point<std::chrono::system_clock> mapstdstartfind = std::chrono::system_clock::now();
	long long int stdsum = 0;
	for(int i = 0; i <50000; i++)
	{
		stdsum += stdmap.find(i) -> first;
		stdsum += stdmap.find(i+700000) -> first;
	}
	std::chrono::time_point<std::chrono::system_clock> mapstdendfind = std::chrono::system_clock::now();
	elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(mapstdendfind - mapstdstartfind).count();
	std::cout << "std find ::elapsed time: " << elapsed_seconds << " milliseconds" << " the sum is : " << stdsum << std::endl;

	std::chrono::time_point<std::chrono::system_clock> mapftstartfind = std::chrono::system_clock::now();
	long long int ftsum = 0;
	for(int i = 0; i < 50000; i++)
	{
		ftsum += ftmap.find(i) -> first;
		ftsum += ftmap.find(i+700000) -> first;
	}
	std::chrono::time_point<std::chrono::system_clock> mapftendfind = std::chrono::system_clock::now();
	elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>(mapftendfind - mapftstartfind).count();
	std::cout << "ft find ::elapsed time: " << elapsed_seconds << " milliseconds" << " the sum is : " << ftsum << std::endl;

	ft::map<char,int> mymap;
	for(int i = 65; i < 127; i++)
		mymap.insert ( ft::pair<char,int>(i,100 + i) );

	std::cout << "=================================================================\n" <<
	"==============    recopy_constructor    =========================\n" <<
	"=================================================================\n\n";

	std::cout << "Printing the content of mymap2 : \n\n";

   ft::map<char,int> mymap2(mymap);
   for (ft::map<char,int>::iterator it=mymap2.begin(); it!=mymap2.end(); ++it)
	 std::cout << it->first << " => " << it->second << '\n';
   std::cout << "---------------------------------" << '\n';
   ft::pair<ft::map<char,int>::iterator,bool> ret;
   ret = mymap.insert ( ft::pair<char,int>('z',500) );
   if (ret.second==false) {
     std::cout << "element 'z' already existed";
     std::cout << " with a value of " << ret.first->second << "\n\n";
   }


   ft::map<char,int>::iterator it = mymap.begin();
   mymap.insert (it, ft::pair<char,int>('b',300));
   mymap.insert (it, ft::pair<char,int>('c',400));


   ft::map<char,int> anothermap;
   anothermap.insert(mymap.begin(),mymap.find('c'));

   	std::cout << "======================================================================\n" <<
	"==============    map_iterator_constructor   =========================\n" <<
	"======================================================================\n";

   std::cout << "\nPrinting the content of mymap : \n\n";
   for (it=mymap.begin(); it!=mymap.end(); ++it)
     std::cout << it->first << " => " << it->second << '\n';
	//mymap.printTree();

   std::cout << "\nPrinting the content of anothermap : \n\n";
   for (it=anothermap.begin(); it!=anothermap.end(); ++it)
     std::cout << it->first << " => " << it->second << '\n';
   //anothermap.printTree();

	std::cout << "=================================================================\n" <<
	"==============           swap           =========================\n" <<
	"=================================================================\n";

	ft::map<char,int> fo;

	  fo['x']= 100;
	  fo['y']= 200;

    fo.swap(anothermap);
	std::cout << "\nAnothermap contains after swap:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';
	fo.swap(anothermap);

	std::cout << "=================================================================\n" <<
	"==============           find           =========================\n" <<
	"=================================================================\n";
	
	std::cout << "\nSearching for the element with key <A> and trying to erase it : \n\n";
	it = anothermap.find('A');
	if (it != mymap.end())
	    anothermap.erase (it);

	std::cout << "\nPrinting the content of anothermap : \n\n";	
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
      std::cout << it->first << " => " << it->second << '\n';

	std::cout << "\nSearching the element with key <B> and printing its value : \n\n";	
	 it = anothermap.find('B');
	 std::cout << it->first << " => " << it->second << '\n';


	std::cout << "=================================================================\n" <<
	"==============          operator[]      =========================\n" <<
	"=================================================================\n\n";
	  
	std::cout << "\nModifying value of element with key <B> and printing its value : \n\n";	
	  anothermap['B'] = 3;

	  std::cout <<  anothermap['B'] << std::endl;

	std::cout << "\nSize of anothermap before searching for element with key <A> : \n";	
	  std::cout << anothermap.size() << std::endl;

	  std::cout << anothermap['A'] << std::endl;

	std::cout << "\nSize of anothermap after searching for element with key <A> : \n";
	  std::cout << anothermap.size() << std::endl;


 	std::cout << "=================================================================\n" <<
	"==============          stack           =========================\n" <<
	"=================================================================\n\n";

 	ft::stack<int> mystack;
	ft::stack<int> mystack2;
   for (int i=0; i<100; ++i) mystack.push(i);

	std::cout << "Stack size after pushing 100 elements : " << mystack.size() << "\n\n";
	mystack2=mystack;
	std::cout << "Popping out elements...";

	while (!mystack.empty())
   {
      std::cout << ' ' << mystack.top();
      mystack.pop();
   }

	std::cout << "\n\n" << "Stack size after pushing 100 elements : " << mystack.size() << '\n';
 	
   std::cout << "\nEgalité : printing and poping out content of MyStack2\n";
	ft::stack<int> mystack3(mystack2);
   while (!mystack2.empty())
   {
      std::cout << ' ' << mystack2.top();
      mystack2.pop();
   }

   std::cout << "\nRecopie : printing anbd poping out content of MyStack3\n";
   while (!mystack3.empty())
   {
      std::cout << ' ' << mystack3.top();
      mystack3.pop();
   }
   std::cout << "\n\nFIN\n\n";

	std::cout << "=================================================================\n" <<
	"==============            set           =========================\n" <<
	"=================================================================\n\n";

  	ft::set<int> myset;
	for(int i = 65; i < 127; i++)
		myset.insert( i );

	std::cout << "=================================================================\n" <<
	"==============    recopy_constructor    =========================\n" <<
	"=================================================================\n\n";

	std::cout << "Printing the content of myset2 : \n\n";

   ft::set<int> myset2(myset);
   for (ft::set<int>::iterator it=myset2.begin(); it!=myset2.end(); ++it)
	 std::cout << *(it) << " ";
   std::cout << "\n---------------------------------" << '\n';
   ft::pair<ft::set<int>::iterator,bool> setres;
   setres = myset.insert ( 100 );
   if (setres.second==false) {
     std::cout << "element '100' already existed" << "\n\n";
   }


   ft::set<int>::iterator setiter = myset.begin();

   ft::set<int> anotherset;
   anotherset.insert(myset.begin(),myset.find(90));

   	std::cout << "======================================================================\n" <<
	"==============    set_iterator_constructor   =========================\n" <<
	"======================================================================\n";

   std::cout << "\nPrinting the content of myset : \n\n";
   for (setiter=myset.begin(); setiter!=myset.end(); ++setiter)
     std::cout << *(setiter) << " ";
   std::cout << "\n---------------------------------" << '\n';

   std::cout << "\nPrinting the content of anotherset : \n\n";
   for (setiter=anotherset.begin(); setiter!=anotherset.end(); ++setiter)
     std::cout << *(setiter) << " ";
	std::cout << "\n---------------------------------" << '\n';

	std::cout << "=================================================================\n" <<
	"==============           find           =========================\n" <<
	"=================================================================\n";
	
	std::cout << "\nSearching for the element <75> and trying to erase it : \n\n";
	setiter = anotherset.find(75);
	if (setiter != myset.end())
	    anotherset.erase (setiter);

	std::cout << "\nPrinting the content of anotherset : \n\n";	
	for (setiter=anotherset.begin(); setiter!=anotherset.end(); ++setiter)
      std::cout << *(setiter) << " ";
	std::cout << "\n---------------------------------" << '\n';

}
