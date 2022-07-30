#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include "utils.hpp"
#include "iterators.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
        public:

            typedef	T 													value_type;
    		typedef Allocator											allocator_type;
    		typedef std::size_t											size_type;
    		typedef std::ptrdiff_t										difference_type;
    		typedef value_type&											reference;
    		typedef const value_type&									const_reference;
    		typedef typename Allocator::pointer							pointer;
    		typedef typename Allocator::const_pointer					const_pointer;

    		typedef ft::my_iter<value_type>								iterator;
    		typedef ft::my_iter<const value_type>						const_iterator;
    		typedef ft::reverse_iterator<iterator>						reverse_iterator;
    		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

        private:

            void move_backward(iterator position, size_type n = 1)
            {
              if (position == end()) return ;
                move_backward(position + 1, n);
              _alloc.construct(&(*(position + n)), *position);
            }
            Allocator    _alloc;
            pointer     _vector;
            size_type   _size;
            size_type   _capacity;

        public:

		//==============     Constructors          ==============

            explicit vector (const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _size(0), _capacity(0)
            {
                _vector = _alloc.allocate(_capacity);
                return ;
            }

            explicit vector (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type())
                : _alloc(alloc), _size(n), _capacity(n)
            {
                _vector = _alloc.allocate(_capacity);
                for(size_type i = 0 ;  i < n ; i++)
                    _alloc.construct(_vector + i, val);
                return;
            }

            template <class InputIterator>
            vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
                    const allocator_type& alloc = allocator_type())
                    : _alloc(alloc), _size(0)
            {
                difference_type n = last - first;
                this->_capacity = n;
				this -> _size = n;
                this->_vector = _alloc.allocate(n);
                for (int i = 0; first != last; i++)
                {
                    _alloc.construct(this->_vector + i, *first);
                    first++;
                }
                return ;
            }

            vector (const vector &x) : _size(0),_capacity(0){ *this = x; }

            ~vector()
            {
              for (iterator it = begin(); it != end(); it++)
                _alloc.destroy(&(*it));
              _alloc.deallocate(_vector, _capacity);
            }

			vector& operator=(const vector &x)
            {
			if (this == &x)
				return *this;
			clear();
			reserve(x.capacity());
			this->_size = x._size;
			for (size_type i = 0; i < this->_size; i++)
				this->_alloc.construct(this->_vector + i, x[i]);
			return *this;
            }

			// vector& operator=(const vector &x)
            // {
			// if (this == &x)
			// 	return *this;
			// clear();
			// this->_size = x._size;
			// if (this->_capacity < this->_size) {
			// 	if (this->_capacity)
			// 		this->_alloc.deallocate(this->_vector, this->_capacity);
			// 	this->_capacity = this->_size;
			// 	this->_vector = this->_alloc.allocate(this->_capacity);
			// }
			// for (size_type i = 0; i < this->_size; i++)
			// 	this->_alloc.construct(this->_vector + i, x[i]);
			// return *this;
            // }

			//==============     Iterators            ==============

			iterator begin() { return iterator(this -> _vector); }

			const_iterator begin() const {return const_iterator(this -> _vector); }

			iterator end() { return iterator( this -> _vector + _size); }

			const_iterator end() const { return const_iterator(this -> _vector + this -> _size); }

			reverse_iterator rbegin() { return reverse_iterator(end()); }

			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

			reverse_iterator rend() { return reverse_iterator(begin()); }

			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

			//==============     Capacity             ==============

            size_type size() const { return (this->_size); }

            size_type max_size() const { return(this->_alloc.max_size()); }

			size_type capacity() const { return (this->_capacity); }

            bool empty() const { return (this->_size == 0); }

            void resize (size_type n, value_type val = value_type())
            {
                if(n > this->_capacity)
                    reserve(n);
                if(n >= this->size)
                {
                  for(size_type i = this->size ; i < n ; i++)
                    _alloc.construct(this->_vector, val);
                }
                else
                {
                  for(size_type i = n; i < this->_size ; i++)
                    _alloc.destroy(this->_vector + i);
                    this->_capacity = n;
                }
                this->_size = n;
            }

			// void reserve (size_type n)
            // {
            //   if(n > max_size())
            //   {
            //     throw(std::length_error("ft::vector::reserve"));
            //   }
            //   else if(n > this->_capacity)
            //   {
            //     pointer tmp = _alloc.allocate(n);
            //     for(size_type i = 0; i < this->_size; i++)
            //       _alloc.construct(tmp + i ,*(this->_vector + i));
            //     _alloc.deallocate(this->_vector, this->_capacity);
            //     this->_vector = tmp;
            //     this->_capacity = n;
            //   }
            // }

            void reserve (size_type n)
            {
              if(n > max_size())
              {
                throw(std::length_error("ft::vector::reserve"));
              }
              else if(n > this->_capacity)
              {
				pointer tmp = _alloc.allocate(n);
				size_type i = 0;
				try{
					std::uninitialized_copy(_vector, _vector + _size, tmp);
				} catch (...){
					_alloc.deallocate(tmp, n);
					throw;
				}
				for (size_type i = 0; i < this -> _size; ++i){
					_alloc.destroy(_vector + i);
				}	
				if (this -> _capacity)		
					_alloc.deallocate(_vector, this -> _capacity);

                this->_vector = tmp;
                this->_capacity = n;
              }
            }

			//==============     Element access             ==============
            
			reference operator[] (size_type n) { return (*(this->_vector + n)); }

            const_reference operator[] (size_type n) const { return (*(this->_vector + n)); }

	        reference front() { return (*begin()); }

            const_reference front() const { return (*begin()); }

            reference back() { return(*(end() - 1)); }

            const_reference back() const { return(*(end() - 1)); }

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


			//==============     Modifiers             ==============     

			template <class InputIterator>
            void assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
            {
                clear();
                size_type n = last - first;
                if (n == 0)
                    return;
                if (n > this->_capacity)
                {
                    _alloc.deallocate(this->_vector, this->_capacity);
                    this->_vector = _alloc.allocate(n);
                    this->_capacity = n;
                }
                for(size_type i = 0; first != last; i++)
                    _alloc.construct(this->_vector + i, *first);
                this->_size = static_cast<size_type>(last - first);
            }

            void assign (size_type n, const value_type& val)
            {
                clear();
                if(n == 0)
                    return ;
                if (n >= this->_capacity)
                {
                    this->_alloc.deallocate(this->_vector, this->_capacity);
                    this->_vector = _alloc.allocate(n);
                    this->_capacity = n;
                }
                for(size_t i = 0; i < n ; i++)
                    _alloc.construct(this->_vector + i, val);
                this->_size = n;
            }

            void push_back (const value_type& val)
            {
                if(this->_size == this->_capacity)
                    empty() ? reserve(1) : reserve(this->_size * 2);
                _alloc.construct(this->_vector + this->_size, val);
                ++(this->_size);
            }

            void pop_back()
            {
                if(_size > 0)
                    _alloc.destroy(this->_vector + --(this->_size));
            }

			void clear() {
                while(this->_size)
                    pop_back();
            }


            iterator insert(iterator position, const value_type& val) {
              size_type idx = position - begin();
              reserve(_size + 1);
              position = begin() + idx;
              move_backward(position);
              _alloc.construct(&(*position), val);
              _size++;
              return (position);
            }

            void insert(iterator position, size_type n, const value_type& val) {
              size_type idx = position - begin();
              reserve(_size + n);
              position = begin() + idx;
              move_backward(position, n);
              for (size_type i = 0; i < n; i++)
                _alloc.construct(&(*(position + i)), val);
              _size += n;
            }

            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last,
              typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr) {
                size_type idx = position - begin();
                size_type n = last - first;
                reserve(_size + n);
                position = begin() + idx;
                move_backward(position, n);
                for (size_type i = 0; i < n; i++)
                  _alloc.construct(&(*(position + i)), *(first + i));
                _size += n;
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
                return(first);
            }

            void swap (vector& x)
            {
				std::swap(this -> _alloc, x._alloc);
				std::swap(this -> _vector, x._vector);
				std::swap(this -> _capacity, x._capacity);
				std::swap(this -> _size, x._size);
            }

            allocator_type get_allocator() const { return (Alloc(_alloc)); }
};

//==============     Non member dunctions  ==============

template <class T, class Alloc>
  bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
  {
      return(lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
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

////==============     SWAP       ==============

template <class T, class Alloc>
  void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
  {
    x.swap(y);
  }
}
#endif
