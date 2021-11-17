#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <math.h>
#include "../Iterators/RandomAccessIterator.hpp"
#include "../Iterators/ReverseRAI.hpp"
#include "../utils/traits.hpp"
#include "../utils/util.hpp"

namespace ft {

	template <typename T, class A = std::allocator<T> >
	class vector {
		public :
			typedef A allocator_type;
			typedef typename A::value_type value_type;
			typedef typename A::pointer pointer;
			typedef typename A::const_pointer const_pointer;
			typedef typename A::reference reference;
			typedef typename A::const_reference const_reference;
			typedef typename A::difference_type difference_type;
			typedef typename A::size_type size_type;

			typedef RandomAccessIterator<T, T*, T&> iterator;
			typedef RandomAccessIterator<T, const T*, const T&> const_iterator;
			typedef ReverseRAI<iterator> reverse_iterator;
			typedef ReverseRAI<const_iterator> const_reverse_iterator;

			vector (const allocator_type& alloc = std::allocator<T>())
			{ 
				_alloc = alloc;
				_data = 0;
				_size = 0;
				_capacity = 0;
			}
			//fill
			vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = std::allocator<T>())
			{
				_alloc = alloc;
				_data = 0;
				_size = 0;
				_capacity = 0;
				if (n > max_size())
				{
					throw std::bad_alloc();
				}
				else
				{
					_data = _alloc.allocate(n);
					if (_data == 0)
						throw std::bad_alloc();
					_capacity = n;
					for (size_type i = 0; i < n; i++)
					{
						_data[i] = val;
						_size++;
					}
				}
			}
			//typename = std::_RequireInputIter<_InputIterator>>
			template <class InputIter>
			vector(InputIter first, InputIter last, const allocator_type& alloc = std::allocator<T>(), 
					typename ft::enable_if<ft::is_integral<InputIter>::value, void>::type* = 0) 
			{
				_alloc = alloc;
				_data = 0;
				_size = 0;
				_capacity = 0;
				size_type n = ft::distance(first, last);
				reserve(n);
				while (first != last)
				{
					push_back(*first);
					first++;
				}
			}
			vector (vector& tmp)
			{
				_data = 0;
				_size = 0;
				_capacity = 0;
				*this = tmp;
			}
			~vector()
			{
				_alloc.deallocate(_data, _size);
			}
			vector& operator=(vector& tmp)
			{
				assign(tmp.begin(), tmp.end());
				return *this;
			}

			/*			Element access				*/
			reference operator[] (size_type n)
			{
				return *(_data + n);
			}

			const_reference operator[] (size_type n) const
			{
				return *(_data + n);
			}

			reference at (size_type n)
			{
				if (n <= 0 || n >= _size)
					throw std::out_of_range("out of range");
				return _data[n];
			}
			const_reference at (size_type n) const {
				if (n <= 0 || n >= _size)
					throw std::out_of_range("out of range");
				return _data[n];
			}

			reference front() {
				return *_data;
			}
			const_reference front() const {
				return *_data;
			}
			reference back() {
				return *(_data + _size - 1);
			}
			const_reference back() const {
				return *(_data + _size - 1);
			}
			/*****************************************/

			/*				capacity				*/
			size_type max_size() const {
				return _alloc.max_size();
			}

			size_type size(void) const {
				return (_size);
			}

			void resize (size_type n, value_type val = value_type()){
				while (n < this->_size)
					pop_back();
				if (n > this->_capacity)
					reserve(n);
				while (n > this->_size)
					push_back(val);
			};

			size_type capacity() const {
				return (_capacity);
			}

			bool empty() const {
				if (_size == 0)
					return (true);
				return (false);
			}

			void reserve(size_type n)
			{
				pointer tmp;
				if (n > _capacity)
				{
					if (n > max_size())
					{
						throw std::length_error("length_error");
					}
					tmp = _alloc.allocate(n);
					if (tmp == 0)
						throw std::bad_alloc();
					for (size_type i = 0; i < _size; i++)
					{
						tmp[i] = _data[i];
					}
					if (_data != 0)
						_alloc.deallocate(_data, _size);
					_data = tmp;
					_capacity = n;
				}
			}
			/*****************************************/

