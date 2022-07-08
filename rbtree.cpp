#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "other.hpp"

namespace ft
{
    const class nullptr_t
    {
    public:
        template<class T>
        operator T*() const
        {
            return(0);
        }
        template <class T, class U>
        operator T U::*() const
        {
            return(0);
        }
        private:
            void operator&() const;
        }
        NIL = {};
        // node
        template <typename T>
        class Node
        {
            Node*   _parent;
            Node*   _left;
            Node*   _right;
            value_type  _value;
            bool        _is_black;
            Node()
              : _parent(NIL), _left(NIL), _right(NIL), _value(value_type()), _is_black(bool()) {}
            Node(const value_type& value)
              : _parent(NIL), _left(NIL), _right(NIL), _value(value), _is_black(bool()) {}
            Node(const TreeNode& ref)
              : _parent(ref._parent), _left(ref._left), _right(ref._right), _value(ref._value), _is_black(ref._is_black) {}
            ~Node() {}
            Node& operator=(const Node& ref)
            {
              if (this != &ref)
              {
                _parent = ref._parent;
                _left = ref._left;
                _right = ref._right;
                _value = ref._value;
                _is_black = ref._is_black;
              }
              return (*this);
            }
          };

      template <typename NodePtr>
      bool is_left_child(const NodePtr& ptr)
      {
        return (ptr == ptr->_parent->_left);
      }
      template <typename NodePtr>
      bool is_right_child(const NodePtr& ptr)
      {
        return (ptr == ptr->_parent->_right);
      }

      template <typename NodePtr>
      bool is_black_color(const NodePtr& ptr)
      {
        return (ptr->_is_black);
      }
      template <typename NodePtr>
      bool is_red_color(const NodePtr& ptr)
      {
        return (!ptr->_is_black);
      }

      template <typename NodePtr>
      NodePtr get_min_node(NodePtr ptr, NodePtr nil)
      {
        while (ptr->_left != nil)
          ptr = ptr->_left;
        return (ptr);
      }
      template <typename NodePtr>
      NodePtr get_max_node(NodePtr ptr, NodePtr nil)
      {
        while (ptr->_right != nil)
          ptr = ptr->_right;
        return (ptr);
      }

      template <typename NodePtr>
      NodePtr get_next_node(NodePtr ptr, NodePtr nil)
      {
        if (ptr->_right != nil)
          return (get_min_node(ptr->_right, nil));
        while (!is_left_child(ptr))
          ptr = ptr->_parent;
        return (ptr->_parent);
      }
      template <typename NodePtr>
      NodePtr get_prev_node(NodePtr ptr, NodePtr nil)
      {
        if (ptr->_left != nil)
          return (get_max_node(ptr->_left, nil));
        while (!is_right_child(ptr))
          ptr = ptr->_parent;
        return (ptr->_parent);
      }

      template <typename U, typename V, class Comp>
      bool is_equal(const U& u, const V& v, Comp comp)
      {
        return (!comp(u, v) && !comp(v, u));
      }

      // iterator

      template <typename U, typename V>
      class tree_iterator {
        public:
        typedef U                                                           value_type;
        typedef value_type*                                                 pointer;
        typedef value_type&                                                 reference;
        typedef V*                                                          iterator_type;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::value_type         node_type;
        typedef typename iterator_traits<iterator_type>::pointer            node_pointer;
        typedef typename iterator_traits<iterator_type>::reference          node_reference;
        typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;

        private:
            node_pointer  _current;
            node_pointer  _nil;

        public:
        tree_iterator() : _current(NIL), _nil(NIL) {}
        tree_iterator(node_pointer cur, node_pointer nil) : _current(cur), _nil(nil) {}
        tree_iterator(const tree_iterator& ref) : _current(ref._current), _nil(ref._nil) {}
        ~tree_iterator() {}

        tree_iterator& operator=(const tree_iterator& ref) {
          if (this != &ref) {
            _current = ref._current;
            _nil = ref._nil;
          }
          return (*this);
        }

        node_pointer base()       const
        {
            return (_current);
        }
        pointer      operator->() const
        {
            return (&_current->_value);
        }
        reference    operator*()  const
        {
            return (_current->_value);
        }

