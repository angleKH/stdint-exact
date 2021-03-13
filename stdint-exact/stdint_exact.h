#ifndef STDINT_EXACT_H
#define STDINT_EXACT_H

//debug
//#include <iostream>

#if __cplusplus >= 201103L
#include <cstdint>
#else
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#endif

#include <cstddef>
#include <iosfwd>
#include <istream>

#if defined(__cpp_impl_three_way_comparison) && defined(__cpp_lib_three_way_comparison)
#include <compare>
#endif

#if __cplusplus >= 201103L
#include <type_traits>
#endif

#ifdef __GNUC__ // These are only used for GCC compiler directives for alignment
#include <climits>
#include <bit>
#endif

#define STDINT_EXACT_H_DETAIL_NAME stdexct_det

#if __cplusplus >= 201103L // if <cstdint> was imported
//Create global aliases for non-exact-width types. It should be legal to do so even if they are already in global (§7.1.3.2: "In a given non-class scope, a typedef specifier can be used to redefine the name of any type declared in that scope to refer to the type to which it already refers." and "A typedef-name can also be introduced by an alias-declaration. The identifier following the using keyword becomes a typedef-name and the optional attribute-specifier-seq following the identifier appertains to that typedef-name. It has the same semantics as if it were introduced by the typedef specifier.")
using std::int_fast8_t;
using std::int_fast16_t;
using std::int_fast32_t;
using std::int_fast64_t;
using std::int_least8_t;
using std::int_least16_t;
using std::int_least32_t;
using std::int_least64_t;
using std::intmax_t;
using std::uint_fast8_t;
using std::uint_fast16_t;
using std::uint_fast32_t;
using std::uint_fast64_t;
using std::uint_least8_t;
using std::uint_least16_t;
using std::uint_least32_t;
using std::uint_least64_t;
using std::uintmax_t;
#ifdef INTPTR_MAX
using std::intptr_t;
#endif
#ifdef UINTPTR_MAX
using std::uintptr_t;
#endif
#endif

namespace STDINT_EXACT_H_DETAIL_NAME {

template<typename underlying_type, uint_fast8_t bits>
struct IntType {
private:
	#if __cplusplus >= 201103L
	// Since the signedness of a bit field type that does not use "signed" or "unsigned" is implementation-defined until C++14, and the fact that typedefs provided by implementations for cstdint may not explicitly use "signed" for signed integers, we force it with std::make_signed
	typename std::conditional<std::is_signed<underlying_type>::value, typename std::make_signed<underlying_type>::type, underlying_type>::type
	#else
	underlying_type
	#endif
	num : bits;
public:

	#if __cplusplus >= 201103L
	#define CONSTEXPR_POLYFILL constexpr
	#else
	#define CONSTEXPR_POLYFILL
	#endif

	//Conversion operators
	template<typename T>
	CONSTEXPR_POLYFILL operator T() {
		return num;
	}
	template<typename T>
	CONSTEXPR_POLYFILL operator T() const {
		return num;
	}
	template<typename T>
	CONSTEXPR_POLYFILL operator T() volatile {
		return num;
	}
	template<typename T>
	CONSTEXPR_POLYFILL operator T() const volatile {
		return num;
	}

	//new
	/*void * operator new(
						#if __cplusplus >= 201103L
						[[maybe_unused]]
						#endif
						std::size_t const _) {
		return ::new IntType();
	};*/

	//void* T::operator new  ( std::size_t count, user-defined-args... );

	//Default constructor
	#if __cplusplus >= 201103L
	IntType() = default;
	#else
	IntType() {};
	#endif

	//TODO Function call operator

	//Copy constructor
	#if __cplusplus >= 201103L
	IntType(IntType const &) = default;
	#else
	IntType(IntType const & x) {
		num = x.num;
	}
	#endif

	//Constructor
	template<typename T>
	CONSTEXPR_POLYFILL IntType(T const x) {
		num = x;
	}

	// copy assignment
	#if __cplusplus >= 201103L
	CONSTEXPR_POLYFILL IntType & operator=(IntType const & x) = default;
	#else
	CONSTEXPR_POLYFILL IntType & operator=(IntType const & x) {
		num = x.num;
		return *this;
	}
	#endif
	#ifndef STDINT_EXACT_NO_VOLATILE
	CONSTEXPR_POLYFILL volatile IntType & operator=(IntType const & x) volatile {
		num = x.num;
		return *this;
	}
	CONSTEXPR_POLYFILL IntType & operator=(IntType const volatile & x) {
		num = x.num;
		return *this;
	}
	CONSTEXPR_POLYFILL volatile IntType & operator=(IntType const volatile & x) volatile {
		num = x.num;
		return *this;
	}
	#endif
	// = operator
	//TODO in c++20, assigning signed int with out of range value is defined
	template<typename T>
	CONSTEXPR_POLYFILL IntType & operator=(T const & x) {
		num = x;
		return *this;
	}
	#ifndef STDINT_EXACT_NO_VOLATILE
	template<typename T>
	CONSTEXPR_POLYFILL IntType volatile & operator=(T const & x) volatile {
		num = x;
		return *this;
	}
	template<typename T>
	CONSTEXPR_POLYFILL IntType & operator=(T const volatile & x) {
		num = x;
		return *this;
	}
	template<typename T>
	CONSTEXPR_POLYFILL IntType volatile & operator=(T const volatile & x) volatile {
		num = x;
		return *this;
	}
	#endif

