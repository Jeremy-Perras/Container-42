#pragma once

#include "iterators.hpp"
#include "utils.hpp"

namespace ft{

//=================================================================
//==============           Red Black Tree            ==============
//=================================================================

template <class Value, class Compare = std::less<Value>, class Alloc = std::allocator<Value> >
class rbtree{
	public:
		typedef	Value 															value_type;
		typedef Alloc															allocator_type;
		typedef Compare 														value_compare;
		typedef std::size_t														size_type;
		typedef std::ptrdiff_t													difference_type;
		typedef value_type&														reference;
		typedef const value_type&												const_reference;
		typedef typename Alloc::pointer											pointer;
		typedef typename Alloc::const_pointer									const_pointer;
		typedef typename Alloc::template rebind<Node<Value> >::other			node_allocator;
		typedef typename node_allocator::pointer								node_pointer;
			typedef Node<value_type>                                        		node_type;

		typedef tree_iterator<value_type>                        iterator;
		typedef tree_iterator<const value_type>                 const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
	private:
		node_pointer 		root;
  		node_pointer 		TNULL;
		allocator_type 		con_alloc;
		node_allocator 		node_alloc;
		value_compare 		cmp;
		size_type 			_size;

	public:

		//==============     CONSTRUCTORS         ==============

		rbtree() : root(0), con_alloc(allocator_type()), node_alloc(node_allocator()), cmp(value_compare()), _size(0)
		{
			init_tree();
			this->root = this->TNULL;
		}

		rbtree(const value_compare &comp, const allocator_type &alloc = allocator_type()) : root(0), con_alloc(alloc), node_alloc(node_allocator()), cmp(comp), _size(0)
		{
			init_tree();
			this->root = this->TNULL;
		}

		~rbtree() { }

		rbtree &operator=(rbtree const &rhs)
		{
			if (this == &rhs)
				return (*this);
			this->con_alloc = rhs.con_alloc;
			this->node_alloc = rhs.node_alloc;
			this->cmp = rhs.cmp;
			if (this -> root == NULL)
				init_tree();
			else 
			delete_all_node(this->root);
			if (rhs._size == 0)
				this->root = this->TNULL;
			else
			{
				this->root = copy_node(rhs.root);
				copy_branches(this->root, rhs.root);
			}
			this->_size = rhs._size;
			return (*this);
		}

		//==============     ITERATORS         ==============

		iterator begin() {
	      return (_size == 0 ? end() : iterator(minimum(this->root), TNULL, this->root));
	    }
	    const_iterator begin() const {
	      return (_size == 0 ? end() : const_iterator(minimum(this->root), TNULL, this->root));
	    }

	    iterator end() {
	      return (iterator(TNULL, TNULL, root));
	    }

	    const_iterator end() const {
	      return (const_iterator(TNULL, TNULL, root));
	    }

