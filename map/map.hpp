#ifndef MAP_HPP
#define MAP_HPP

#include "RBTree.hpp"
#include "pair.hpp"
#include "MapIterator.hpp"
#include <iostream>

namespace ft
{
    template <class Key,                                           // map::key_type
              class T,                                             // map::mapped_type
              class Compare = std::less<Key>,                      // map::key_compare
              class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
              >
    class Map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<Key, T> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef MapIterator<Node<typename ft::pair<const Key, T> >, Node<typename ft::pair<const Key, T> >*, Node<typename ft::pair<const Key, T> >& > iterator;
		typedef MapIterator<Node<ft::pair<const Key, T> >, const Node<ft::pair<const Key, T> >*, const Node<ft::pair<const Key, T> >& > const_iterator;
		typedef ReverseRAI<iterator> reverse_iterator;
		typedef ReverseRAI<const_iterator> const_reverse_iterator;

        explicit Map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _comp(comp) {}

        class value_compare : std::binary_function<value_type, value_type, bool>
        { // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            friend class map;

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

    private : 
        RBTree<ft::pair<Key, T> > _rb;
        allocator_type _alloc;
        key_compare _comp;
    };
}

#endif