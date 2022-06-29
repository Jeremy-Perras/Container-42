#ifndef PAIR_HPP
# define PAIR_HPP


namespace ft
{
    template <class T1, class T2>
    struct pair
    {
            typedef T1 first_type;
            typedef T2 second_type;

            T1 first;
            T2 second;

            pair() : first(),second() {}
            pair(const T1 &a, const T2 &b) : first(a), second(b) {}
            template<class U, class V>
            pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
            pair& operator=(const pair &rhs)
            {
                if(this == &rhs)
                    return(*this);
                first = rhs.first;
                second = rhs.second;
                return(*this)
            }
        };
                template <class T1, class T2>
      bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
      {
          return(lhs.first == rhs.first && lhs.second == rhs.second);
      }

    template <class T1, class T2>
      bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
      {
          return!(lhs == rhs);
      }

    template <class T1, class T2>
      bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
      {
          return( lhs.first < rhs.first || !(rhs.first < lhs.first) && lhs.second < rhs.second);
      }

    template <class T1, class T2>
      bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
      {
          return(!(rhs < lhs));
      }

    template <class T1, class T2>
      bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
      {
          return(rhs < lhs);
      }

    template <class T1, class T2>
        bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
      {
          return(!(lhs < rhs));
      }

    template<class _T1, class _T2>
        inline pair<_T1, _T2> make_pair(_T1 __x, _T2 __y)
    {
        return pair<_T1, _T2>(__x, __y);
    }

}
#endif