	template<typename T>
	friend T & operator<<(T & s, IntType & i) {
		return s << i.num;
	}
	template<typename T>
	friend T & operator<<(T & s, IntType const & i) {
		return s << i.num;
	}
	template<typename T>
	friend T & operator<<(T & s, IntType volatile & i) {
		return s << i.num;
	}
	template<typename T>
	friend T & operator<<(T & s, IntType const volatile & i) {
		return s << i.num;
	}

	friend std::istringstream & operator>>(std::istringstream & s, IntType & i) {
		underlying_type n = i.num;
		s >> n;
		i.num = n;
		return s;
	}

	template<typename T>
	friend T & operator>>(T & s, IntType & i) {
		return s >> i.num;
	}
	template<typename T>
	friend T & operator>>(T & s, IntType const & i) {
		return s >> i.num;
	}
	template<typename T>
	friend T & operator>>(T & s, IntType volatile & i) {
		return s >> i.num;
	}
	template<typename T>
	friend T & operator>>(T & s, IntType const volatile & i) {
		return s >> i.num;
	}

#if defined(__cpp_impl_three_way_comparison) && defined(__cpp_lib_three_way_comparison)
//TODO see if this actually works
constexpr std::strong_ordering operator<=>(IntType const &) const = default;
#else
	CONSTEXPR_POLYFILL bool operator==(IntType const & x) const {
		return num == x.num;
	}
	CONSTEXPR_POLYFILL bool operator==(IntType const & x) const volatile {
		return num == x.num;
	}
	CONSTEXPR_POLYFILL bool operator==(IntType const volatile & x) const {
		return num == x.num;
	}
	CONSTEXPR_POLYFILL bool operator==(IntType const volatile & x) const volatile {
		return num == x.num;
	}

	template<typename T>
	CONSTEXPR_POLYFILL bool operator==(T const & x) const {
		return num == x;
	}
	template<typename T>
	CONSTEXPR_POLYFILL bool operator==(T const & x) const volatile {
		return num == x;
	}
	template<typename T>
	CONSTEXPR_POLYFILL bool operator==(T const volatile & x) const {
		return num == x;
	}
	template<typename T>
	CONSTEXPR_POLYFILL bool operator==(T const volatile & x) const volatile {
		return num == x;
	}
	// < operator
	CONSTEXPR_POLYFILL bool operator<(IntType const & x) const {
		return num < x.num;
	}
	CONSTEXPR_POLYFILL bool operator<(IntType const & x) const volatile {
		return num < x.num;
	}
	CONSTEXPR_POLYFILL bool operator<(IntType const volatile & x) const {
		return num < x.num;
	}
	CONSTEXPR_POLYFILL bool operator<(IntType const volatile & x) const volatile {
		return num < x.num;
	}

