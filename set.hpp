#ifndef SET_HPP
# define SET_HPP
# include "utils.hpp"
# include "rbtree.hpp"
# include <functional>  // std::less
# include <memory>      // std::allocator

namespace ft
{
    template < class T,
           class Compare = std::less<T>,
           class Alloc = std::allocator<T> >
    class set
    {
        public:
            typedef T																				key_type;
            typedef T																				value_type;
            typedef Compare                                         								key_compare;
			typedef Compare                                         								value_compare;
            typedef Alloc                                           								allocator_type;
            typedef typename allocator_type::reference              								reference;
            typedef typename allocator_type::const_reference        								const_reference;
            typedef typename allocator_type::pointer                								pointer;
            typedef typename allocator_type::const_pointer          								const_pointer;

            typedef size_t                                         									size_type;
			typedef std::ptrdiff_t 																	difference_type;
        	typedef rbtree<value_type, value_compare, allocator_type>								tree_type;

			typedef typename tree_type::iterator													iterator;
        	typedef typename tree_type::const_iterator												const_iterator;
			typedef typename tree_type::reverse_iterator											reverse_iterator;
        	typedef typename tree_type::const_reverse_iterator										const_reverse_iterator;

        private:
            rbtree<value_type, value_compare, allocator_type> tree;

        public:

			//==============     CONSTRUCTORS         ==============

            explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			tree(tree_type(comp, alloc)){}

    		template< class InputIt >
    		set(InputIt first, InputIt last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
            : tree(tree_type(first, last, comp, alloc)) {}

    		set(const set& other){ *this= other; }

    		set& operator=(const set& other) {
    			this->tree = other.tree;
    			return *this;
    		}

			~set() {}

			//==============     ITERATORS         ==============

            iterator begin() { return tree.begin(); }

    		const_iterator begin() const { return tree.begin(); }

    		iterator end(){ return tree.end(); }

    		const_iterator end() const { return tree.end(); }

    		reverse_iterator rbegin() { return tree.rbegin(); }

    		const_reverse_iterator rbegin() const { return tree.rbegin(); }

    		reverse_iterator rend() { return tree.rend(); }

    		const_reverse_iterator rend() const { return tree.rend(); }

			//==============     CAPACITY        ==============

            bool empty() const { return(tree.empty()); }

            size_type size() const { return(tree.size()); }

            size_type max_size() const { return(tree.max_size()); }

			//==============     FUNCTIONS        ==============

            template <class InputIterator>
            void insert (typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type first,InputIterator last)
            {
                tree.insert_val(first, last);
            }

            iterator insert (iterator position, const value_type& val)
            {
                return tree.insert_val(position, val);
            }

            ft::pair<iterator,bool> insert (const value_type& val)
            {
                return tree.insert_val(val);
            }

            void erase (iterator position)
            {
                tree.deleteNodeHelper(position.getCurrent()->data);
            }

            size_type erase (const key_type& k)
            {

                iterator iter = find(k);
                if(iter != end())
                {
                    erase(iter);
                    return(1);
                }
                return(0);
            }

            void erase (iterator first, iterator last)
            {
                while(first != last)
                {
                    erase (first);
                    first++;
                }
            }

            void swap (set& x) { tree.swap(x.tree); }

            void clear() { tree.clear(); }

            value_compare value_comp() const { return tree.value_comp(); }

		    key_compare key_comp() const { return value_comp(); }

            iterator find (const key_type& k) { return tree.find(k); }

            const_iterator find (const key_type& k) const { return tree.find(k); }

		    size_type count (const key_type& k) const { return (find(k) != end() ? 1 : 0); }  //  TO-DO

			allocator_type get_allocator() const { return tree.get_allocator(); }

			//==============     BOUNDS           ==============

            iterator lower_bound (const key_type& k) { return tree.lower_bound(k); }

            const_iterator lower_bound (const key_type& k) const { return tree.lower_bound(k); }

            iterator upper_bound (const key_type& k) { return tree.upper_bound(k); }

            const_iterator upper_bound (const key_type& k) const { return tree.upper_bound(k); }

            pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return tree.equal_range(k); }

            pair<iterator,iterator>             equal_range (const key_type& k) { return tree.equal_range(k); }



			// void printTree(){
			// 	this -> tree.printHelper(this -> tree.getRoot(), "", true);
			// }

			//==============     Comparison operations           ==============
			template< class K, class Comp, class All >
			friend bool operator==( const ft::set<K,Comp,All>& lhs, const ft::set<K,Comp,All>& rhs );
			template< class K, class Comp, class All >
			friend bool operator<( const ft::set<K,Comp,All>& lhs, const ft::set<K,Comp,All>& rhs );
    };

	//==============     Comparison operations           ==============

	template< class T, class Compare, class Alloc >
	bool operator==( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ){
		return lhs.tree == rhs.tree;
	}

	template< class T, class Compare, class Alloc >
	bool operator!=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ){
		return !(lhs == rhs);
	}

	template< class T, class Compare, class Alloc >
	bool operator<( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ){
		return lhs.tree < rhs.tree;
	}

	template< class T, class Compare, class Alloc >
	bool operator<=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ){
		return !(rhs < lhs);
	}

	template< class T, class Compare, class Alloc >
	bool operator>( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ){
		return rhs < lhs;
	}

	template< class T, class Compare, class Alloc >
	bool operator>=( const ft::set<T,Compare,Alloc>& lhs, const ft::set<T,Compare,Alloc>& rhs ){
		return !(lhs < rhs);
	}
}

#endif