        tree_iterator& operator++()
        {
          _current = get_next_node(_current, _nil);
          return (*this);
        }
        tree_iterator operator++(int)
        {
          tree_iterator tmp(*this);
          ++(*this);
          return (tmp);
        }

        tree_iterator& operator--()
        {
          _current = get_prev_node(_current, _nil);
          return (*this);
        }
        tree_iterator operator--(int)
        {
          tree_iterator tmp(*this);
          --(*this);
          return (tmp);
        }

        template <typename T>
        bool operator==(const tree_iterator<T, node_type>& x) const
        {
          return (_current == x.base());
        }
        template <typename T>
        bool operator!=(const tree_iterator<T, node_type>& x) const
        {
          return !(*this == x);
        }

        operator tree_iterator<const value_type, node_type>(void) const
        {
          return (tree_iterator<const value_type, node_type>(_current, _nil));
        }

        friend bool operator==(const tree_iterator& lhs, const tree_iterator& rhs)
        {
          return (lhs._current == rhs._current);
        }
        friend bool operator!=(const tree_iterator& lhs, const tree_iterator& rhs)
        {
          return (!(lhs == rhs));
        }
      };

      // tree
      
      template <typename T, class Key, class Comp, class Allocator>
      class rbtree {
        public:
        typedef T                                                           value_type;
        typedef Key                                                         key_type;
        typedef Comp                                                        compare_type;
        typedef TreeNode<value_type>                                        node_type;
        typedef TreeNode<value_type>*                                       node_pointer;
        typedef tree_iterator<value_type, node_type>                        iterator;
        typedef tree_iterator<const value_type, node_type>                  const_iterator;
        typedef Allocator                                                   allocator_type;
        typedef typename allocator_type::template rebind<node_type>::other  node_allocator;
        typedef std::allocator_traits<node_allocator>                       node_traits;
        typedef std::size_t                                                 size_type;
        typedef std::ptrdiff_t                                              difference_type;

        private:
        node_pointer    _nil;
        node_pointer    _begin;
        node_pointer    _end;
        compare_type    _comp;
        node_allocator  _alloc;
        size_type       _size;

        public:
        rbtree(const compare_type& comp, const allocator_type& alloc)
          : _comp(comp), _alloc(alloc), _size(size_type()) {
            _nil = _alloc.allocate(1);
            _alloc.construct(_nil, value_type());
            _nil->_is_black = true;
            _nil->_parent = _nil;
            _nil->_left = _nil;
            _nil->_right= _nil;
            _end = create_node(value_type());
            _end->_is_black = true;
            _begin = _end;
          }
        rbtree(const rbtree& ref)
          : _comp(ref._comp), _alloc(ref._alloc), _size(size_type()) {
            _nil = _alloc.allocate(1);
            _alloc.construct(_nil, value_type());
            _nil->_is_black = true;
            _nil->_parent = _nil;
            _nil->_left = _nil;
            _nil->_right = _nil;
            _end = create_node(value_type());
            _end->_is_black = true;
            _begin = _end;
            insert(ref.begin(), ref.end());
          }
        ~rbtree() {
          delete_node_recursive(_end);
          delete_node(_nil);
        }

        rbtree& operator=(const rbtree& ref) {
          if (this != &ref) {
            rbtree tmp(ref);
            swap(tmp);
          }
          return (*this);
        }

        iterator begin() {
          return (iterator(_begin, _nil));
        }
        const_iterator begin() const {
          return (const_iterator(_begin, _nil));
        }

        iterator end() {
          return (iterator(_end, _nil));
        }
        const_iterator end() const {
          return (const_iterator(_end, _nil));
        }

        size_type size() const {
          return (_size);
        }
        size_type max_size() const {
          return (_alloc.max_size());
        }

        bool empty() const {
          return (_size == 0);
        }