			/*				Modifiers				*/
			template <class InputIter>
			void assign(InputIter first, InputIter last, 
							typename ft::enable_if<ft::is_integral<InputIter>::value, void>::type* = 0)
			{
				clear();
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}

			void assign(size_type n, const value_type& val = value_type())
			{
				clear();
				while (n)
				{
					push_back(val);
					n--;
				}
			}

			void push_back(const value_type& val)
			{
				if (_size + 1 > _capacity)
					realloc(_size + 1);
				_data[_size] = val;
				_size++;
			}

			void pop_back()
			{
				if (_size > 0)
					_size = _size - 1;
			}

			iterator insert(iterator position, const value_type& val)
			{
				size_type n = ft::distance(begin(), position);
				insert(position, 1, val);
				return (iterator(&_data[n]));
			}
			
			void insert(iterator position, size_type n, const value_type& val) 
			{
				vector tmp(position, end());
				_size -= ft::distance(position, end());
				for (size_type i = 0; i < n; i ++)
					push_back(val);
				iterator it = tmp.begin();
				while (it != tmp.end())
				{
					push_back(*it);
					it++;
				}
			}
			template <class InputIter>
			void insert(iterator position, InputIter first , InputIter last, 
							typename ft::enable_if<ft::is_integral<InputIter>::value, void>::type* = 0)
			{
				vector tmp(position, end());
				_size -= ft::distance(position, end());
				while (first != last)
				{
					push_back(*first);
					first++;
				}
				iterator it = tmp.begin();
				while (it != tmp.end())
				{
					push_back(*it);
					it++;
				}
			}

			iterator erase (iterator position)
			{
				iterator it(position);
				while (position != end())
				{
					*position = *(position + 1);
					position++;
				}
				_size = _size - 1 ;
				return it;
			}

			iterator erase (iterator first, iterator last)
			{
				iterator it(last);
				while (last != end()) {
					*first = *last;
					++first;
					++last;
				}
				_size = _size - ft::distance(first, last);
				return it;
			}

			void clear() {
				while (_size)
					pop_back();
			}

			void swap(vector& x)
			{
				vector tmp(x);
				x = *this;
				*this = tmp;
			}

			/*****************************************/

			/*				iterator				*/
			iterator begin(void) {
				return iterator(_data);
			}
			const_iterator begin() const {
				return const_iterator(_data);
			}

			iterator end(void) {
				return iterator(_data + _size);
			}
			const_iterator end(void) const {
				return const_iterator(_data + _size);
			}

			reverse_iterator rbegin(void) {
				return reverse_iterator(_data + _size - 1);
			}

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(_data + _size - 1);
			}

			reverse_iterator rend() {
				return reverse_iterator(_data - 1);
			}

			const_reverse_iterator rend() const {
				return const_reverse_iterator(_data - 1);
			}

			/*****************************************/
			allocator_type get_allocator() const {
				return _alloc;
			}
			

		protected:
			std::allocator<T> _alloc;
			pointer _data;
			size_type _capacity;
			size_type _size;

		private:
			void realloc(size_type n)
			{
				pointer tmp;
				size_type capatmp;

				capatmp = _capacity;
				while (capatmp < n)
				{
					if (capatmp == 0)
						capatmp = 1;
					else
						capatmp = capatmp * 2;
				}
				tmp = _alloc.allocate(capatmp);
				if (tmp == 0)
					throw std::bad_alloc();
				for (size_type i = 0; i < _size; i++)
					tmp[i] = _data[i];
				if (capatmp != 1)
					_alloc.deallocate(_data, _size);
				_data = tmp;
				_capacity = capatmp;
			}
	};
/*
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), &ft::lessthan<T>);
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), &ft::more<T>);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), &ft::morethan<T>);
	}
	*/
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		vector<T,Alloc>	tmp(x);
		x = y;
		y = tmp;
	}
}

#endif