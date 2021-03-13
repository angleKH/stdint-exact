#define STDINT_EXACT_NO_VOLATILE
#define SIMULATE_REPLACEMENTS

#include <stdint_exact.h>

#ifdef SIMULATE_REPLACEMENTS
#define int16_t stdexct_det::int16_t
#endif

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <sstream>

#undef NDEBUG
#include <cassert>

#if __cplusplus >= 201103L // Functions for type trait matching section of tests
#include <cmath>
#include <climits>

template<template<class T> class trait>
struct compare_with_native {
	constexpr static bool result = trait<int16_t>::value == trait<int_least16_t>::value;
};

uint_fast8_t constexpr calculateBytesNeededForBits(uint_fast8_t bits) {
	return (bits+CHAR_BIT-1)/CHAR_BIT;
}

uint_fast8_t calculateExpectedAlign(uint_fast8_t bits) {
	uint_fast8_t const x = calculateBytesNeededForBits(bits);
	return x == 1 ? 1 : (1U << (static_cast<unsigned int>(std::log2(x-1))+1));
}

#endif

#if __cplusplus >= 201703L
		#define MAYBE_UNUSED_POLYFILL [[maybe_unused]]
#else
		#define MAYBE_UNUSED_POLYFILL
#endif


int main()
{
	//Default constructor tests
	{
		MAYBE_UNUSED_POLYFILL int16_t a;
		MAYBE_UNUSED_POLYFILL int16_t volatile b;
		MAYBE_UNUSED_POLYFILL int16_t c;
		MAYBE_UNUSED_POLYFILL int16_t volatile d;
		int16_t * e = new int16_t;
		delete e;
		delete new int16_t[3];
	}

	//Zero initialization
	{
		static int16_t z;
		assert(z==0);
		//Zero initialization from value initialization
#if __cplusplus >= 201103L
		constexpr int16_t b = int16_t();
		static_assert(b == 0, "");
		int16_t * const e = new int16_t();
		assert((*e) == 0);
		constexpr int16_t a{};
		static_assert(a==0, "");
		int16_t * const p = new int16_t[3]();
		assert(p[0] == 0);
		assert(p[1] == 0);
		assert(p[2] == 0);
		delete[] p;
#endif
	}

	// Direct initialization
	{
		int16_t x(7);
		assert(x==7);
	}


#if __cplusplus >= 201103L
	//constexpr tests
	{
		constexpr int16_t a = 8;
		constexpr int16_t b(8);
		constexpr int16_t c = int16_t(8);
		constexpr int d = 7;
		constexpr int16_t e = (int16_t)d;
		static_assert(a==b, "");
		static_assert(b==c, "");
		static_assert(c==8, "");
		static_assert(d==e, "");
		static_assert(e==7, "");
	}
#endif

	{
		int16_t x = int16_t(7);
		int16_t * const y = new int16_t(7);
		assert(x==7);
		assert(x==(*y));
		delete y;
	}


	//TODO do the logic tests with new also



	//Creation
	int native = 1;
	int const c_native = 2;
	int volatile v_native = 3;
	int const volatile cv_native = 4;
	int16_t custom = 5;
	int16_t volatile v_custom = 6;
	int16_t const c_custom = 7;
	int16_t const volatile cv_custom = 8;

	//Assignment
	native = custom;
	native = v_custom;
	native = c_custom;
	native = cv_custom;
	v_native = custom;
	v_native = v_custom;
	v_native = c_custom;
	v_native = cv_custom;
	custom = native;
	custom = c_native;
	custom = v_native;
	custom = cv_native;
	custom = custom;
	custom = v_custom;
	custom = c_custom;
	custom = cv_custom;
	#ifndef STDINT_EXACT_NO_VOLATILE
	v_custom = native;
	v_custom = c_native;
	v_custom = v_native;
	v_custom = cv_native;
	v_custom = custom;
	v_custom = v_custom;
	v_custom = c_custom;
	v_custom = cv_custom;
	#endif

	//Chained assignment
	native = (v_native = custom);
	native = (v_native = v_custom);
	native = (v_native = c_custom);
	native = (v_native = cv_custom);
	native = (custom = native);
	native = (custom = c_native);
	native = (custom = v_native);
	native = (custom = cv_native);
	native = (custom = custom);
	native = (custom = v_custom);
	native = (custom = c_custom);
	native = (custom = cv_custom);
	#ifndef STDINT_EXACT_NO_VOLATILE
	native = (v_custom = native);
	native = (v_custom = c_native);
	native = (v_custom = v_native);
	native = (v_custom = cv_native);
	native = (v_custom = custom);
	native = (v_custom = v_custom);
	native = (v_custom = c_custom);
	native = (v_custom = cv_custom);
	#endif
	v_native = (native = custom);
	v_native = (native = v_custom);
	v_native = (native = c_custom);
	v_native = (native = cv_custom);
	v_native = (custom = native);
	v_native = (custom = c_native);
	v_native = (custom = v_native);
	v_native = (custom = cv_native);
	v_native = (custom = custom);
	v_native = (custom = v_custom);
	v_native = (custom = c_custom);
	v_native = (custom = cv_custom);
	#ifndef STDINT_EXACT_NO_VOLATILE
	v_native = (v_custom = native);
	v_native = (v_custom = c_native);
	v_native = (v_custom = v_native);
	v_native = (v_custom = cv_native);
	v_native = (v_custom = custom);
	v_native = (v_custom = v_custom);
	v_native = (v_custom = c_custom);
	v_native = (v_custom = cv_custom);
	#endif
	custom = (native = custom);
	custom = (native = v_custom);
	custom = (native = c_custom);
	custom = (native = cv_custom);
	custom = (v_native = custom);
	custom = (v_native = v_custom);
	custom = (v_native = c_custom);
	custom = (v_native = cv_custom);
	#ifndef STDINT_EXACT_NO_VOLATILE
	custom = (v_custom = native);
	custom = (v_custom = c_native);
	custom = (v_custom = v_native);
	custom = (v_custom = cv_native);
	custom = (v_custom = custom);
	custom = (v_custom = v_custom);
	custom = (v_custom = c_custom);
	custom = (v_custom = cv_custom);
	v_custom = (native = custom);
	v_custom = (native = v_custom);
	v_custom = (native = c_custom);
	v_custom = (native = cv_custom);
	v_custom = (v_native = custom);
	v_custom = (v_native = v_custom);
	v_custom = (v_native = c_custom);
	v_custom = (v_native = cv_custom);
	v_custom = (custom = native);
	v_custom = (custom = c_native);
	v_custom = (custom = v_native);
	v_custom = (custom = cv_native);
	v_custom = (custom = custom);
	v_custom = (custom = v_custom);
	v_custom = (custom = c_custom);
	v_custom = (custom = cv_custom);
	#endif
	(v_native = custom) = native;
	(v_native = v_custom) = native;
	(v_native = c_custom) = native;
	(v_native = cv_custom) = native;
	(custom = native) = native;
	(custom = c_native) = native;
	(custom = v_native) = native;
	(custom = cv_native) = native;
	(custom = custom) = native;
	(custom = v_custom) = native;
	(custom = c_custom) = native;
	(custom = cv_custom) = native;
	#ifndef STDINT_EXACT_NO_VOLATILE
	(v_custom = native) = native;
	(v_custom = c_native) = native;
	(v_custom = v_native) = native;
	(v_custom = cv_native) = native;
	(v_custom = custom) = native;
	(v_custom = v_custom) = native;
	(v_custom = c_custom) = native;
	(v_custom = cv_custom) = native;
	#endif
	(native = custom) = c_native;
	(native = v_custom) = c_native;
	(native = c_custom) = c_native;
	(native = cv_custom) = c_native;
	(v_native = custom) = c_native;
	(v_native = v_custom) = c_native;
	(v_native = c_custom) = c_native;
	(v_native = cv_custom) = c_native;
	(custom = native) = c_native;
	(custom = c_native) = c_native;
	(custom = v_native) = c_native;
	(custom = cv_native) = c_native;
	(custom = custom) = c_native;
	(custom = v_custom) = c_native;
	(custom = c_custom) = c_native;
	(custom = cv_custom) = c_native;
	#ifndef STDINT_EXACT_NO_VOLATILE
	(v_custom = native) = c_native;
	(v_custom = c_native) = c_native;
	(v_custom = v_native) = c_native;
	(v_custom = cv_native) = c_native;
	(v_custom = custom) = c_native;
	(v_custom = v_custom) = c_native;
	(v_custom = c_custom) = c_native;
	(v_custom = cv_custom) = c_native;
	#endif
	(native = custom) = v_native;
	(native = v_custom) = v_native;
	(native = c_custom) = v_native;
	(native = cv_custom) = v_native;
	(custom = native) = v_native;
	(custom = c_native) = v_native;
	(custom = v_native) = v_native;
	(custom = cv_native) = v_native;
	(custom = custom) = v_native;
	(custom = v_custom) = v_native;
	(custom = c_custom) = v_native;
	(custom = cv_custom) = v_native;
	#ifndef STDINT_EXACT_NO_VOLATILE
	(v_custom = native) = v_native;
	(v_custom = c_native) = v_native;
	(v_custom = v_native) = v_native;
	(v_custom = cv_native) = v_native;
	(v_custom = custom) = v_native;
	(v_custom = v_custom) = v_native;
	(v_custom = c_custom) = v_native;
	(v_custom = cv_custom) = v_native;
	#endif
	(native = custom) = cv_native;
	(native = v_custom) = cv_native;
	(native = c_custom) = cv_native;
	(native = cv_custom) = cv_native;
	(v_native = custom) = cv_native;
	(v_native = v_custom) = cv_native;
	(v_native = c_custom) = cv_native;
	(v_native = cv_custom) = cv_native;
	(custom = native) = cv_native;
	(custom = c_native) = cv_native;
	(custom = v_native) = cv_native;
	(custom = cv_native) = cv_native;
	(custom = custom) = cv_native;
	(custom = v_custom) = cv_native;
	(custom = c_custom) = cv_native;
	(custom = cv_custom) = cv_native;
	#ifndef STDINT_EXACT_NO_VOLATILE
	(v_custom = native) = cv_native;
	(v_custom = c_native) = cv_native;
	(v_custom = v_native) = cv_native;
	(v_custom = cv_native) = cv_native;
	(v_custom = custom) = cv_native;
	(v_custom = v_custom) = cv_native;
	(v_custom = c_custom) = cv_native;
	(v_custom = cv_custom) = cv_native;
	#endif
	(native = custom) = custom;
	(native = v_custom) = custom;
	(native = c_custom) = custom;
	(native = cv_custom) = custom;
	(v_native = custom) = custom;
	(v_native = v_custom) = custom;
	(v_native = c_custom) = custom;
	(v_native = cv_custom) = custom;
	(custom = native) = custom;
	(custom = c_native) = custom;
	(custom = v_native) = custom;
	(custom = cv_native) = custom;
	(custom = custom) = custom;
	(custom = v_custom) = custom;
	(custom = c_custom) = custom;
	(custom = cv_custom) = custom;
	#ifndef STDINT_EXACT_NO_VOLATILE
	(v_custom = native) = custom;
	(v_custom = c_native) = custom;
	(v_custom = v_native) = custom;
	(v_custom = cv_native) = custom;
	(v_custom = custom) = custom;
	(v_custom = v_custom) = custom;
	(v_custom = c_custom) = custom;
	(v_custom = cv_custom) = custom;
	#endif
	(native = custom) = c_custom;
	(native = v_custom) = c_custom;
	(native = c_custom) = c_custom;
	(native = cv_custom) = c_custom;
	(v_native = custom) = c_custom;
	(v_native = v_custom) = c_custom;
	(v_native = c_custom) = c_custom;
	(v_native = cv_custom) = c_custom;
	(custom = native) = c_custom;
	(custom = c_native) = c_custom;
	(custom = v_native) = c_custom;
	(custom = cv_native) = c_custom;
	(custom = custom) = c_custom;
	(custom = v_custom) = c_custom;
	(custom = c_custom) = c_custom;
	(custom = cv_custom) = c_custom;
	#ifndef STDINT_EXACT_NO_VOLATILE
	(v_custom = native) = c_custom;
	(v_custom = c_native) = c_custom;
	(v_custom = v_native) = c_custom;
	(v_custom = cv_native) = c_custom;
	(v_custom = custom) = c_custom;
	(v_custom = v_custom) = c_custom;
	(v_custom = c_custom) = c_custom;
	(v_custom = cv_custom) = c_custom;
	#endif
	(native = custom) = v_custom;
	(native = v_custom) = v_custom;
	(native = c_custom) = v_custom;
	(native = cv_custom) = v_custom;
	(v_native = custom) = v_custom;
	(v_native = v_custom) = v_custom;
	(v_native = c_custom) = v_custom;
	(v_native = cv_custom) = v_custom;
	(custom = native) = v_custom;
	(custom = c_native) = v_custom;
	(custom = v_native) = v_custom;
	(custom = cv_native) = v_custom;
	(custom = custom) = v_custom;
	(custom = v_custom) = v_custom;
	(custom = c_custom) = v_custom;
	(custom = cv_custom) = v_custom;
	#ifndef STDINT_EXACT_NO_VOLATILE
	(v_custom = native) = v_custom;
	(v_custom = c_native) = v_custom;
	(v_custom = v_native) = v_custom;
	(v_custom = cv_native) = v_custom;
	(v_custom = custom) = v_custom;
	(v_custom = v_custom) = v_custom;
	(v_custom = c_custom) = v_custom;
	(v_custom = cv_custom) = v_custom;
	#endif
	(native = custom) = cv_custom;
	(native = v_custom) = cv_custom;
	(native = c_custom) = cv_custom;
	(native = cv_custom) = cv_custom;
	(v_native = custom) = cv_custom;
	(v_native = v_custom) = cv_custom;
	(v_native = c_custom) = cv_custom;
	(v_native = cv_custom) = cv_custom;
	(custom = native) = cv_custom;
	(custom = c_native) = cv_custom;
	(custom = v_native) = cv_custom;
	(custom = cv_native) = cv_custom;
	(custom = custom) = cv_custom;
	(custom = v_custom) = cv_custom;
	(custom = c_custom) = cv_custom;
	(custom = cv_custom) = cv_custom;
	#ifndef STDINT_EXACT_NO_VOLATILE
	(v_custom = native) = cv_custom;
	(v_custom = c_native) = cv_custom;
	(v_custom = v_native) = cv_custom;
	(v_custom = cv_native) = cv_custom;
	(v_custom = custom) = cv_custom;
	(v_custom = v_custom) = cv_custom;
	(v_custom = c_custom) = cv_custom;
	(v_custom = cv_custom) = cv_custom;
	#endif
	{
		int16_t a = 1;
		int16_t b = 2;
		int16_t c = 3;
		int16_t d = 4;
		int16_t e = 5;
		int16_t f = 6;
		(a = b) = c;
		d = (e = f);

		assert(a==3);
		assert(b==2);
		assert(c==3);
		assert(d==6);
		assert(e==6);
		assert(f==6);
	}

	//These should cause errors when uncommented
//	int16_t const c;
//	int16_t const volatile d;
//	c_custom = native;
//	c_custom = c_native;
//	c_custom = v_native;
//	c_custom = cv_native;
//	c_custom = custom;
//	c_custom = v_custom;
//	c_custom = c_custom;
//	c_custom = cv_custom;
//	cv_custom = native;
//	cv_custom = c_native;
//	cv_custom = v_native;
//	cv_custom = cv_native;
//	cv_custom = custom;
//	cv_custom = v_custom;
//	cv_custom = c_custom;
//	cv_custom = cv_custom;

	//Operator << (stream)
	std::cout<<"Stream operator << tests:"<<'\n';
	std::cout<<custom<<'\n';
	std::cout<<c_custom<<'\n';
	std::cout<<v_custom<<'\n';
	std::cout<<cv_custom<<'\n';

	std::istringstream istream("20");
	istream >> custom;
	//istream>>c_custom; // Should cause error
	#ifndef STDINT_EXACT_NO_VOLATILE
	//istream >> v_custom; // Should cause error
	//istream>>cv_custom; // Should cause error
	#endif

	assert(custom == 20);


	//Operator ==
	native == custom;
	native == v_custom;
	native == c_custom;
	native == cv_custom;
	v_native == custom;
	v_native == v_custom;
	v_native == c_custom;
	v_native == cv_custom;
	custom == native;
	custom == c_native;
	custom == v_native;
	custom == cv_native;
	custom == custom;
	custom == v_custom;
	custom == c_custom;
	custom == cv_custom;
	#ifndef STDINT_EXACT_NO_VOLATILE
	v_custom == native;
	v_custom == c_native;
	v_custom == v_native;
	v_custom == cv_native;
	v_custom == custom;
	v_custom == v_custom;
	v_custom == c_custom;
	v_custom == cv_custom;
	#endif

	{
		int16_t * const x = new int16_t(117);
		int16_t * const y = (int16_t *)std::malloc(sizeof(*x));
		std::memcpy(y, x, sizeof(*x));

		assert((*x) == (*y));
		assert((*x) == 117);
		assert((*y) == 117);

		delete x;
		std::free(y);

		//TODO test with assigning signed value out of range
	}

	{
		int16_t f(); // Should be a function declaration (most vexing parse)
		//f should be a function for all C++ versions, but I only know how to test it without std::is_function so that's why the below has the C++11 check
		#if __cplusplus >= 201103L
		static_assert(std::is_function<decltype(f)>::value, "");
		#endif
	}

	//TODO check bitshift operations with native ones, if native ones exist, iterate through every number and perform bit shifts and compare stdexact values with native values

	//TODO check if IntegralType functions accept replacements

	//Don't test right shifts by negative amounts (implementation defined), or left shift by negative amounts (undefined)

/* TODO

Signed integer overflow may be newly defined in C++20

*/

	#if __cplusplus >= 201103L
	std::cout<<"\n=Type trait matching=\n";

	std::vector<char const *> matches;
	std::vector<char const *> not_matches;

	#define COMPARE_AND_ADD_TO_VECTOR(trait_name) ((compare_with_native<trait_name>::result ? matches : not_matches).push_back(#trait_name))

	COMPARE_AND_ADD_TO_VECTOR(std::is_void);
	COMPARE_AND_ADD_TO_VECTOR(std::is_null_pointer);
	COMPARE_AND_ADD_TO_VECTOR(std::is_integral);
	COMPARE_AND_ADD_TO_VECTOR(std::is_floating_point);
	COMPARE_AND_ADD_TO_VECTOR(std::is_array);
	COMPARE_AND_ADD_TO_VECTOR(std::is_enum);
	COMPARE_AND_ADD_TO_VECTOR(std::is_union);
	COMPARE_AND_ADD_TO_VECTOR(std::is_class);
	COMPARE_AND_ADD_TO_VECTOR(std::is_function);
	COMPARE_AND_ADD_TO_VECTOR(std::is_pointer);
	COMPARE_AND_ADD_TO_VECTOR(std::is_member_object_pointer);
	COMPARE_AND_ADD_TO_VECTOR(std::is_member_function_pointer);
	COMPARE_AND_ADD_TO_VECTOR(std::is_fundamental);
	COMPARE_AND_ADD_TO_VECTOR(std::is_arithmetic);
	COMPARE_AND_ADD_TO_VECTOR(std::is_scalar);
	COMPARE_AND_ADD_TO_VECTOR(std::is_object);
	COMPARE_AND_ADD_TO_VECTOR(std::is_compound);
	COMPARE_AND_ADD_TO_VECTOR(std::is_reference);
	COMPARE_AND_ADD_TO_VECTOR(std::is_member_pointer);
	COMPARE_AND_ADD_TO_VECTOR(std::is_trivial);
	COMPARE_AND_ADD_TO_VECTOR(std::is_trivially_copyable);
	COMPARE_AND_ADD_TO_VECTOR(std::is_standard_layout);
	COMPARE_AND_ADD_TO_VECTOR(std::is_empty);
	COMPARE_AND_ADD_TO_VECTOR(std::is_polymorphic);
	COMPARE_AND_ADD_TO_VECTOR(std::is_abstract);
	COMPARE_AND_ADD_TO_VECTOR(std::is_signed);
	COMPARE_AND_ADD_TO_VECTOR(std::is_unsigned);
	COMPARE_AND_ADD_TO_VECTOR(std::is_default_constructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_trivially_default_constructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_nothrow_default_constructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_copy_constructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_trivially_copy_constructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_nothrow_copy_constructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_move_constructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_trivially_move_constructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_nothrow_move_constructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_copy_assignable);
	COMPARE_AND_ADD_TO_VECTOR(std::is_trivially_copy_assignable);
	COMPARE_AND_ADD_TO_VECTOR(std::is_nothrow_copy_assignable);
	COMPARE_AND_ADD_TO_VECTOR(std::is_move_assignable);
	COMPARE_AND_ADD_TO_VECTOR(std::is_trivially_move_assignable);
	COMPARE_AND_ADD_TO_VECTOR(std::is_nothrow_move_assignable);
	COMPARE_AND_ADD_TO_VECTOR(std::is_destructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_trivially_destructible);
	COMPARE_AND_ADD_TO_VECTOR(std::is_nothrow_destructible);
	COMPARE_AND_ADD_TO_VECTOR(std::has_virtual_destructor);
	((std::alignment_of<int16_t>::value == calculateExpectedAlign(16) ? matches : not_matches).push_back("std::alignment_of"));

	#if __cplusplus >= 201402L
	COMPARE_AND_ADD_TO_VECTOR(std::is_final);
	#endif
	#if __cplusplus >= 201703L
	COMPARE_AND_ADD_TO_VECTOR(std::has_unique_object_representations);
	COMPARE_AND_ADD_TO_VECTOR(std::is_aggregate);
	COMPARE_AND_ADD_TO_VECTOR(std::is_swappable);
	COMPARE_AND_ADD_TO_VECTOR(std::is_nothrow_swappable);
	#endif
	#ifdef __cpp_lib_bounded_array_traits
	COMPARE_AND_ADD_TO_VECTOR(std::is_bounded_array);
	COMPARE_AND_ADD_TO_VECTOR(std::is_unbounded_array);
	#endif

	#undef COMPARE_AND_ADD_TO_VECTOR

	//sizeof and alignof
	((sizeof(int16_t) == calculateBytesNeededForBits(16) ? matches : not_matches).push_back("sizeof operator"));
	((alignof(int16_t) == calculateExpectedAlign(16) ? matches : not_matches).push_back("std::alignment_of"));

	std::cout<<"==Matches==\n";
	for (auto const & s : matches) {
		std::cout<<s<<'\n';
	}

	std::cout<<"\n==Failed to match==\n";
	for (auto const & s : not_matches) {
		std::cout<<s<<'\n';
	}


	#endif

	return 0;
}
#undef int16_t
