#ifndef EXAMPLECLASS_HPP
# define EXAMPLECLASS_HPP

#include <iostream>
#include <string>

class exampleClass	{
	public:
		std::string a;
		int			b;
		exampleClass( void ) : a("HelloWorld"), b(42)	{};
		exampleClass( int i ) : a("HelloWorld"), b(i)	{};
		exampleClass( const exampleClass& src ) : a(src.a), b(src.b)	{};
		~exampleClass( void ) {};
		exampleClass & operator=( exampleClass const & rhs )	{
		if ( this != &rhs )
		{
			this->a = rhs.a;
			this->b = rhs.b;
		}
		return *this;
		}
};

inline bool
operator<( const exampleClass& lhs, const exampleClass& rhs ) {
	return (lhs.b < rhs.b);
}

inline bool
operator>( const exampleClass& lhs, const exampleClass& rhs ) {
	return (lhs.b > rhs.b);
}

inline bool
operator==( const exampleClass& lhs, const exampleClass& rhs ) {
	return (lhs.b == rhs.b && lhs.a == rhs.a);
}
inline bool
operator!=( const exampleClass& lhs, const exampleClass& rhs ) {
	return (!(lhs==rhs));
}
inline std::ostream&
operator<<( std::ostream & o, exampleClass const & i )	{
	o << i.b << " - " << i.a;
	return o;
};
#endif
