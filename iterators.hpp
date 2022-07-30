#pragma once
#include <iterator>
#include "utils.hpp"

namespace ft{

//=================================================================
//==============           Iterator traits           ==============
//=================================================================


template <class Iter>
class iterator_traits {
	public:
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;

};

template <class T>
class iterator_traits<T*> {
	public:
		typedef std::ptrdiff_t						difference_type;
		typedef T 									value_type;
		typedef T* 									pointer;
		typedef T& 									reference;
		typedef std::random_access_iterator_tag		iterator_category;
};

template <class T>
class iterator_traits<const T*> {
	public:
		typedef std::ptrdiff_t						difference_type;
		typedef T 									value_type;
		typedef const T* 							pointer;
		typedef const T& 							reference;
		typedef std::random_access_iterator_tag		iterator_category;
};

template<class T> struct remove_const { typedef T type; };

template<class T> struct remove_const <const T> { typedef T type; };

//=================================================================
//==============           Vector iterator           ==============
//=================================================================


template <class T>
class my_iter{


	public:
		typedef typename ft::iterator_traits<T*>::difference_type		difference_type;
		typedef typename ft::iterator_traits<T*>::value_type			value_type;
		typedef typename ft::iterator_traits<T*>::pointer				pointer;
		typedef typename ft::iterator_traits<T*>::reference				reference;
		typedef std::random_access_iterator_tag							iterator_category;

	private:
		pointer _ptr;

	public:
		//==============     Constructors          ==============
		my_iter() : _ptr(nullptr) {}

		my_iter(pointer x) : _ptr(x) {}

		my_iter(const my_iter<typename remove_const<value_type>::type > & rhs) : _ptr(&(*rhs)) {}


		my_iter<value_type> & operator=(my_iter<typename remove_const<value_type>::type > const & src) {
			_ptr = &(*src);
			return *this;
		}

		virtual ~my_iter() {}

		//==============     Pointer like operations          ==============

		reference operator*() const{ return *(this -> _ptr);}

		pointer operator->() const{ return this -> _ptr;}

		reference operator[](const difference_type& offset) const { return this -> _ptr[offset];}


		//==============     Increment / Decrement           ==============

		my_iter& operator++(){ ++(this -> _ptr); return *this; }

		my_iter operator++(int){ my_iter tmp(*this); ++_ptr; return tmp;}

		my_iter& operator--(){ --(this -> _ptr); return *this; }

		my_iter operator--(int){ my_iter tmp(*this); --_ptr; return tmp; }


		//==============     Arithmetic operations           ==============

		my_iter& operator+=(const difference_type& n) { this -> _ptr += n; return *this; }

		my_iter operator+(const difference_type& n) { return my_iter(this -> _ptr + n); }

		my_iter& operator-=(const difference_type& n) { this -> _ptr -= n; return *this; }

		my_iter operator-(const difference_type& n) { return my_iter(this -> _ptr - n); }

		const my_iter &base() const { return this -> _ptr; }
};

//==============     Comparison operations           ==============

template < typename IteratorL, typename IteratorR>
bool operator==(const my_iter<IteratorL> & lhs, const my_iter<IteratorR> & rhs){ return &(*lhs) == &(*rhs); }

template < typename IteratorL, typename IteratorR>
bool operator!=(const my_iter<IteratorL> & lhs, const my_iter<IteratorR> & rhs){ return &(*lhs) != &(*rhs); }

template < typename IteratorL, typename IteratorR>
bool operator<(const my_iter<IteratorL> & lhs, const my_iter<IteratorR> & rhs){ return &(*lhs) < &(*rhs); }

template < typename IteratorL, typename IteratorR>
bool operator>(const my_iter<IteratorL> & lhs, const my_iter<IteratorR> & rhs){ return &(*lhs) > &(*rhs); }

template < typename IteratorL, typename IteratorR>
bool operator<=(const my_iter<IteratorL> & lhs, const my_iter<IteratorR> & rhs){ return &(*lhs) <= &(*rhs); }

template < typename IteratorL, typename IteratorR>
bool operator>=(const my_iter<IteratorL> & lhs, const my_iter<IteratorR> & rhs){ return &(*lhs) >= &(*rhs); }

template < typename IteratorL, typename IteratorR>
typename my_iter<IteratorL>::difference_type operator-(const my_iter<IteratorL> & lhs,
	const my_iter<IteratorR> & rhs){ return &(*lhs) - &(*rhs); }

template < typename Iterator>
my_iter<Iterator> operator-(const my_iter<Iterator> & iter, typename my_iter<Iterator>::difference_type n){ return iter - n; }

template < typename Iterator>
my_iter<Iterator> operator+(const my_iter<Iterator> & iter, typename my_iter<Iterator>::difference_type n){ return iter + n; }



//=================================================================
//==============           Tree iterators            ==============
//=================================================================

template <typename U>
class tree_iterator
{
public:
	typedef typename iterator_traits<U *>::difference_type		difference_type;
	typedef typename iterator_traits<U *>::value_type			value_type;
	typedef typename iterator_traits<U *>::pointer				pointer;
	typedef typename iterator_traits<U *>::reference			reference;
	typedef Node<typename ft::remove_const<value_type>::type>*	node_pointer;

	typedef typename std::bidirectional_iterator_tag			iterator_category;

private:

	node_pointer current;
	node_pointer TNULL;
	node_pointer root;

	node_pointer minimum(node_pointer node)
	{
		while (node->left != TNULL)
			node = node->left;
		return node;
	}

	node_pointer maximum(node_pointer node)
	{
		while (node->right != TNULL)
			node = node->right;
		return node;
	}