        ft::pair<iterator, bool> insert(const value_type& value) {
          node_pointer ptr = search_parent(value);
          if (ptr != _end && is_equal(ptr->_value, value, _comp))
            return (ft::make_pair(iterator(ptr, _nil), false));
          return (ft::make_pair(iterator(insert_internal(value, ptr), _nil), true));
        }
        iterator insert(iterator position, const value_type& value) {
          node_pointer ptr = search_parent(value, position.base());
          if (ptr != _end && is_equal(ptr->_value, value, _comp))
            return (iterator(ptr, _nil));
          return (iterator(insert_internal(value, ptr), _nil));
        }
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last) {
          for (; first != last; first++)
            insert(*first);
        }

        iterator erase(iterator position) {
          if (_size == 0)
            return (iterator(_nil, _nil));
          iterator tmp(position);
          ++tmp;
          if (position == begin())
            _begin = tmp.base();
          --_size;
          remove_internal(position.base());
          delete_node(position.base());
          return (tmp);
        }
        template <typename U>
        size_type erase(const U& value) {
          iterator i(find_internal(value), _nil);
          if (i == end())
            return (0);
          if (i == begin()) {
            iterator tmp(i);
            ++tmp;
            _begin = tmp.base();
          }
          --_size;
          remove_internal(i.base());
          delete_node(i.base());
          return (1);
        }
        void erase(iterator first, iterator last) {
          for (; first != last;)
            first = erase(first);
        }

        void swap(rbtree& ref) {
          std::swap(_nil, ref._nil);
          std::swap(_begin, ref._begin);
          std::swap(_end, ref._end);
          std::swap(_comp, ref._comp);
          std::swap(_alloc, ref._alloc);
          std::swap(_size, ref._size);
        }

        void clear(void) {
          rbtree tmp(_comp, _alloc);
          swap(tmp);
        }

        iterator find(const key_type& key) {
          return (iterator(find_internal(key), _nil));
        }
        const_iterator find(const key_type& key) const {
          return (const_iterator(find_internal(key), _nil));
        }

        iterator lower_bound(const key_type& key) {
          return (iterator(lower_bound_internal(key), _nil));
        }
        const_iterator lower_bound(const key_type& key) const {
          return (const_iterator(lower_bound_internal(key), _nil));
        }

        iterator upper_bound(const key_type& key) {
          return (iterator(upper_bound_internal(key), _nil));
        }
        const_iterator upper_bound(const key_type& key) const {
          return (const_iterator(upper_bound_internal(key), _nil));
        }

