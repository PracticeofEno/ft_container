#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <iostream>

namespace ft {

	template <typename T, class A = std::allocator<T> >
	class vector {
		typedef A allocator_type;
		typedef typename A::value_type value_type;
		typedef typename A::pointer pointer;
		typedef typename A::const_pointer const_pointer;
		typedef typename A::reference reference;
		typedef typename A::const_reference const_reference;
		typedef typename A::difference_type difference_type;
		typedef typename A::size_type size_type;


		public :
			//default
			explicit vector (const allocator_type& alloc = std::allocator<T>())
			{
				_alloc = alloc;
			}
			//fill
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = std::allocator<T>())
			{
				(void)n;
				(void)val;
				(void)alloc;
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = std::allocator<T>());
			vector (const vector& tmp);
			~vector()
			{

			}
			vector& operator =(const vector& tmp);

		class Iterator {
			public :
				typedef typename A::difference_type difference_type;
				typedef typename A::value_type value_type;
				typedef typename A::reference reference;
				typedef typename A::pointer pointer;
				typedef std::random_access_iterator_tag iterator_category;

			protected:
		};

		protected:
			std::allocator<T> _alloc;
			pointer _pointer;
			size_type _capacity;
			size_type _size;
	};
}

#endif