	node_pointer successor(node_pointer x)
	{
		if (x->right != TNULL)
			return minimum(x->right);

		node_pointer y = x->parent;
		while (y != NULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	node_pointer precedent(node_pointer x)
	{
		if (x->left != TNULL)
			return maximum(x->left);

		node_pointer y = x->parent;
		while (y != TNULL && y != NULL &&x == y->left)
		{
			x = y;
			y = y->parent;
		}

		return y;
	}

public:

	//==============     Constructors          ==============

	tree_iterator() : current(nullptr), TNULL(nullptr) {}
	tree_iterator(node_pointer cur, node_pointer tnull) : current(cur), TNULL(tnull) {}
	tree_iterator(node_pointer cur, node_pointer tnull, node_pointer rout) : current(cur), TNULL(tnull), root(rout) {}
	tree_iterator(node_pointer cur) : current(nullptr), TNULL(cur) {}

	tree_iterator(const tree_iterator<typename ft::remove_const<value_type>::type> &ref) {
		*this = ref;
	}


	~tree_iterator() {}

	tree_iterator &operator=(const tree_iterator<typename remove_const<value_type>::type> &ref)
	{
			this->current = ref.getCurrent();
			this->root = ref.getRoot();
			this->TNULL = ref.getTNULL();
		return *this;
	}

	//==============     Pointer like operations          ==============

	reference operator*() const
	{
		if (current == NULL)
			return (TNULL->data);
		return (current->data);
	}
	pointer operator->() const { return (&operator*()); }

	//==============     Increment / Decrement           ==============

	tree_iterator &operator++()
	{
		this->current = successor(this->current);
		return (*this);
	}

	tree_iterator operator++(int)
	{
		tree_iterator tmp(*this);
		++(*this);
		return (tmp);
	}

	tree_iterator &operator--()
	{
		if (current == TNULL)
		{
			current = maximum(this->root);
			return (*this);
		}
		current = precedent(current);
		return (*this);
	}

	tree_iterator operator--(int)
	{
		tree_iterator tmp(*this);
		--(*this);
		return (tmp);
	}

	//==============     Getters           ==============

	node_pointer getRoot() const { return this -> root; }
	node_pointer getCurrent() const { return this -> current; }
	node_pointer getTNULL() const { return this -> TNULL; }

};
//==============     Comparison operations           ==============

template < typename IteratorL, typename IteratorR>
bool operator==(const tree_iterator<IteratorL> & lhs, const tree_iterator<IteratorR> & rhs){ return &(*lhs) == &(*rhs); }

template < typename IteratorL, typename IteratorR>
bool operator!=(const tree_iterator<IteratorL> & lhs, const tree_iterator<IteratorR> & rhs){ return &(*lhs) != &(*rhs); }


//=================================================================
//==============           Reverse iterator          ==============
//=================================================================


template <class Iter>
class	reverse_iterator
{
protected:
    Iter current;
public:
	typedef typename ft::iterator_traits<Iter>::value_type			value_type;
	typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
    typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
    typedef typename ft::iterator_traits<Iter>::reference			reference;
    typedef typename ft::iterator_traits<Iter>::pointer				pointer;
	typedef Iter													iterator_type;

	//==============     Constructors          ==============

    reverse_iterator() : current() {}
    explicit reverse_iterator(Iter rhs) : current(rhs) {}
    template <class T>
        reverse_iterator(const reverse_iterator<T>& rhs) : current(rhs.base()) {}
    template <class T>
        reverse_iterator& operator=(const reverse_iterator<T>& rhs)
            { current = rhs.base(); return *this; }
    Iter base() const {return current;}

	//==============     Pointer like operations          ==============

    reference operator*() const {Iter tmp = current; return *--tmp;}
    pointer  operator->() const {return std::addressof(operator*());}

	//==============     Increment / Decrement           ==============

    reverse_iterator& operator++() {--current; return *this;}
    reverse_iterator  operator++(int) {reverse_iterator tmp(*this); --current; return tmp;}
    reverse_iterator& operator--() {++current; return *this;}
    reverse_iterator  operator--(int) {reverse_iterator tmp(*this); ++current; return tmp;}

	//==============     Arithmetic operations           ==============

    reverse_iterator  operator+ (difference_type n) const {return reverse_iterator(current - n);}
    reverse_iterator& operator+=(difference_type n) {current -= n; return *this;}
    reverse_iterator  operator- (difference_type n) const {return reverse_iterator(current + n);}
    reverse_iterator& operator-=(difference_type n) {current += n; return *this;}
    reference         operator[](difference_type n) const {return *(*this + n);}
};

//==============     Comparison operations           ==============

template <class IteratorL, class IteratorR>
bool operator==(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs) { return lhs.base() == rhs.base(); }

template <class IteratorL, class IteratorR>
bool
operator<(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs) { return lhs.base() > rhs.base(); }

template <class IteratorL, class IteratorR>
bool operator!=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs) { return lhs.base() != rhs.base(); }

template <class IteratorL, class IteratorR>
bool operator>(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs){ return lhs.base() < rhs.base(); }

template <class IteratorL, class IteratorR> bool operator>=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <class IteratorL, class IteratorR>
bool
operator<=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{
    return lhs.base() >= rhs.base();
}

//==============     Arithmetic operations           ==============

template <class IteratorL, class IteratorR>
typename reverse_iterator<IteratorL>::difference_type
operator-(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
{
    return rhs.base() - lhs.base();
}

template <class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& lhs)
{
    return reverse_iterator<Iter>(lhs.base() - n);
}

template <class Iter>
reverse_iterator<Iter> make_reverse_iterator(Iter i)
{
    return reverse_iterator<Iter>(i);
}

};
