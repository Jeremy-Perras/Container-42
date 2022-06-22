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
            typedef size_t   size_type;
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
            explicit vector (const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _size(0), _capacity(0)
            {
                _vector = _alloc.allocate(_capacity);
                return ;
            }

            explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type())
                : _alloc(alloc), _size(n), _capactity(n)
            {
                _vector = _alloc.allocate(_capacity);
                for(size_type i = 0 ;  i < n ; i++)
                    _alloc.construc(_vector + i, val);
                return;
            }

            template <class InputIterator>
            vector (InputIterator first, InputIterator last,
                    const allocator_type& alloc = allocator_type())
                    : _alloc(alloc), _size(0)
            {
                _vector = _alloc.allocate(_capacity);
                for(size_t i = first; i < ; i++)
                    _vector[i] =

                return;
            }
            vector (const vector& x)
            {
                return;
            }
            ~vector();
            vector& operator=(vector const &rhs)
            {
                if(this = &rhs)
                    return (*this);


            }
            // Iterators:
            iterator begin()
            {
                return (iterator (_vector));
            }
            const_iterator begin() const
            {
                return (iterator(_vector));
            }
            iterator end()
            {
                return (const_iterator(_vector + size));
            }
            const_iterator end() const
            {
                return (const_iterator(_vector + size));
            };
            reverse_iterator rbegin()
            {
                    return (const_reverse_iterator(end()));
            }
            const_reverse_iterator rbegin() const
            {
                return (const_reverse_iterator(end()));
            }
            reverse_iterator rend()
            {
                return (reverse_iterator(begin()));
            }
            const_reverse_iterator rend() const
            {
                return (const_reverse_iterator(begin()));
            }
            // Capacity:
            size_type size() const
            {
                return (this->_size)
            }
            size_type max_size() const
            {
                return(_alloc.maxsize())
            }
            void resize (size_type n, value_type val = value_type())
            {
                if(n < this->_size)
                    eras;
                else
            }
            size_type capacity() const
            {
                return (this->_capacity);
            }
            bool empty() const
            {
                return (this->_size == 0);
            }
            void reserve (size_type n)
            {
                if(this->_capacity < n)
                {
                    _alloc.destroy(_vector);
                    _alloc.deallocate(_vector);
                    _alloc.allocate(n);
                    _alloc.construct();
                }
            }
            // Element access:
            reference operator[] (size_type n)
            {
                return ( this->_vector + n);
            }
            const_reference operator[] (size_type n) const
            {
                return ( this->_vector + n);
            }
            reference at (size_type n)
            {
                return ( *(this->_vector + n));
            }
            const_reference at (size_type n) const
            {
                return( *(this->_vector + n));
            }
            reference front()
            {
                return ( );
            }
            const_reference front() const
            {
                return ( );
            }
            reference back()
            {
                return( );
            }
            const_reference back() const
            {
                return( );
            }
            // Modifiers:
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {

            }
            void assign (size_type n, const value_type& val)
            {
                
            }
            void push_back (const value_type& val);
            void pop_back();
            iterator insert (iterator position, const value_type& val);
            void insert (iterator position, size_type n, const value_type& val);
            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last);
            iterator erase (iterator position);
            iterator erase (iterator first, iterator last);
            void swap (vector& x);
            void clear();


                // Allocator:
                allocator_type get_allocator() const;

    }
};
//Non-member function overloads
template <class T, class Alloc>
  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>

template <class T, class Alloc>
  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
//swap
template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
#endif
