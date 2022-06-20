#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstddef>

namespace ft
{
    template < class T, class Alloc = allocator<T> >
    class vector
    {
    //Typedefs
        // typedef implementation-defined const_iterator;
        // typedef typename Allocator::const_pointer const_pointer;
        // typedef typename Allocator::const_reference const_reference;
        // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        // typedef typename Allocator::difference_type difference_type;
        // typedef implementation-defined iterator;
        // typedef typename Allocator::pointer pointer;
        // typedef typename Allocator::reference reference;
        // typedef std::reverse_iterator<iterator> reverse_iterator;
        // typedef typename Allocator::size_type size_type;
        // typedef typename Allocator::value_type value_type;

        public:
            //Member functions
                //Constructors / Destructors 
            explicit vector (const allocator_type& alloc = allocator_type());
            explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type());

            // template <class InputIterator>
            vector (InputIterator first, InputIterator last,
                    const allocator_type& alloc = allocator_type());
            vector (const vector& x);
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
