#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <iostream>
#include <math.h>
#include "RandomAccessIterator.hpp"
#include "ReverseRAI.hpp"
#include "traits.hpp"
#include "util.hpp"

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
			typedef ReverseRAI<const iterator> const_reverse_iterator;

			vector (const allocator_type& alloc = std::allocator<T>())
			{
				_size = 0;
				_capacity = 0;
				_data = 0;
				_alloc = alloc;
			}
			//fill
			vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = std::allocator<T>())
			{
				_alloc = alloc;
				_data = _alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
				{
					_data[i] = val;
				}
				_size = n;
				_capacity = n;
			}
			//typename = std::_RequireInputIter<_InputIterator>>
			template <class InputIter>
			vector(InputIter first, InputIter last, const allocator_type& alloc = std::allocator<T>(), 
					typename ft::enable_if<ft::is_integral<InputIter>::value, void>::type* = 0)
			{
				int n = 0;
				_alloc = alloc;
				while (first != last)
				{
					n++;
					first++;
				}
				_data = _alloc.allocate(n);
				_size = n;
				_capacity = n;
			}
			vector (const vector& tmp)
			{
				*this = tmp;
			}
			~vector()
			{
				delete[] this->_data;
			}
			vector& operator =(const vector& tmp)
			{
				delete[] this->_data;
				this->_data = new value_type[tmp._capacity];
				this->_capacity = tmp._capacity;
				this->size = 0;
				this->assign(tmp.begin(), tmp.end());
				return *this;
			}

			/*			Element access				*/
			reference operator[] (size_type n)
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
				return *_data[_size - 1];
			}
			const_reference back() const {
				return *_data[_size - 1];
			}
			/*****************************************/

			/*				capacity				*/
			size_type max_size() const {
				size_t tmp = CatchOS<sizeof(size_t)>();
				return (( pow(2,tmp) / sizeof(T) ) - 1);
			}

			size_type size(void) const {
				return (_size);
			}

			void resize (size_type n, value_type val = value_type()){
				pointer tmp;
				tmp = _alloc.allocate(n);

				if (n <= _capacity)
				{
					for(size_type i = 0; i < n; i ++)
						tmp[i] = _data[i];
				}
				else
				{
					for(size_type i = 0; i < _size; i++)
						tmp[i] = _data[i];
					for(size_type i = _size; i < n; i++)
						tmp[i] = val;
					_capacity = n;
				}
				_alloc.deallocate(_data, _size);
				_size = n;
				_data = tmp;
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
					delete[] _data;
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

			void assign(size_type n, const value_type& val)
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
/*
			iterator insert(iterator position, const value_type& val)
			{
				
			}
			*/
			void insert(iterator position, size_type n, const value_type& val) 
			{
			}
/*
			template <class InputIter>
			void insert(iterator position, InputIter first , InputIter last, 
							typename ft::enable_if<ft::is_integral<InputIter>::value, void>::type* = 0)
			{
				
			}
*/
			/*****************************************/

			/*				iterator				*/
			iterator begin(void) {
				return iterator(_data);
			}
			iterator end(void) {
				return iterator(&_data[_size]);
			}
			/*****************************************/

			void clear() {
				while (_size)
					pop_back();
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
				_alloc.deallocate(_data, _size);
				_data = tmp;
				_capacity = capatmp;
			}
	};

	
}

#endif