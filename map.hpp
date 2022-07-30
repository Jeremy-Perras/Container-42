#ifndef MAP_HPP
# define MAP_HPP
# include "utils.hpp"
# include "rbtree.hpp"
# include <functional>
# include <memory>

namespace ft
{
    template < class Key,
           class T,
           class Compare = std::less<Key>,
           class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map
    {
        public:
            typedef Key																key_type;
            typedef T																mapped_type;
            typedef ft::pair<const key_type, mapped_type>							value_type;
            typedef Compare															key_compare;
            typedef Alloc															allocator_type;
            typedef typename allocator_type::template rebind<value_type>::other		type_allocator;
            typedef std::allocator_traits<type_allocator>							type_traits;
            typedef typename allocator_type::reference              				reference; // T&
            typedef typename allocator_type::const_reference						const_reference; //const t&
            typedef typename allocator_type::pointer								pointer; // T*
            typedef typename allocator_type::const_pointer							const_pointer; // const T*

            typedef size_t															size_type;
			typedef std::ptrdiff_t													difference_type;

        	class value_compare {
				key_compare cmp;

				public:
					value_compare(const key_compare & cmp) : cmp(cmp) {}
					bool operator()(const value_type& x, const value_type& y) const {
						return cmp(x.first, y.first);
					}
		    	};

			typedef rbtree<value_type, value_compare, allocator_type>				tree_type;
    		typedef typename tree_type::iterator									iterator;
        	typedef typename tree_type::const_iterator								const_iterator;
        	typedef typename tree_type::reverse_iterator							reverse_iterator;
    		typedef typename tree_type::const_reverse_iterator						const_reverse_iterator;

        private:
            rbtree<value_type, value_compare, allocator_type> tree;
            key_compare cmp;

        public:

			//==============     CONSTRUCTORS         ==============

            explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
			tree(tree_type(value_compare(comp), alloc)), cmp(comp){}

    		template< class InputIt >
    		map(InputIt first, InputIt last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
            : tree(tree_type(first, last, value_compare(comp), alloc)),cmp(comp) {}

    		map(const map& other): tree(other.tree), cmp(other.cmp) {}

    		map& operator=(const map& other) {
    			this->tree = other.tree;
    			this->cmp = other.cmp;
    			return *this;
    		}

            ~map() {}

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

            mapped_type& operator[] (const key_type& k)
            {
                return tree.insert_val(ft::make_pair(k, mapped_type())).first->second;
            }

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
                    ++first;
                }
            }

            void swap (map& x)
            {
                std::swap(this->cmp, x.cmp);
			    tree.swap(x.tree);
		    }

            void clear() { tree.clear(); }

            value_compare value_comp() const { return tree.value_comp(); }

		    key_compare key_comp() const { return cmp; }

            iterator find (const key_type& k) { return tree.find(ft::make_pair(k, mapped_type())); }

            const_iterator find (const key_type& k) const { return tree.find(ft::make_pair(k, mapped_type())); }

		    size_type count (const key_type& k) const { return (find(k) != end() ? 1 : 0) ;}

            allocator_type get_allocator() const { return tree.get_allocator(); }

			//==============     BOUNDS           ==============

            iterator lower_bound (const key_type& k) { return tree.lower_bound(ft::make_pair(k, mapped_type())); }

            const_iterator lower_bound (const key_type& k) const { return tree.lower_bound(ft::make_pair(k, mapped_type())); }

            iterator upper_bound (const key_type& k) { return tree.upper_bound(ft::make_pair(k, mapped_type())); }

            const_iterator upper_bound (const key_type& k) const { return tree.upper_bound(ft::make_pair(k, mapped_type())); }

            pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return tree.equal_range(ft::make_pair(k, mapped_type())); }

            pair<iterator,iterator>             equal_range (const key_type& k) { return tree.equal_range(ft::make_pair(k, mapped_type())); }


			void printTree(){
				this -> tree.printHelper(this -> tree.getRoot(), "", true);
			}

			//==============     Comparison operations           ==============

			template< class K, class Type, class Comp, class All >
			friend bool operator==( const ft::map<K, Type, Comp,All>& lhs, const ft::map<K, Type, Comp,All>& rhs );
			template< class K, class Type, class Comp, class All >
			friend bool operator<( const ft::map<K, Type, Comp,All>& lhs, const ft::map<K, Type, Comp,All>& rhs );

	};

	//==============     Comparison operations           ==============

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return lhs.tree == rhs.tree;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return lhs.tree < rhs.tree;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
		return !(lhs < rhs);
	}
}

#endif
