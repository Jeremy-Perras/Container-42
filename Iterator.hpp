# ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
    // Iterator Tags
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};
    // iterator class
    template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
    typename _Pointer = _Tp*, typename _Reference = _Tp&>
    class iterator
    {
        public :
          /// One of the @link iterator_tags tag types@endlink.
          typedef _Category  iterator_category;
          /// The type "pointed to" by the iterator.
          typedef _Tp        value_type;
          /// Distance between iterators is represented as this type.
          typedef _Distance  difference_type;
          /// This type represents a pointer-to-value_type.
          typedef _Pointer   pointer;
          /// This type represents a reference-to-value_type.
          typedef _Reference reference;
    };

    template<typename _Iterator>
    class iterator_traits
    {
        public:
            typedef typename _Iterator::iterator_category iterator_category;
            typedef typename _Iterator::value_type        value_type;
            typedef typename _Iterator::difference_type   difference_type;
            typedef typename _Iterator::pointer           pointer;
            typedef typename _Iterator::reference         reference;
    };

    template<typename _Tp>
    class iterator_traits<_Tp*>
    {
    public:
        typedef random_access_iterator_tag iterator_category;
        typedef _Tp                         value_type;
        typedef ptrdiff_t                   difference_type;
        typedef _Tp*                        pointer;
        typedef _Tp&                        reference;
    };

    template<typename _Tp>
    class iterator_traits<const _Tp*>
    {
    public:
        typedef random_access_iterator_tag iterator_category;
        typedef _Tp                         value_type;
        typedef ptrdiff_t                   difference_type;
        typedef const _Tp*                  pointer;
        typedef const _Tp&                  reference;
    };

    template<typename Iterator>
    class reverse_iterator
    {
        protected:
            Iterator _current;

        public:
            typedef Iterator iterator_type;
            typedef typename iterator_traits<Iterator>::difference_type
                                    difference_type;
           typedef typename iterator_traits<Iterator>::reference   reference;
           typedef typename iterator_traits<Iterator>::pointer     pointer;
           reverse_iterator() : _current(nullptr){}
           explicit reverse_iterator(iterator_type it) : _current(it){}
           reverse_iterator(const reverse_iterator& it) : _current(it._current){}
           template<typename _Iter>
            reverse_iterator(const reverse_iterator<_Iter>& it): _current(it.base())
            {}
            iterator_type base() const {return this->_current;}

            reference operator*() const
            {
                iterator_type tmp(_current);
                return(*--tmp);
            }

            pointer operator->() const
            {
                return(&(operator*()));
            }

            reverse_iterator& operator++()
            {
                --_current;
                return(*this);
            }

            reverse_iterator& operator++(int)
            {
                reverse_iterator tmp = *this;
                --_current;
                return(tmp);
            }

            reverse_iterator& operator--()
            {
                ++_current;
                return(*this);
            }
            reverse_iterator operator--(int)
            {
                reverse_iterator tmp=*this;
                ++_current;
                return(tmp);
            }

            reverse_iterator operator+(difference_type n) const
            {
                return(reverse_iterator(_current - n));
            }
            reverse_iterator& operator+=(difference_type n)
            {
                _current -= n;
                return(*this);
            }

            reverse_iterator operator-(difference_type n) const
            {
                return reverse_iterator(_current + n);
            }
            reverse_iterator& operator-=(difference_type n)
            {
                _current += n;
                return(*this);
            }

            reference operator[](difference_type n) const
            {
                return *(*this + n);
            }
        };

            template <class Iterator1, class Iterator2>
            bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
            {
                return (lhs.base() == rhs.base());
            }
            template <class Iterator1, class Iterator2>
            bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
            {
                return (lhs.base() != rhs.base());
            }
            template <class Iterator1, class Iterator2>
            bool operator< (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
            {
                return (lhs.base() > rhs.base());
             }
            template <class Iterator1, class Iterator2>
            bool operator> (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
            {
                return (lhs.base() < rhs.base());
            }
            template <class Iterator1, class Iterator2>
            bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
            {
                return (lhs.base() >= rhs.base());
            }
            template <class Iterator1, class Iterator2>
            bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
            {
                return (lhs.base() <= rhs.base());
            }

            template <class Iterator>
            reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
            {
              return (rev_it + n);
            }

            template <class Iterator1, class Iterator2>
            typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
            {
              return (rhs.base() - lhs.base());
            }

            //Random access iterator :

            template <typename T>
            class random_access_iterator : public iterator<random_access_iterator_tag, T>
            {
              public:
                  typedef typename iterator<random_access_iterator_tag, T>::value_type          value_type;
                  typedef typename iterator<random_access_iterator_tag, T>::difference_type     difference_type;
                  typedef typename iterator<random_access_iterator_tag, T>::pointer             pointer;
                  typedef typename iterator<random_access_iterator_tag, T>::reference           reference;
                  typedef typename iterator<random_access_iterator_tag, T>::iterator_category   iterator_category;

              protected:
              pointer _current;

              public:
                  random_access_iterator(void)                                 : _current(nullptr) {}
                  random_access_iterator(pointer ptr)                          : _current(ptr) {}
                  random_access_iterator(const random_access_iterator<T>& ref) : _current(ref._current) {}

                  operator random_access_iterator<const value_type>() const {
                    return random_access_iterator<const value_type>(_current);
                  }

                  random_access_iterator& operator=(const random_access_iterator& ref)
                  {
                    if (this != &ref)
                      _current = ref._current;
                    return (*this);
                  }

                  virtual ~random_access_iterator() {}

                  pointer base(void) const
                  {
                      return (_current);
                  }

                  reference operator* (void) const
                  {
                      return (*_current);
                  }
                  pointer   operator->(void) const
                  {
                      return (&(operator*()));
                  }
                  reference operator[](difference_type n) const
                  {
                      return (_current[n]);
                  }

                  random_access_iterator operator+(difference_type n) const
                  {
                      return (_current + n);
                  }
                  random_access_iterator operator-(difference_type n) const
                  {
                      return (_current - n);
                  }

                  random_access_iterator& operator++(void)
                  {
                    ++_current;
                    return (*this);
                  }
                  random_access_iterator operator++(int)
                  {
                    random_access_iterator tmp(*this);
                    _current++;
                    return (tmp);
                  }
                  random_access_iterator& operator--(void)
                  {
                    --_current;
                    return (*this);
                  }
                  random_access_iterator operator--(int)
                  {
                    random_access_iterator tmp(*this);
                    _current--;
                    return (tmp);
                  }

                  random_access_iterator& operator+=(difference_type n)
                  {
                    _current += n;
                    return (*this);
                  }
                  random_access_iterator& operator-=(difference_type n)
                  {
                    _current -= n;
                    return (*this);
                  }
                };

            template <typename T1, typename T2>
            bool operator==(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
            {
                return (lhs.base() == rhs.base());
            }
            template <typename T1, typename T2>
            bool operator!=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
            {
                return (lhs.base() != rhs.base());
            }
            template <typename T1, typename T2>
            bool operator< (const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
            {
                return (lhs.base() < rhs.base());
            }
            template <typename T1, typename T2>
            bool operator> (const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
            {
                return (lhs.base() > rhs.base());
            }
            template <typename T1, typename T2>
            bool operator<=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
            {
                return (lhs.base() <= rhs.base());
            }
            template <typename T1, typename T2>
            bool operator>=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
            {
                return (lhs.base() >= rhs.base());
            }

            template <typename T>
            random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& rev_it)
            {
              return (rev_it + n);
            }

            template <typename T1, typename T2>
            typename random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs)
            {
              return (lhs.base() - rhs.base());
            }

}

#endif
