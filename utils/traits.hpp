#ifndef TRAITS_HPP
#define TRAITS_HPP

namespace ft {
	////////     enable_if ///////////////////
	template<bool, typename T = void>
    struct enable_if 
	{ };
	
	// Partial specialization for true.
	template<typename T>
    struct enable_if<false, T>
    { 
		typedef T type; 
	};
	////////////////////////////////////////
	template <class>
	struct check_type
	{
		typedef void type;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag	{};
	struct random_access_iterator_tag : public bidirectional_iterator_tag{};

	template<class T>
	struct _has_iterator_typedefs
	{
		private:
			struct _two { char _temp[2]; };
			template <class U>
			static _two _test(...);
			template <class U>
			static char _test(typename ft::check_type<typename U::iterator_category>::type * = 0,
							  typename ft::check_type<typename U::difference_type>::type* = 0,
							  typename ft::check_type<typename U::refference>::type* = 0,
							  typename ft::check_type<typename U::pointer>::type * = 0,
							  typename ft::check_type<typename U::value_type>::type* = 0);
		public:
			static const bool value = sizeof(_test<T>(0,0,0,0,0)) == 1;
	};

	template <class T>
	struct _has_iterator_category
	{
		private:
			struct _two { char _temp[2]; };
			template <class U>
			static _two _test(...);
			template <class U>
			static char _test(typename U::iterator_category* = 0);
		public:
			static const bool value = sizeof(_test<T>(0)) == 1;
	};

	template <class Iter, bool>
	struct _iterator_traits {};
	
	template <class Iter>
	struct _iterator_traits<Iter, true>
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <class Iter>
	struct iterator_traits : public _iterator_traits<Iter, _has_iterator_typedefs<Iter>::value> {};


	template <class T>
	class iterator_traits<T *>
	{
	public:
		typedef std::ptrdiff_t differenece_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T *>
	{
	public:
		typedef std::ptrdiff_t differenece_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

}

#endif