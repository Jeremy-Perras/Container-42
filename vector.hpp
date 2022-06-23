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

            vector (const vector& x) : _alloc(x._alloc), _size(x._size),_capactiy(x._capacity)
            {
              this->_vector = _alloc.allocate(this->capacity);
                return;
            }

            ~vector()
            {
              for(iterator it = begin(); it != end(); i++)
                _alloc.destroy(&(*it));
              _alloc.deallocate(_vector, _capacity);
            }

            vector& operator=(vector const &rhs)
            {
                if(this == &rhs)
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
                return (const_iterator(_vector + this->_size));
            }
            const_iterator end() const
            {
                return (const_iterator(_vector + this->_size));
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
                if(n > this->_capacity)
                    reserve(n);
                if(n >= this->size)
                {
                  for(size_type i = this->size ; i < n ; i++)
                    _alloc.construct(this->_vector, val)
                }
                else
                {
                  for(size_type i = n; i < _size ; i++)
                    _alloc.destroy(this->_vector + i)
                    this->_capacity = n;
                }
                this->_size = n;
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
              if(n > max_size())
              {
                throw(std::length_error("ft::vector::reserve"))
              }
              else if(n > this->_capacity)
              {
                pointer tmp = _alloc.allocate(n);
                for(size_type i = 0; i < this->_size; i++)
                  _alloc.construct(tmp + i ,*(this->_vector + i));
                _alloc.deallocate(this->_vector, this->_capacity);
                this->vector = tmp;
                this->capacity = n;
              }
            }
            // Element access:
            reference operator[] (size_type n)
            {
                return (*(this->_vector + n));
            }

            const_reference operator[] (size_type n) const
            {
                return (*(this->_vector + n));
            }

            reference at (size_type n)
            {
              if (n >= size())
                throw (std::out_of_range("ft::vector::at"));
              else
                return (*(this->_vector + n));
            }
            const_reference at (size_type n) const
            {
              if (n >= size())
                throw (std::out_of_range("ft::vector::at"));
              else
                return (*(this->_vector + n));
            }

            reference front()
            {
                return (*begin());
            }

            const_reference front() const
            {
                return (*begin()); //this->_vector[0]
            }

            reference back()
            {
                return(*(end() - 1));
            }

            const_reference back() const
            {
                return(*(end() - 1));
            }
            // Modifiers:
            template <class InputIterator>
            void assign (InputIterator first, InputIterator last)
            {

            }

            void assign (size_type n, const value_type& val)
            {
                clear();
                if(n == 0)
                    return ;
                if (n >= this->_capacity)
                {
                    _alloc.deallocate(this->_vector, this->_capacity)
                    this->_vector = _alloc.allocate(n);
                    _capacity = n;
                }
                for(size_t i = 0; i < n ; i++)
                    _alloc.construct(this->_vector + i, val)
                this->_size = n;
            }
            void push_back (const value_type& val)
            {
                if(this->_size == this->_capacity)
                    empty() ? reserve(1) : reserve(this->_size * 2);
                _alloc.construct(this->_vector + size, val)
                this->_size = this->_size + 1;
            }

            void pop_back()
            {
                if(size > 0)
                {
                    this->_size = this->_size - 1;
                    _alloc.destroy(this->_vector + this->_size);
                }
            }

            iterator insert (iterator position, const value_type& val)
            {
                int i;
                while(size_t i = 0, i != psition; i++)

                return ();

            }

            void insert (iterator position, size_type n, const value_type& val)
            {


            }

            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last)
            {


            }

            iterator erase (iterator position)
            {
                if(empty())
                    return(end());
                iterator it = begin();
                while(it != position)
                    it++;
                this->_alloc.destroy(it);
                while(it + 1 != end())
                {
                    _alloc.construct(it, * (it + 1) );
                    it++;
                }
                pop_back();
                return(position);
            }

            iterator erase (iterator first, iterator last)
            {
                if(empty())
                    return(end());
                iterator it = begin();
                while(it != first)
                    it++;
                while(it != last)
                {
                    this->_alloc.destroy(it);
                    this->_size = this->_size - 1;
                    pop_back();
                    it++;
                }
                while(it + 1 != end())
                    _alloc.construct(it, * (it + 1) );
                pop_back();
                return(position);

            }

            void swap (vector& x)
            {

            }

            void clear()
            {
                while(this->_size)
                    pop_back();
            }
                // Allocator:
                allocator_type get_allocator() const
                {

                }

    }
};
//Non-member function overloads
template <class T, class Alloc>
  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return(x.size() == y.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
  }
template <class T, class Alloc>
 bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
 {
     return (!(lhs == rhs));
 }
template <class T, class Alloc>
  bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
  }
template <class T, class Alloc>
  bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return (!(rhs < lhs));
  }
template <class T, class Alloc>
  bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return (rhs < lhs);
  }
template <class T, class Alloc>
  bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return (!(lhs < rhs));
  }
//swap
template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
#endif