        ft::pair<iterator, iterator> equal_range(const key_type& key) {
          return (equal_range_internal(key));
        }
        ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
          return (equal_range_internal(key));
        }

        allocator_type get_allocator() const {
          return (_alloc);
        }

        private:
        node_pointer get_root() const {
          return (_end->_left);
        }

        void set_root(const node_pointer ptr) {
          ptr->_parent = _end;
          _end->_left = ptr;
        }

        node_pointer create_node(const value_type& value) {
          node_pointer ptr = _alloc.allocate(1);
          _alloc.construct(ptr, value);
          ptr->_parent = _nil;
          ptr->_left = _nil;
          ptr->_right = _nil;
          ptr->_is_black = false;
          return (ptr);
        }

        void delete_node(node_pointer ptr) {
          _alloc.destroy(ptr);
          _alloc.deallocate(ptr, 1);
        }

        void delete_node_recursive(node_pointer ptr) {
          if (ptr == _nil)
            return ;
          delete_node_recursive(ptr->_left);
          delete_node_recursive(ptr->_right);
          delete_node(ptr);
        }

        node_pointer search_parent(const value_type& value, node_pointer position = NIL) {
          if (position && position != _end) {
            if (_comp(value, position->_value) && position->_left == _nil) {
              iterator prev = iterator(position, _nil);
              if (prev == begin() || _comp(*--prev, value))
                return (position);
            } else if (position->_right == _nil) {
              iterator next = iterator(position, _nil);
              if (next == end() || _comp(value, *++next))
                return (position);
            }
          }
          node_pointer cur = get_root();
          node_pointer tmp = _end;
          for (; cur != _nil;) {
            tmp = cur;
            if (_comp(value, cur->_value))
              cur = cur->_left;
            else if (_comp(cur->_value, value))
              cur = cur->_right;
            else
              return (cur);
          }
          return (tmp);
        }

        node_pointer insert_internal(const value_type& value, node_pointer parent) {
          node_pointer ptr = create_node(value);
          if (parent == _end) {
            set_root(ptr);
          } else if (_comp(value, parent->_value)) {
            parent->_left = ptr;
          } else {
            parent->_right = ptr;
          }
          ptr->_parent = parent;
          insert_fixup(ptr);
          insert_update(ptr);
          return (ptr);
        }

        void insert_fixup(node_pointer ptr) {
          while (is_red_color(ptr->_parent)) {
            if (is_left_child(ptr->_parent)) {
              insert_fixup_left(ptr);
            } else {
              insert_fixup_right(ptr);
            }
          }
          get_root()->_is_black = true;
        }

        void insert_fixup_left(node_pointer& ptr) {
          node_pointer uncle = ptr->_parent->_parent->_right;
          if (is_red_color(uncle)) {
            ptr->_parent->_is_black = true;
            uncle->_is_black = true;
            uncle->_parent->_is_black = false;
            ptr = uncle->_parent;
          } else {
            if (is_right_child(ptr)) {
              ptr = ptr->_parent;
              rotate_left(ptr);
            }
            ptr->_parent->_is_black = true;
            ptr->_parent->_parent->_is_black = false;
            rotate_right(ptr->_parent->_parent);
          }
        }

        void insert_fixup_right(node_pointer& ptr) {
          node_pointer uncle = ptr->_parent->_parent->_left;
          if (is_red_color(uncle)) {
            ptr->_parent->_is_black = true;
            uncle->_is_black = true;
            uncle->_parent->_is_black = false;
            ptr = uncle->_parent;
          } else {
            if (is_left_child(ptr)) {
              ptr = ptr->_parent;
              rotate_right(ptr);
            }
            ptr->_parent->_is_black = true;
            ptr->_parent->_parent->_is_black = false;
            rotate_left(ptr->_parent->_parent);
          }
        }

        void insert_update(const node_pointer ptr) {
          if (_begin == _end || _comp(ptr->_value, _begin->_value))
            _begin = ptr;
          _size++;
        }

        void remove_internal(node_pointer ptr) {
          node_pointer recolor_node;
          node_pointer fixup_node = ptr;
          bool original_color = is_black_color(ptr);
          if (ptr->_left == _nil) {
            recolor_node = ptr->_right;
            transplant(ptr, ptr->_right);
          } else if (ptr->_right == _nil) {
            recolor_node = ptr->_left;
            transplant(ptr, ptr->_left);
          } else {
            fixup_node = get_min_node(ptr->_right, _nil);
            original_color = is_black_color(fixup_node);
            recolor_node = fixup_node->_right;
            if (fixup_node->_parent == ptr) {
              recolor_node->_parent = fixup_node;
            } else {
              transplant(fixup_node, fixup_node->_right);
              fixup_node->_right = ptr->_right;
              fixup_node->_right->_parent = fixup_node;
            }
            transplant(ptr, fixup_node);
            fixup_node->_left = ptr->_left;
            fixup_node->_left->_parent = fixup_node;
            fixup_node->_is_black = is_black_color(ptr);
          }
          if (original_color)
            remove_fixup(recolor_node);
        }

        void remove_fixup(node_pointer ptr) {
          while (ptr != get_root() && is_black_color(ptr)) {
            if (is_left_child(ptr)) {
              remove_fixup_left(ptr);
            } else {
              remove_fixup_right(ptr);
            }
          }
          ptr->_is_black = true;
        }

        void remove_fixup_left(node_pointer& ptr) {
          node_pointer sibling = ptr->_parent->_right;
          if (is_red_color(sibling)) {
            sibling->_is_black = true;
            ptr->_parent->_is_black = false;
            rotate_left(ptr->_parent);
            sibling = ptr->_parent->_right;
          }
          if (is_black_color(sibling->_left) && is_black_color(sibling->_right)) {
            sibling->_is_black = false;
            ptr = ptr->_parent;
          } else if (is_black_color(sibling->_right)) {
            sibling->_left->_is_black = true;
            sibling->_is_black = false;
            rotate_right(sibling);
            sibling = ptr->_parent->_right;
          }
          if (is_red_color(sibling->_right)) {
            sibling->_is_black = is_black_color(ptr->_parent);
            ptr->_parent->_is_black = true;
            sibling->_right->_is_black = true;
            rotate_left(ptr->_parent);
            ptr = get_root();
          }
        }

        void remove_fixup_right(node_pointer& ptr) {
          node_pointer sibling = ptr->_parent->_left;
          if (is_red_color(sibling)) {
            sibling->_is_black = true;
            ptr->_parent->_is_black = false;
            rotate_right(ptr->_parent);
            sibling = ptr->_parent->_left;
          }
          if (is_black_color(sibling->_right) && is_black_color(sibling->_left)) {
            sibling->_is_black = false;
            ptr = ptr->_parent;
          } else if (is_black_color(sibling->_left)) {
            sibling->_right->_is_black = true;
            sibling->_is_black = false;
            rotate_left(sibling);
            sibling = ptr->_parent->_left;
          }
          if (is_red_color(sibling->_left)) {
            sibling->_is_black = is_black_color(ptr->_parent);
            ptr->_parent->_is_black = true;
            sibling->_left->_is_black = true;
            rotate_right(ptr->_parent);
            ptr = get_root();
          }
        }

        void transplant(node_pointer former, node_pointer latter) {
          if (former->_parent == _end) {
            set_root(latter);
          } else if (is_left_child(former)) {
            former->_parent->_left = latter;
          } else {
            former->_parent->_right = latter;
          }
          latter->_parent = former->_parent;
        }

        void rotate_left(node_pointer ptr) {
          node_pointer child = ptr->_right;
          ptr->_right = child->_left;
          if (ptr->_right != _nil) {
            ptr->_right->_parent = ptr;
          }
          node_pointer parent = ptr->_parent;
          child->_parent = parent;
          if (parent == _end) {
            set_root(child);
          } else if (is_left_child(ptr)) {
            parent->_left = child;
          } else {
            parent->_right = child;
          }
          child->_left = ptr;
          ptr->_parent = child;
        }

        void rotate_right(node_pointer ptr) {
          node_pointer child = ptr->_left;
          ptr->_left = child->_right;
          if (ptr->_left != _nil) {
            ptr->_left->_parent = ptr;
          }
          node_pointer parent = ptr->_parent;
          child->_parent = parent;
          if (parent == _end) {
            set_root(child);
          } else if (is_left_child(ptr)) {
            parent->_left = child;
          } else {
            parent->_right = child;
          }
          child->_right = ptr;
          ptr->_parent = child;
        }

        template <typename U>
        node_pointer find_internal(const U& value) const {
          node_pointer ptr = get_root();
          while (ptr != _nil) {
            if (_comp(value, ptr->_value)) {
              ptr = ptr->_left;
            } else if (_comp(ptr->_value, value)) {
              ptr = ptr->_right;
            } else {
              return ptr;
            }
          }
          return _end;
        }

        node_pointer lower_bound_internal(const key_type& key) const {
          node_pointer ptr = get_root();
          node_pointer tmp = _end;
          while (ptr != _nil) {
            if (!_comp(ptr->_value, key)) {
              tmp = ptr;
              ptr = ptr->_left;
            } else {
              ptr = ptr->_right;
            }
          }
          return tmp;
        }

        node_pointer upper_bound_internal(const key_type& key) const {
          node_pointer ptr = get_root();
          node_pointer tmp = _end;
          while (ptr != _nil) {
            if (_comp(key, ptr->_value)) {
              tmp = ptr;
              ptr = ptr->_left;
            } else {
              ptr = ptr->_right;
            }
          }
          return tmp;
        }

        template <typename U>
        ft::pair<iterator, iterator> equal_range_internal(const U& value) {
          node_pointer ptr = get_root();
          node_pointer tmp = _end;
          while (ptr != _nil) {
            if (_comp(value, ptr->_value)) {
              tmp = ptr;
              ptr = ptr->_left;
            } else if (_comp(ptr->_value, value)) {
              ptr = ptr->_right;
            } else {
              if (ptr->_right != _nil) {
                tmp = get_min_node(ptr->_right, _nil);
              }
              return (make_pair(iterator(ptr, _nil), iterator(tmp, _nil)));
            }
          }
          return (make_pair(iterator(tmp, _nil), iterator(tmp, _nil)));
        }
        template <typename U>
        ft::pair<const_iterator, const_iterator> equal_range_internal(const U& value) const {
          node_pointer ptr = get_root();
          node_pointer tmp = _end;
          while (ptr != _nil) {
            if (_comp(value, ptr->_value)) {
              tmp = ptr;
              ptr = ptr->_left;
            } else if (_comp(ptr->_value, value)) {
              ptr = ptr->_right;
            } else {
              if (ptr->_right != _nil) {
                tmp = get_min_node(ptr->_right, _nil);
              }
              return (ft::make_pair(const_iterator(ptr, _nil), const_iterator(tmp, _nil)));
            }
          }
          return (ft::make_pair(const_iterator(tmp, _nil), const_iterator(tmp, _nil)));
        }
      };
    }
















    void initializeNULLNode(NodePtr node, NodePtr parent) {
       node->data = 0;
       node->parent = parent;
       node->left = nullptr;
       node->right = nullptr;
       node->color = 0;
     }

     // Preorder
     void preOrderHelper(NodePtr node) {
       if (node != TNULL) {
         cout << node->data << " ";
         preOrderHelper(node->left);
         preOrderHelper(node->right);
       }
     }

     // Inorder
     void inOrderHelper(NodePtr node) {
       if (node != TNULL) {
         inOrderHelper(node->left);
         cout << node->data << " ";
         inOrderHelper(node->right);
       }
     }

     // Post order
     void postOrderHelper(NodePtr node) {
       if (node != TNULL) {
         postOrderHelper(node->left);
         postOrderHelper(node->right);
         cout << node->data << " ";
       }
     }

     NodePtr searchTreeHelper(NodePtr node, int key) {
       if (node == TNULL || key == node->data) {
         return node;
       }

       if (key < node->data) {
         return searchTreeHelper(node->left, key);
       }
       return searchTreeHelper(node->right, key);
     }

     // For balancing the tree after deletion
     void deleteFix(NodePtr x) {
       NodePtr s;
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

     void rbTransplant(NodePtr u, NodePtr v) {
       if (u->parent == nullptr) {
         root = v;
       } else if (u == u->parent->left) {
         u->parent->left = v;
       } else {
         u->parent->right = v;
       }
       v->parent = u->parent;
     }

     void deleteNodeHelper(NodePtr node, int key) {
       NodePtr z = TNULL;
       NodePtr x, y;
       while (node != TNULL) {
         if (node->data == key) {
           z = node;
         }

         if (node->data <= key) {
           node = node->right;
         } else {
           node = node->left;
         }
       }

       if (z == TNULL) {
         cout << "Key not found in the tree" << endl;
         return;
       }

       y = z;
       int y_original_color = y->color;
       if (z->left == TNULL) {
         x = z->right;
         rbTransplant(z, z->right);
       } else if (z->right == TNULL) {
         x = z->left;
         rbTransplant(z, z->left);
       } else {
         y = minimum(z->right);
         y_original_color = y->color;
         x = y->right;
         if (y->parent == z) {
           x->parent = y;
         } else {
           rbTransplant(y, y->right);
           y->right = z->right;
           y->right->parent = y;
         }

         rbTransplant(z, y);
         y->left = z->left;
         y->left->parent = y;
         y->color = z->color;
       }
       delete z;
       if (y_original_color == 0) {
         deleteFix(x);
       }
     }

     // For balancing the tree after insertion
     void insertFix(NodePtr k) {
       NodePtr u;
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

     void printHelper(NodePtr root, string indent, bool last) {
       if (root != TNULL) {
         cout << indent;
         if (last) {
           cout << "R----";
           indent += "   ";
         } else {
           cout << "L----";
           indent += "|  ";
         }

         string sColor = root->color ? "RED" : "BLACK";
         cout << root->data << "(" << sColor << ")" << endl;
         printHelper(root->left, indent, false);
         printHelper(root->right, indent, true);
       }
     }

      public:
     RedBlackTree() {
       TNULL = new Node;
       TNULL->color = 0;
       TNULL->left = nullptr;
       TNULL->right = nullptr;
       root = TNULL;
     }

     void preorder() {
       preOrderHelper(this->root);
     }

     void inorder() {
       inOrderHelper(this->root);
     }

     void postorder() {
       postOrderHelper(this->root);
     }

     NodePtr searchTree(int k) {
       return searchTreeHelper(this->root, k);
     }

     NodePtr minimum(NodePtr node) {
       while (node->left != TNULL) {
         node = node->left;
       }
       return node;
     }

     NodePtr maximum(NodePtr node) {
       while (node->right != TNULL) {
         node = node->right;
       }
       return node;
     }

     NodePtr successor(NodePtr x) {
       if (x->right != TNULL) {
         return minimum(x->right);
       }

       NodePtr y = x->parent;
       while (y != TNULL && x == y->right) {
         x = y;
         y = y->parent;
       }
       return y;
     }

     NodePtr predecessor(NodePtr x) {
       if (x->left != TNULL) {
         return maximum(x->left);
       }

       NodePtr y = x->parent;
       while (y != TNULL && x == y->left) {
         x = y;
         y = y->parent;
       }

       return y;
     }

     void leftRotate(NodePtr x) {
       NodePtr y = x->right;
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

     void rightRotate(NodePtr x) {
       NodePtr y = x->left;
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

     // Inserting a node
     void insert(int key) {
       NodePtr node = new Node;
       node->parent = nullptr;
       node->data = key;
       node->left = TNULL;
       node->right = TNULL;
       node->color = 1;

       NodePtr y = nullptr;
       NodePtr x = this->root;

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

       if (node->parent == nullptr) {
         node->color = 0;
         return;
       }

       if (node->parent->parent == nullptr) {
         return;
       }

       insertFix(node);
     }

     NodePtr getRoot() {
       return this->root;
     }

     void deleteNode(int data) {
       deleteNodeHelper(this->root, data);
     }

     void printTree() {
       if (root) {
         printHelper(this->root, "", true);
       }
     }
   };
























}







































































// C++ program to delete a node from AVL Tree

#include <iostream>
#include <memory>
using namespace std;

// An AVL tree node
class Node
{
    public:
    int key;
    Node *left;
    Node *right;
    int height;
};

// A utility function to get maximum
// of two integers
int max(int a, int b);

// A utility function to get height
// of the tree
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum
// of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
                      // added at leaf
    return(node);
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) -
           height(N->right);
}

