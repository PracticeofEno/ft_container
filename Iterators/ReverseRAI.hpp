#ifndef REVERSERAI_HPP
#define REVERSERAI_HPP

template <class Iterator>

class ReverseRAI {
	public:
		typedef Iterator iterator_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::size_type size_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::iterator_category iterator_category;

		ReverseRAI() : current() { }
		explicit ReverseRAI (iterator_type it) : current(it) { }
		template <class Iter>
		ReverseRAI(const ReverseRAI<Iter>& rev_it) : ReverseRAI<Iter>(rev_it.base()) { };
		~ReverseRAI() { }

		ReverseRAI& operator=(const ReverseRAI& tmp) {
			Iterator::operator=(tmp);
			return *this;
		}

		ReverseRAI operator+(difference_type n) const {
			return ReverseRAI(current - n);
		}

		ReverseRAI& operator+=(difference_type n) const {
			this->current -= n;
			return *this;
		}

		ReverseRAI operator-(difference_type n) const {
			return ReverseRAI(current + n);
		}

		ReverseRAI& operator-=(difference_type n) const {
			this->current += n;
			return *this;
		}
		
		reference operator[](difference_type n) {
			return *(*this + n);
		}

		//-----------------------------------------------------------

		iterator_type base() const {
			return this->current;
		}

		reference operator*() {
			return *current;
		}

		ReverseRAI& operator++() {
			--current;
			return *this;
		}

		ReverseRAI operator++(int) {
			ReverseRAI out(*this);
			--current;
			return out;
		}

		ReverseRAI& operator--() {
			++current;
			return *this;
		}

		ReverseRAI operator--(int) {
			ReverseRAI out(*this);
			++current;
			return out;
		}

		pointer operator->() const {
			return &(operator*());
		}

		
	protected: 
		Iterator current;


};

#endif