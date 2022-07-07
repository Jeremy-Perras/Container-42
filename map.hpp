#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"

namespace ft
{
    template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator<pair<const Key,T> >    // map::allocator_type
    class map
    {
        public:
            typedef Key                                             key_type;
            typedef T                                               mapped_type;
            typedef ft::pair<const key_type, mapped_type>           value_type;
            typedef Compare                                         key_compare;
            typedef Alloc                                           allocator_type;
            typedef typename allocator_type::template rebind<value_type>::other   type_allocator;
            typedef std::allocator_traits<type_allocator>                         type_traits;
            typedef typename allocator_type::reference              reference; // T&
            typedef typename allocator_type::const_reference        const_reference; //const t&
            typedef typename allocator_type::pointer                pointer; // T*
            typedef typename allocator_type::const_pointer          const_pointer; // const T*
            typedef typename rbtree<value_type, key_type, value_compare, allocator_type>::iterator           iterator;
            typedef typename rbtree<value_type, key_type, value_compare, allocator_type>::const_iterator  const_iterator;
            typedef ft::reverse_iterator<iterator>                  reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
            typedef iterator_traits<iterator>::difference_type      difference_type;
            typedef size_t                                          size_type;

            class value_compare : public std::binary_function<value_type, value_type, bool> {
              protected:
              key_compare comp;

              public:
              value_compare(key_compare c) : comp(c) {}
              ~value_compare() {}

              bool operator()(const value_type& x, const value_type& y) const {
                return (comp(x.first, y.first));
              }
              bool operator()(const value_type& x, const key_type& y) const {
                return (comp(x.first, y));
              }
              bool operator()(const key_type& x, const value_type& y) const {
                return (comp(x, y.first));
              }
            };
        private:
            key_compare     _key_comp;
            value_compare   _value_comp;
            rbtree<value_type, key_type, value_compare, allocator_type>   _tree;

        public :
            template <class InputIterator>
            map (InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type())
            {

            }

            map (const map& x)
            {

            }
            explicit map (const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            {

            }
            ~map()
            {

            }
            iterator begin()
            {

            }
            const_iterator begin() const
            {

            }
            iterator end()
            {

            }
            const_iterator end() const
            {

            }
            reverse_iterator rbegin()
            {

            }
            const_reverse_iterator rbegin() const
            {

            }
            reverse_iterator rend()
            {

            }
            const_reverse_iterator rend() const
            {

            }
            bool empty() const
            {

            }
            size_type size() const
            {

            }
            size_type max_size() const
            {

            }
            mapped_type& operator[] (const key_type& k)
            {

            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {

            }
            iterator insert (iterator position, const value_type& val)
            {

            }
            pair<iterator,bool> insert (const value_type& val)
            {

            }
            void erase (iterator position)
            {

            }
            size_type erase (const key_type& k)
            {

            }
            void erase (iterator first, iterator last)
            {

            }
            void swap (map& x)
            {

            }
            void clear()
            {

            }
            key_compare key_comp() const
            {

            }
            value_compare value_comp() const
            {

            }
            iterator find (const key_type& k)
            {

            }
            const_iterator find (const key_type& k) const
            {

            }
            size_type count (const key_type& k) const
            {

            }
            iterator lower_bound (const key_type& k)
            {

            }
            const_iterator lower_bound (const key_type& k) const
            {

            }
            iterator upper_bound (const key_type& k)
            {

            }
            const_iterator upper_bound (const key_type& k) const
            {

            }
            pair<const_iterator,const_iterator> equal_range (const key_type& k) const
            {

            }
            pair<iterator,iterator>             equal_range (const key_type& k)
            {

            }
            allocator_type get_allocator() const
            {

            }




    };
}

#endif
