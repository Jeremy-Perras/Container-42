#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack
{
    public :
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

    protected :
        container_type _container;

    public :
        explicit stack (const container_type& ctnr = container_type()):_container(ctnr)
        {
        }

        stack& operator=(const stack& other) {
          if (this != &other) {
            this->_container = other._container;
          }
          return (*this);
        }

        stack(const stack& other): _container(other._container) {}

        ~stack() {}

        bool empty() const
        {
            return(_container.size() == 0 ? true : false);
        }

        size_type size() const
        {
            return(_container.size());
        }

        value_type& top()
        {
            return(_container.back());
        }

        const value_type& top() const
        {
            return(_container.back());
        }

        void push (const value_type& val)
        {
            return(_container.push_back(val));
        }

        void pop()
        {
            return(_container.pop_back());
        }

        friend bool operator==(const stack& lhs, const stack& rhs)
        {
            return (lhs._container == rhs._container);
        }
        friend bool operator!=(const stack& lhs, const stack& rhs)
        {
            return (lhs._container != rhs._container);
        }
        friend bool operator<(const stack& lhs, const stack& rhs)
        {
            return (lhs._container < rhs._container);
        }
        friend bool operator<=(const stack& lhs, const stack& rhs)
        {
            return (lhs._container <= rhs._container);
        }
        friend bool operator>(const stack& lhs, const stack& rhs)
        {
            return (lhs._container > rhs._container);
        }
        friend bool operator>=(const stack& lhs, const stack& rhs)
        {
            return (lhs._container >= rhs._container);
        }
};

}
#endif
