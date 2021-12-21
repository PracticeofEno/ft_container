#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "MapIterator.hpp"
#include "MapReverseIterator.hpp"
#include <iostream>

template <typename A, typename B>
class RBTree;

namespace ft
{
    template <class Key,                                           // map::key_type
              class T,                                             // map::mapped_type
              class Compare = std::less<Key>,                      // map::key_compare
              class Alloc = std::allocator<Node<Key, T> > // map::allocator_type
              >
    class Map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<Key, T> value_type;
        typedef Node<Key, T> node_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef size_t size_type;

        typedef MapIterator<node_type, node_type*, node_type&> iterator;
        typedef MapIterator<node_type, const node_type*, const node_type&> const_iterator;
		typedef MapReverseIterator<iterator> reverse_iterator;
		typedef MapReverseIterator<const_iterator> const_reverse_iterator;

        ////////////////// constructor, destructor ///////////////////////

        explicit Map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), _comp(comp), _size(0)
        { 
            _rb.setAlloc(alloc);
        }

        template <class InputIterator>
        Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp)
        { 
            _rb.setAlloc(alloc);
            _size = 0;
            while (first != last)
            {
                insert(first, last);
                first++;
            }
        }

        Map (const Map& x)
        {
            this->insert(x.begin(), x.end());
        }

        ~Map()
        {
            clear();
        }
        ///////////////////////////////////////////////////////////////////

        // Map::operator= 
        Map& operator=(const Map& x)
        {
            if (this != &x) {
				this->clear();
				this->_alloc = x._alloc;
				this->_comp = x._comp;
				this->insert(x.begin(), x.end());
			}
			return (*this);
        }
        ///////////////////////////////


        //////        Modifiers         ///////////
        //////        insert            ///////////
        ft::pair<iterator, bool> insert(const value_type& val)
        {
            Node<Key,T> *tmp;

            tmp = _rb.search(val.first, &tmp);
            if (tmp) // key is exist
            {
                return ft::make_pair(iterator(tmp), true);
            }
            else  // non exist
            {
                _size = _size + 1;
                return ft::make_pair(iterator(_rb.insert(val)), false);
            }
        }

        iterator insert (iterator position, const value_type& val)
        {
            Node<Key,T> *tmp;
            (void)position;

            tmp = _rb.search(val.first, &tmp);
            if (tmp) // key is exist
            {
                return (iterator(tmp));
            }
            else  // non exist
            {
                return iterator(_rb.insert(val));
            }
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                _rb.insert( (*first)._data );
            }
        }
        ////////////////////////////////////////////////////////////
        ///////////        erase           /////////////////////
        void erase (iterator position)
        {
            _rb.erase((*position)._data.first);
        }

        size_type erase (const key_type& k)
        {
            size_type n = 0;
            while (true)
            {
                if (_rb.erase(k) == true)
                {
                    n++;
                    _size = _size - 1;
                }
                else
                    break;
            }
            return n;
        }

        void erase (iterator first, iterator last)
        {
            while (first != last)
            {
                _rb.erase( (*first)._data.first );
                first++;
            }
        }
        /////////////////////////////////////////////////////////

        void swap (Map& x)
        {
            (void)x;
        }

        void clear()
        {
            while (_size != 0)
            {
                erase(_rb.root->_data.first);
            }
        }
        //////////////////////////////////////////////////////////

        /////////////////    iterator         //////////////////////
        iterator begin()
        {
            return iterator(_rb.begin());
        }

        const_iterator begin() const
        {
            return iterator(_rb.begin());
        }

        iterator end()
        {
            return iterator(_rb.end());
        }

        const_iterator end() const
        {
            return iterator(_rb.end());
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
        ////////////////////////////////////////////////////////////

        ///////////////// capacity ///////////////////////////////
        size_type size() const
        {
            return _size;
        }

        size_type max_size() const 
        {
            return _alloc.max_size();
        }

        bool empty() const
        {
            if (_size == 0)
                return true;
            return false;
        }

        ///////////////////////////////////////////////////////////

        //////////////     operations ////////////////////////////
        iterator find (const key_type& k)
        {
            Node<Key,T>* tmp(_rb.search(k));
            if (tmp == 0)
                return end();
            else
                return iterator(tmp);
        }

        const_iterator find (const key_type& k) const
        {
            Node<Key,T>* tmp(_rb.search(k));
            if (tmp == 0)
                return end();
            else
                return iterator(tmp);
        }

        size_type count (const key_type& k) const
        {
            Node<Key,T>* tmp(_rb.search(k));
            if (tmp == 0)
                return 0;
            else
                return 1;
        }

        iterator lower_bound (const key_type& k)
        {
            Node<Key, T>* root = _rb.root;

            while (!root->isNull)
            {
                if (_comp(root->_data.first, k) == false)
                {
                    return iterator(root);
                }
                else
                {
                    root = root->right;
                }
            }
            return end();
        }

        const_iterator lower_bound (const key_type& k) const
        {
            Node<Key, T>* root = _rb.root;

            while (!root->isNull)
            {
                if (_comp(root->_data.first, k) == false)
                {
                    return iterator(root);
                }
            }
            return end();
        }

        iterator upper_bound (const key_type& k)
        {
            Node<Key, T>* root = _rb.root;

            while (!root->isNull)
            {
                if (_comp(root->_data.first, k) == false)
                {
                    if (root->_data.first != k)
                        return iterator(root);
                    else
                        root = root->right;
                }
                else
                {
                    root = root->right;
                }
            }
            return end();
        }

        const_iterator upper_bound (const key_type& k) const
        {
            Node<Key, T>* root = _rb.root;

            while (!root->isNull)
            {
                if (_comp(root->_data.first, k) == false)
                {
                    if (root->_data.first != k)
                        return iterator(root);
                    else
                        root = root->right;
                }
                else
                {
                    root = root->right;
                }
            }
            return end();
        }

        
        mapped_type& operator[] (const key_type& k)
        {
            return (*((this->insert(make_pair(k,mapped_type()))).first))._data.second;
        }

        allocator_type get_allocator() const
        {
            return _alloc;
        }

        class value_compare : std::binary_function<value_type, value_type, bool>
        { // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            friend class Map;

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

        value_compare value_comp() const
        {
            return value_compare(_comp);
        }

        key_compare key_comp() const
        {
            return _comp;
        }

        pair<iterator,iterator>             equal_range (const key_type& k)
        {
            return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
        }

        pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
            return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
        }
        
    
    private : 
        allocator_type _alloc;
        RBTree<Key, T> _rb;
        key_compare _comp;
        size_type _size;
    };
}

#endif