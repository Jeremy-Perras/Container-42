#pragma once

#include <iostream>

namespace ft{

//==============     NODE         ==============
template <class T, class Alloc = std::allocator<T> >
struct Node {
	typedef T value_type;
	T     data;
  	Node *parent;
	Node *left;
  	Node *right;
  	bool color;
	bool is_null;


	Node():data(value_type()), parent(nullptr),left(nullptr), right(nullptr),color(true), is_null(false){}
	// Node(const Node &rhs)
	// {
	// 	*this = rhs;
	// 	return;
	// }
	Node(const value_type &rhs):parent(nullptr),left(nullptr), right(nullptr),color(true), is_null(false), data(rhs){};

	Node(const Node &rhs) : parent(rhs.parent),left(rhs.left), right(rhs.right),color(rhs.color), is_null(rhs.is_null), data(rhs.data){}



	Node& operator=(const Node &rhs)
	{
		if(this != &rhs)
		{
			this->data = rhs.data;
			this->parent = rhs.parent;
			this->left = rhs.left;
			this->right = rhs.right;
			this->color = rhs.color;
			this->is_null = rhs.is_null;
		}
		return(*this);
	}
 ~Node(){ } ;
};

//==============     PAIR         ==============

template <class T1, class T2>
struct pair{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	//==============     Constructors          ==============

	pair() : first(), second() {}

	pair(const T1& a, const T2& b) : first(a), second(b) { }

	template <class U1, class U2>
	pair(const pair<U1, U2> &rhs) : first(rhs.first), second(rhs.second) { }

	pair(const pair<T1, T2> &rhs) : first(rhs.first), second(rhs.second) { }

	template <typename U1, typename U2>
	pair & operator=(const pair<U1, U2> &rhs){
		this -> first = rhs.first;
		this -> second = rhs.second;
		return (*this);
	}

	pair & operator=(const pair &rhs)/*: first(rhs.first), second(rhs.second) */{
		this -> first = rhs.first;
		this -> second = rhs.second;
		return (*this);
	}

};

//==============     Comparison operations           ==============

template <class T1, class T2>
bool operator==(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs){ return lhs.first == rhs.first && lhs.second == rhs.second; }

template <class T1, class T2>
bool operator!=(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs){ return !(lhs == rhs); }

template <class T1, class T2>
bool operator<(const pair<T1, T2> & lhs, const pair<T1, T2> & rhs){ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

template <class T1, class T2>
  bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(rhs<lhs); }

template <class T1, class T2>
  bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return rhs<lhs; }

template <class T1, class T2>
  bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs<rhs); }

//==============     make_pair           ==============

template <class T1, class T2>
pair<T1, T2> make_pair (T1 x, T2 y) { return pair<T1, T2>(x, y); }




//==============     LEXICOGRAPHICAL COMPARE       ==============

template <class InpIter1, class InpIter2>
bool lexicographical_compare (InpIter1 first1, InpIter1 last1, InpIter2 first2, InpIter2 last2) {
	while (first1 != last1){
		if (first2 == last2 || *first2 < *first1) return false;
		else if (*first1 < *first2) return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

template <class InpIter1, class InpIter2, class Compare>
bool lexicographical_compare (InpIter1 first1, InpIter1 last1, InpIter2 first2, InpIter2 last2, Compare comp){
	while (first1 != last1){
		if (first2 == last2 || comp(*first2, *first1)) return false;
		else if (comp(*first1, *first2)) return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

//==============     EQUAL        ==============

template <class InpIter1, class InpIter2>
bool equal (InpIter1 first1, InpIter1 last1, InpIter2 first2) {
	while (first1 != last1){
		if (!(*first1 == *first2)) return false;
		++first1;
		++first2;
	}
	return true;
}

template <class InpIter1, class InpIter2, class BinaryPredicate>
bool equal (InpIter1 first1, InpIter1 last1, InpIter2 first2, BinaryPredicate pred) {
	while (first1 != last1){
		if (!pred(*first1, *first2)) return false;
		++first1;
		++first2;
	}
	return true;
}

//==============    Enable_if       ==============

template<bool Cond, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };

//==============     IS INTEGRAL        ==============

    template<class T, T v>
    struct integral_constant
    {
        typedef T value_type;
        typedef integral_constant <T, v> type;
        static const T value = v;
    };
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    // is_integral :
    template <class T> struct is_integral : public false_type{};

    template<> struct is_integral<bool> : public true_type{};
    template<> struct is_integral<char> : public true_type{};
    template<> struct is_integral<wchar_t> : public true_type{};
    template<> struct is_integral<signed char> : public true_type{};
    template<> struct is_integral<short int> : public true_type{};
    template<> struct is_integral<int> : public true_type{};
    template<> struct is_integral<long int> : public true_type{};
    template<> struct is_integral<long long int> : public true_type{};
    template<> struct is_integral<unsigned char> : public true_type{};
    template<> struct is_integral<unsigned short int> : public true_type{};
    template<> struct is_integral<unsigned int> : public true_type{};
    template<> struct is_integral<unsigned long int> : public true_type{};
    template<> struct is_integral<unsigned long long int> : public true_type{};
};
