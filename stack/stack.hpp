#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = vector<T> >
    class stack
    {
    public:
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;

        explicit stack(const container_type& ctnr = container_type())
        { 
            c = ctnr;
        }
        bool empty() const
        {
            return (c.empty());
        }

        size_type size() const
        {
            return (c.size());
        }

        value_type &top()
        {
            return (c.back());
        }

        const value_type &top() const
        {
            return (c.back());
        }

        void push(const value_type &val)
        {
            c.push_back(val);
        }

        void pop()
        {
            c.pop_back();
        }

    private:
        container_type c;
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (lhs.c.size() == rhs.c.size() && ft::equal(lhs.c.begin(), lhs.c.end(), rhs.c.begin()));
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (!(lhs.c == rhs.c));
    }

    template <class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return ft::lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end());
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (!(rhs.c < lhs.c));
    }

    template <class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (rhs.c < lhs.c);
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return (!(lhs.c < rhs.c));
    }
}
#endif