		reverse_iterator rbegin()
		{
		return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		//==============     CAPACITY        ==============

		bool empty() const { return this->_size == 0; }

		size_type size() const { return this->_size; }

		allocator_type get_allocator() const { return con_alloc; }

		size_type max_size() const { return con_alloc.max_size(); }

		//==============     BOUNDS           ==============

		iterator lower_bound( const_reference value ){
			iterator first = this -> begin();
			iterator last = this -> end();
			while ( first != last){
				if (!this -> cmp(*first, value))
					return first;
				++first;
			}
			return last;
		}

		const_iterator lower_bound( const_reference value ) const {
			const_iterator first = this -> begin();
			const_iterator last = this -> end();
			while ( first != last){
				if (!this -> cmp(*first, value))
					return first;
				++first;
			}
			return last;
		}

		iterator upper_bound( const_reference value ){
			iterator first = this -> begin();
			iterator last = this -> end();
			while ( first != last){
				if (this -> cmp(value, *first))
					return first;
				++first;
			}
			return last;
		}

		const_iterator upper_bound( const_reference value )const {
			const_iterator first = this -> begin();
			const_iterator last = this -> end();
			while ( first != last){
				if (this -> cmp(value, *first))
					return first;
				++first;
			}
			return last;
		}

		ft::pair<iterator, iterator> equal_range( const_reference value){
			return (ft::make_pair<iterator, iterator>(lower_bound(value), upper_bound(value)));
		}

		ft::pair<const_iterator, const_iterator> equal_range( const_reference value) const {
			return (ft::make_pair<const_iterator, const_iterator>(lower_bound(value), upper_bound(value)));
		}

		//==============     FUNCTIONS        ==============

		iterator find(const_reference value){
			return (search(value) ? iterator(search(value), this -> TNULL, this -> root) : this -> end());
		}

		const_iterator find(const_reference value) const {
			return (search(value) ? const_iterator(search(value), this -> TNULL, this -> root) : this -> end());
		}

		ft::pair<iterator, bool> insert_val( const_reference value){
			iterator tmp = this -> find(value);
			if (tmp != this -> end())
				return (ft::make_pair<iterator, bool>(tmp, false));
			this -> insert(value);
			return (ft::make_pair<iterator, bool>(this -> find(value), true));
		}

		iterator insert_val(iterator hint, const_reference value){
			(void)hint;

			return (insert_val(value).first);
		}

		template<class InputIt>
  		void insert_val(typename ft::enable_if< !ft::is_integral<InputIt>::value, InputIt >::type first, InputIt last)
  		{
	  		for (; first != last; ++first)
		  		insert(*first);
  		}

		void clear()
		{
			delete_all_node(this->root);

			this->root = this->TNULL;
			this->_size = 0;
		}

		void swap(rbtree & rhs){
			std::swap(this -> root, rhs.root);
			std::swap(this -> TNULL, rhs.TNULL);
			std::swap(this -> con_alloc, rhs.con_alloc);
			std::swap(this -> node_alloc, rhs.node_alloc);
			std::swap(this -> cmp, rhs.cmp);
			std::swap(this -> _size, rhs._size);
		}

		value_compare value_comp() const { return this->cmp; }

		// create a node
		node_pointer createNode(const value_type & data)
		{
			node_pointer node = node_alloc.allocate(1);
			node_alloc.construct(node, data);
			node->left = TNULL;
			node->right = TNULL;
			node->color = true;
			return (node);
		}


		node_pointer minimum(node_pointer node) const {
		while (node->left != TNULL)
    			node = node->left;
		return node;
		}


  node_pointer maximum(node_pointer node) const {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
  }

  node_pointer successor(node_pointer x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    node_pointer y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  node_pointer precedent(node_pointer x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    node_pointer y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(node_pointer x) {
    node_pointer y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(node_pointer x) {
    node_pointer y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }
	public :


  // For balancing the tree after insertion
  void insertFix(node_pointer k) {
    node_pointer u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }
  // Inserting a node
  void insert(const value_type & data) {

	node_pointer node = createNode(data);

	node_pointer y = nullptr;
    node_pointer x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }
	++(this -> _size);

    if (node->parent == nullptr) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr) {
      return;
    }

    insertFix(node);
  }



	private:

	node_pointer search(const_reference value){
		node_pointer node = this -> root;
		node_pointer z = TNULL;

		while (node != TNULL){
			if (!cmp(value, node -> data) && !cmp(node -> data, value))
				z = node;
			if (cmp(value, node -> data))
				node = node -> left;
			else
				node = node -> right;
		}
		if (z == TNULL)
			return NULL;
		return z;
	}
	void init_tree() {
		TNULL = node_alloc.allocate(1);
		node_alloc.construct( TNULL, value_type());
		TNULL -> color = 0;
		TNULL -> is_null = 1;
	}

	node_pointer copy_node(node_pointer rhs){
		node_pointer tmp = node_alloc.allocate(1);
		node_alloc.construct(tmp, Node<Value>());
		tmp -> color = rhs -> color;
		tmp -> is_null = rhs -> is_null;
		tmp -> data = rhs -> data;
		return tmp;
	}

	void copy_branches(node_pointer lhs, node_pointer rhs){
		if (rhs -> left -> is_null)
			lhs -> left = TNULL;
		else {
			lhs -> left = copy_node(rhs -> left);
			lhs -> left -> parent = lhs;
			copy_branches(lhs -> left, rhs -> left);
		}
		if (rhs -> right -> is_null)
			lhs -> right = TNULL;
		else {
			lhs -> right = copy_node(rhs -> right);
			lhs -> right -> parent = lhs;
			copy_branches(lhs -> right, rhs -> right);
		}
	}
	//delete
	void delete_node(node_pointer ptr)
	{
		node_alloc.destroy(ptr);
		node_alloc.deallocate(ptr, 1);
	}

	void delete_all_node(node_pointer ptr)
	{
	  if (ptr != TNULL)
	  {
		delete_all_node(ptr-> left);
		delete_all_node(ptr-> right);
		delete_node(ptr);
	  }
	}

	void rbTransplant(node_pointer u, node_pointer v) {
      if (u->parent == nullptr) {
        root = v;
      } else if (u == u->parent->left) {
        u->parent->left = v;
      } else {
        u->parent->right = v;
      }
      v->parent = u->parent;
    }


public:
	int deleteNodeHelper(const_reference value)
	{
		node_pointer x, y, z;

		z = search(value);
		if (!z)
			return 0;

		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL)
		{
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == TNULL)
		{
			x = z->left;
			rbTransplant(z, z->left);
		}
		else
		{
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete_node(z);
		--(this -> _size);
		if (y_original_color == 0)
		{
			deleteFix(x);
		}
		return 1;
	}

	// For balancing the tree after deletion
    void deleteFix(node_pointer x) {
      node_pointer s;
      while (x != root && x->color == 0) {
        if (x == x->parent->left) {
          s = x->parent->right;
          if (s->color == 1) {
            s->color = 0;
            x->parent->color = 1;
            leftRotate(x->parent);
            s = x->parent->right;
          }

          if (s->left->color == 0 && s->right->color == 0) {
            s->color = 1;
            x = x->parent;
          } else {
            if (s->right->color == 0) {
              s->left->color = 0;
              s->color = 1;
              rightRotate(s);
              s = x->parent->right;
            }

            s->color = x->parent->color;
            x->parent->color = 0;
            s->right->color = 0;
            leftRotate(x->parent);
            x = root;
          }
        } else {
          s = x->parent->left;
          if (s->color == 1) {
            s->color = 0;
            x->parent->color = 1;
            rightRotate(x->parent);
            s = x->parent->left;
          }

          if (s->right->color == 0 && s->right->color == 0) {
            s->color = 1;
            x = x->parent;
          } else {
            if (s->left->color == 0) {
              s->right->color = 0;
              s->color = 1;
              leftRotate(s);
              s = x->parent->left;
            }

            s->color = x->parent->color;
            x->parent->color = 0;
            s->left->color = 0;
            rightRotate(x->parent);
            x = root;
          }
        }
      }
      x->color = 0;
    }

public:
	int deleteNode(value_type data)
	{
		return deleteNodeHelper(this->root, data);
	}



	node_pointer getRoot()
	{
		return (this->root);
	}

	void printHelper(node_pointer root, std::string indent, bool last) {
    	if (root != TNULL) {
      		std::cout << indent;
      	if (last) {
        	std::cout << "R----";
        	indent += "   ";
      	} else {
        	std::cout << "L----";
        	indent += "|  ";
      	}

      std::string sColor = root->color ? "RED" : "BLACK";
      std::cout << root->data.first << " " << root-> data.second  << "(" << sColor << ")" << std::endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

};

//==============     Comparison operations           ==============

	template<class T, class Compare, class Alloc >
	bool operator==( const ft::rbtree<T,Compare,Alloc>& lhs, const ft::rbtree<T,Compare,Alloc>& rhs ){
		return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class T, class Compare, class Alloc >
	bool operator!=( const ft::rbtree<T,Compare,Alloc>& lhs, const ft::rbtree<T,Compare,Alloc>& rhs ){
		return !(lhs == rhs);
	}

	template<class T, class Compare, class Alloc >
	bool operator<( const ft::rbtree<T,Compare,Alloc>& lhs, const ft::rbtree<T,Compare,Alloc>& rhs ){
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T, class Compare, class Alloc >
	bool operator<=( const ft::rbtree<T,Compare,Alloc>& lhs, const ft::rbtree<T,Compare,Alloc>& rhs ){
		return !(rhs < lhs);
	}

	template<class T, class Compare, class Alloc >
	bool operator>( const ft::rbtree<T,Compare,Alloc>& lhs, const ft::rbtree<T,Compare,Alloc>& rhs ){
		return rhs < lhs;
	}

	template<class T, class Compare, class Alloc >
	bool operator>=( const ft::rbtree<T,Compare,Alloc>& lhs, const ft::rbtree<T,Compare,Alloc>& rhs ){
		return !(lhs < rhs);
	}

};
