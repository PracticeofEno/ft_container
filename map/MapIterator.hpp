#ifndef MAPITERATOR_HPP
#define MAPITERATOR_HPP

#include <memory>
#include <cstddef>


namespace ft
{
	//T is Node<T1,T2>
	template <typename T, typename Pointer, typename Reference, class Category = std::bidirectional_iterator_tag>
	class MapIterator 
	{
		
		public:
			typedef MapIterator<T, Pointer, Reference> this_type;
			typedef MapIterator<T, T*, T&> iterator;
			typedef MapIterator<T, const T*, const T&> const_iterator;
			typedef T value_type;
			typedef Pointer 	pointer;
			typedef Reference 	reference;
			typedef size_t 		size_type;
			typedef ptrdiff_t 	difference_type;
			typedef Category 	iterator_category;
			//template <class T2, class A> friend class vector;
			
			pointer array;
		public:
			MapIterator() : array(NULL) {}
			MapIterator(const pointer elem) : array(elem) {}
			MapIterator(const iterator& x) : array(const_cast<pointer>(x.array)) {}
			virtual ~MapIterator() {}

			this_type& operator=(const iterator& x){
				this->array = x.array;
				return *this;
			}

			this_type operator++(int){
				this_type out(*this);
				array = const_cast<pointer>(array->getNext());
				return out;
			}

			this_type& operator++() {
				array = const_cast<pointer>(array->getNext());
				return *this;
			}

			this_type operator--(int) {
				this_type out(*this);
				array = const_cast<pointer>(array->getPrev());
				return out;
			}

			this_type& operator--() {
				array = const_cast<pointer>(array->getPrev());
				return *this;
			}
            
			value_type& operator*() {
				return array->_data;
			}

			value_type* operator->() {
				return &(array->_data);
			}
			
			template <typename T2, typename P, typename R, class C>
			friend inline bool operator==(const this_type& lhs, const MapIterator<T2, P, R, C>& rhs){
				return (lhs.array == rhs.array);
			}
			template <typename T2, typename P, typename R, class C>
			friend inline bool operator!=(const this_type& lhs, const MapIterator<T2, P, R, C>& rhs){
				return (lhs.array != rhs.array);
			}
	};
}

#endif