Node* insert(Node* node, int key)
{
    /* 1. Perform the normal BST rotation */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys not allowed
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Get the balance factor of this
        ancestor node to check whether
        this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree,
return the node with minimum key value
found in that tree. Note that the entire
tree does not need to be searched. */
Node * minValueNode(Node* node)
{
    Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node
// with given key from subtree with
// given root. It returns root of the
// modified subtree.
Node* deleteNode(Node* root, int key)
{

    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            Node *temp = root->left ?
                         root->left :
                         root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's
            // data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }

    // If the tree had only one node
    // then return
    if (root == NULL)
    return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// A utility function to print preorder
// traversal of the tree.
// The function also prints height
// of every node
void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Driver Code
int main()
{
Node *root = NULL;

    /* Constructing tree given in
    the above figure */
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    /* The constructed AVL Tree would be
        9
        / \
        1 10
        / \ \
        0 5 11
        / / \
        -1 2 6
    */

    cout << "Preorder traversal of the "
            "constructed AVL tree is \n";
    preOrder(root);

    root = deleteNode(root, 10);

    /* The AVL Tree after deletion of 10
            1
        / \
        0 9
        / / \
    -1 5     11
        / \
        2 6
    */

    cout << "\nPreorder traversal after"
         << " deletion of 10 \n";
    preOrder(root);

    return 0;
}
