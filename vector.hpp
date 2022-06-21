#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
    template < class T, class Alloc = allocator<T> >
    class vector
    {
        public:
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;

        private:
            pointer _vector;
            size_type _size;
            size_type _capacity;
            Alloc _alloc;
        public:
            //Member functions
                //Constructors / Destructors
            explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0)
            {
                _vector = _alloc.allocate(_capacity);
                return ;
            }
            explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capactity(n)
            {
                _vector = _alloc.allocate(_capacity);
                for(int i = 0 ;  i < n ; i++)
                    _vector[i] = val;
                return;
            }

            template <class InputIterator>
            vector (InputIterator first, InputIterator last,
                    const allocator_type& alloc = allocator_type()) : _alloc(alloc), _capacity(last - first), _size(last - first)
            {
                _vector = _alloc.allocate(_capacity);
                for(int i = first; i < ; i++)
                    _vector[i] =

                return;
            }
            vector (const vector& x)
            {
                return;
            }
            ~vector();
            vector& operator=(vector const &rhs);
                // Iterators:
                // Capacity:
                // Element access:
                // Modifiers:
                // Allocator:


        private:




    }
}
//Non-member function overloads
//swap
#endif
