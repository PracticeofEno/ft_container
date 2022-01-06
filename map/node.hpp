#ifndef NODE_HPP
#define NODE_HPP

#include "pair.hpp"
#define RED 1
#define BLACK 2
#define DBLACK 3

template <class T1, class T2, class Compare>
class Node
{
public:
    typedef Compare key_compare;
    Node<T1, T2, Compare> *parent;
    Node<T1, T2, Compare> *left;
    Node<T1, T2, Compare> *right;
    int color;
    bool isNull;
    ft::pair<T1, T2> _data;
    key_compare comp;

    Node() : parent(0), left(0), right(0), color(BLACK), isNull(false), comp(Compare()) {}
    Node(const Node& tmp) : parent(tmp.parent), left(tmp.left), right(tmp.right), color(tmp.color), isNull(tmp.isNull), _data(tmp._data) { }
    Node(const ft::pair<T1,T2> tmp) : parent(0), left(0), right(0), color(BLACK), isNull(false), _data(tmp) {}

    Node& operator=(const Node& tmp)
    {
        parent = tmp.parent;
        left = tmp.left;
        right = tmp.right;
        color = tmp.color;
        isNull = tmp.isNull;
        _data = tmp._data;
        return *this;
    }

    const Node<T1, T2, Compare>* getNext() const
    {
        Node<T1, T2, Compare> *biggerParent;

        if (isNull)
            return getleftend(this);
        
        if (right->isNull == true)
        {
            biggerParent = getBiggerParent(this);
            if (biggerParent == 0)
                return right;
            else
                return biggerParent;
        }
        else
        {
            return findSmallestSubtree(right);
        }
    }

    const Node<T1, T2, Compare> *getPrev() const
    {
        Node<T1, T2, Compare> *lowerParent;

        if (isNull)
            return getrightend(this);

        if (left->isNull == true)
        {
            lowerParent = getLowerParent(this);
            if (lowerParent == 0)
                return left;
            else
                return lowerParent;
        }
        else
        {
            return findLargestSubtree(left);
        }
    }

    ft::pair<T1, T2>& operator*()
    {
        return _data;
    }

    ft::pair<T1, T2>* operator->()
    {
        return &_data;
    }

    void setData(ft::pair<T1,T2> tmp)
    {
        _data = tmp;
    }

    ft::pair<T1,T2>& getData()
    {
        return _data;
    }

private:
    Node<T1, T2, Compare> *findLargestSubtree(Node<T1, T2, Compare> *subtree) const
    {
        while (subtree->right->isNull == false)
        {
            subtree = subtree->right;
        }
        return subtree;
    }

    Node<T1, T2, Compare> *findSmallestSubtree(Node<T1, T2, Compare> *subtree) const
    {
        while (subtree->left->isNull == false)
        {
            subtree = subtree->left;
            if (subtree->left->isNull == true)
                break;
        }
        return subtree;
    }

    Node<T1, T2, Compare> *getLowerParent(const Node<T1, T2, Compare> *tmp) const
    {
        Node<T1, T2, Compare> *parent;

        parent = tmp->parent;
        if (parent != 0)
        {
            while ( comp(tmp->_data.first, parent->_data.first) == true)
            {
                parent = parent->parent;
                if (parent == 0)
                    return 0;
            }
            return parent;
        }
        else
        {
            return 0;
        }
    }

    Node<T1, T2, Compare> *getBiggerParent(const Node<T1, T2, Compare> *tmp) const
    {
        Node<T1, T2, Compare> *parent;

        parent = tmp->parent;
        if (parent != 0)
        {
            while ( comp(tmp->_data.first, parent->_data.first) == false)
            {
                parent = parent->parent;
                if (parent == 0)
                    return 0;
            }
            return parent;
        }
        else
        {
            return 0;
        }
    }

    Node<T1,T2, Compare> *getrightend(const Node<T1, T2, Compare> *tmp) const
    {
        Node<T1, T2, Compare> *parent;

        parent = tmp->parent;
        while (parent)
        {
            if (parent->parent != 0)
                parent = parent->parent;
            else
                break;
        }
        while (parent->right->isNull == false)
            parent = parent->right;
        return parent;
    }

    Node<T1,T2, Compare> *getleftend(const Node<T1, T2, Compare> *tmp) const 
    {
        Node<T1, T2, Compare> *parent;

        parent = tmp->parent;
        while (parent)
        {
            if (parent->parent != 0)
                parent = parent->parent;
            else
                break;
        }
        while (parent->left->isNull == false)
            parent = parent->left;
        return parent;
    }
};

template <class T1, class T2, class Compare>
bool operator==(const Node<T1, T2, Compare> &lhs, const Node<T1, T2, Compare> &rhs)
{
    return lhs._data.first == rhs._data.first && lhs._data.second == rhs._data.second;
}

template <class T1, class T2, class Compare>
bool operator!=(const Node<T1, T2, Compare> &lhs, const Node<T1, T2, Compare> &rhs)
{
    return !(lhs == rhs);
}

template <class T1, class T2, class Compare>
bool operator<(const Node<T1, T2, Compare> &lhs, const Node<T1, T2, Compare> &rhs)
{
    return lhs._data.first < rhs._data.first || (!(rhs._data.first < lhs._data.first) && lhs._data.second < rhs._data.second);
}

template <class T1, class T2, class Compare>
bool operator<=(const Node<T1, T2, Compare> &lhs, const Node<T1, T2, Compare> &rhs)
{
    return !(rhs < lhs);
}

template <class T1, class T2, class Compare>
bool operator>(const Node<T1, T2, Compare> &lhs, const Node<T1, T2, Compare> &rhs)
{
    return rhs < lhs;
}

template <class T1, class T2, class Compare>
bool operator>=(const Node<T1, T2, Compare> &lhs, const Node<T1, T2, Compare> &rhs)
{
    return !(lhs < rhs);
}

#endif