#ifndef MAPREVERSEITERATOR_HPP
#define MAPREVERSEITERATOR_HPP

template <class Iterator>
class MapReverseIterator {
	public:
		typedef Iterator iterator_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::size_type size_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;

		MapReverseIterator() : current() { }
		explicit MapReverseIterator (iterator_type it) : current(it) { }
		template <class Iter>
		MapReverseIterator(const MapReverseIterator<Iter>& rev_it) : MapReverseIterator<Iter>(rev_it.base()) { };
		~MapReverseIterator() { }

		MapReverseIterator& operator=(const MapReverseIterator& tmp) {
			current = tmp.getCurrent();
			//Iterator::operator=(tmp);
			return *this;
		}

		iterator_type base() const {
			return this->current;
		}

		MapReverseIterator& operator++() {
			--current;
			return *this;
		}

		MapReverseIterator operator++(int) {
			MapReverseIterator out(*this);
			--current;
			return out;
		}

		MapReverseIterator& operator--() {
			++current;
			return *this;
		}

		MapReverseIterator operator--(int) {
			MapReverseIterator out(*this);
			++current;
			return out;
		}

		value_type& operator*() {
			return *current;
		}

		value_type* operator->() {
			return &(*current);
		}		

	protected: 
		Iterator current;

	private:
		Iterator getCurrent() const { return current; }


};

template <typename Iterator>
inline bool	operator==(const MapReverseIterator<Iterator>& lhs, const MapReverseIterator<Iterator>& rhs) {
	return (lhs.base() == rhs.base());
}

template <typename Iterator>
inline bool	operator!=(const MapReverseIterator<Iterator>& lhs, const MapReverseIterator<Iterator>& rhs) {
	return !(lhs == rhs);
}

// Comparison of reverse_iterator to const reverse iterator
template <typename IteratorL, typename IteratorR>
inline bool operator==(const MapReverseIterator<IteratorL>& lhs, const MapReverseIterator<IteratorR>& rhs) {
	return (lhs.base() == rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator!=(const MapReverseIterator<IteratorL>& lhs, const MapReverseIterator<IteratorR>& rhs) {
	return !(lhs == rhs);
}


#endif