	template<typename T>
	CONSTEXPR_POLYFILL bool operator<(T const & x) const {
		return num < x;
	}
	template<typename T>
	CONSTEXPR_POLYFILL bool operator<(T const & x) const volatile {
		return num < x;
	}
	template<typename T>
	CONSTEXPR_POLYFILL bool operator<(T const volatile & x) const {
		return num < x;
	}
	template<typename T>
	CONSTEXPR_POLYFILL bool operator<(T const volatile & x) const volatile {
		return num < x;
	}
#endif

#undef CONSTEXPR_POLYFILL

}
#ifdef __GNUC__
//Optional bonus for GCC users, makes std::alignment_of/alignof the same, comment this out if it causes a compile error for whatever reason
__attribute__ ((__packed__,aligned (

#ifdef __cpp_lib_int_pow2
	std::bit_ceil((bits + CHAR_BIT - 1U) / CHAR_BIT)
#else
	//The horrendous code below uses precomputed values for the formula: std::bit_ceil(bits divided by CHAR_BIT rounded up)
	//Since std::log2 is not constexpr, a lookup table made with ternary operators is used to make this a compile time expression (and for C++98 support)
	bits==8?(CHAR_BIT==1?8:(CHAR_BIT==2?4:(CHAR_BIT==3?4:(CHAR_BIT==4?2:(CHAR_BIT==5?2:(CHAR_BIT==6?2:(CHAR_BIT==7?2:1))))))):(bits==16?(CHAR_BIT==1?16:(CHAR_BIT==2?8:(CHAR_BIT==3?8:(CHAR_BIT==4?4:(CHAR_BIT==5?4:(CHAR_BIT==6?4:(CHAR_BIT==7?4:(CHAR_BIT==8?2:(CHAR_BIT==9?2:(CHAR_BIT==10?2:(CHAR_BIT==11?2:(CHAR_BIT==12?2:(CHAR_BIT==13?2:(CHAR_BIT==14?2:(CHAR_BIT==15?2:1))))))))))))))):(bits==32?(CHAR_BIT==1?32:(CHAR_BIT==2?16:(CHAR_BIT==3?16:(CHAR_BIT==4?8:(CHAR_BIT==5?8:(CHAR_BIT==6?8:(CHAR_BIT==7?8:(CHAR_BIT==8?4:(CHAR_BIT==9?4:(CHAR_BIT==10?4:(CHAR_BIT==11?4:(CHAR_BIT==12?4:(CHAR_BIT==13?4:(CHAR_BIT==14?4:(CHAR_BIT==15?4:(CHAR_BIT==16?2:(CHAR_BIT==17?2:(CHAR_BIT==18?2:(CHAR_BIT==19?2:(CHAR_BIT==20?2:(CHAR_BIT==21?2:(CHAR_BIT==22?2:(CHAR_BIT==23?2:(CHAR_BIT==24?2:(CHAR_BIT==25?2:(CHAR_BIT==26?2:(CHAR_BIT==27?2:(CHAR_BIT==28?2:(CHAR_BIT==29?2:(CHAR_BIT==30?2:(CHAR_BIT==31?2:1))))))))))))))))))))))))))))))):(bits==64?(CHAR_BIT==1?64:(CHAR_BIT==2?32:(CHAR_BIT==3?32:(CHAR_BIT==4?16:(CHAR_BIT==5?16:(CHAR_BIT==6?16:(CHAR_BIT==7?16:(CHAR_BIT==8?8:(CHAR_BIT==9?8:(CHAR_BIT==10?8:(CHAR_BIT==11?8:(CHAR_BIT==12?8:(CHAR_BIT==13?8:(CHAR_BIT==14?8:(CHAR_BIT==15?8:(CHAR_BIT==16?4:(CHAR_BIT==17?4:(CHAR_BIT==18?4:(CHAR_BIT==19?4:(CHAR_BIT==20?4:(CHAR_BIT==21?4:(CHAR_BIT==22?4:(CHAR_BIT==23?4:(CHAR_BIT==24?4:(CHAR_BIT==25?4:(CHAR_BIT==26?4:(CHAR_BIT==27?4:(CHAR_BIT==28?4:(CHAR_BIT==29?4:(CHAR_BIT==30?4:(CHAR_BIT==31?4:(CHAR_BIT==32?2:(CHAR_BIT==33?2:(CHAR_BIT==34?2:(CHAR_BIT==35?2:(CHAR_BIT==36?2:(CHAR_BIT==37?2:(CHAR_BIT==38?2:(CHAR_BIT==39?2:(CHAR_BIT==40?2:(CHAR_BIT==41?2:(CHAR_BIT==42?2:(CHAR_BIT==43?2:(CHAR_BIT==44?2:(CHAR_BIT==45?2:(CHAR_BIT==46?2:(CHAR_BIT==47?2:(CHAR_BIT==48?2:(CHAR_BIT==49?2:(CHAR_BIT==50?2:(CHAR_BIT==51?2:(CHAR_BIT==52?2:(CHAR_BIT==53?2:(CHAR_BIT==54?2:(CHAR_BIT==55?2:(CHAR_BIT==56?2:(CHAR_BIT==57?2:(CHAR_BIT==58?2:(CHAR_BIT==59?2:(CHAR_BIT==60?2:(CHAR_BIT==61?2:(CHAR_BIT==62?2:(CHAR_BIT==63?2:1))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))):1)))
#endif

)))
#endif //__GNUC__
;
typedef STDINT_EXACT_H_DETAIL_NAME::IntType<int_least16_t,16> int16_t;
}

#define STDINT_EXACT_SPECIALIZE_TRAIT(trait_name, type, value) template <> struct trait_name<type> : public std::integral_constant<bool, value> {}

//Since extending the std namespace is technically undefined behavior, this adds to only global namespace. Exact-width types that are already defined in the std namespace are given a global alias.
#ifndef INT16_MAX
using STDINT_EXACT_H_DETAIL_NAME::int16_t;
#ifdef STDINT_EXACT_EXTEND_STD
namespace std {
	using ::int16_t;
}
#endif
#define INT16_MIN (-32768)
#define INT16_MAX 32767
//STDINT_EXACT_SPECIALIZE_TRAIT(std::is_integral, int16_t, true);

#elif __cplusplus >= 201103L
using std::int16_t;
#endif // INT16_MAX

#undef STDINT_EXACT_SPECIALIZE_TRAIT

/*
-(2^(n-1))
#define INT8_MIN (-128)
#define INT16_MIN (-32768)
#define INT32_MIN (-2147483647 - 1)
#define INT64_MIN  (-9223372036854775807LL - 1)

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807LL

#define UINT8_MAX 255
#define UINT16_MAX 65535
#define UINT32_MAX 0xffffffffU
#define UINT64_MAX 0xffffffffffffffffULL

*/

#undef STDINT_EXACT_H_DETAIL_NAME
#endif
