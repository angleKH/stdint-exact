Development for this library is incomplete due to lack of time and practicality to justify sinking time into it, but it is left up as a code reference since this library does some unique things no other library seems to have done before.

----

# Guaranteed exact-width integer types for C++
A header-only library for exact-width integer types.

## TL;DR
Include this library whenever you use exact-width types like ``int32_t``. See the options section for options.

## About
The C++ header `<cstdint>` defines portable fixed-width integer types. However, only the "fast" and "least" types are guaranteed to exist on all implementations, while the exact-width integer types like `int16_t` are **optional, and not guaranteed**.

This library, when included, defines exact-width integer types and their corresponding macros for types that do not exist. The types are defined in the global namespace, and optionally in the std namespace (see Options section of this document). If a type already exists, it does nothing for that type. For example, if an implementation does not define ``int64_t``, it will define ``int64_t`` as well as the macros ``INT64_MIN`` and ``INT64_MAX``. The defined replacements should act exactly as if the implementation supported the native type (e.g. can be used anywhere a native one would, ``uint32_t`` wraps around to 0 as if there are 32 bits, etc.).

In addition, global type aliases are provided for all types that are included by `<cstdint>`. (The standard only requires that types in `<cstdint>` are in the std namespace, whether they are also in the global namespace is unspecified behavior.)

The library supports C++11 to C++20, and should be compatible with future versions of the standard as well, provided there are no breaking changes in the standard. Support for C++98 is provided, but not guaranteed, as the ``<stdint.h>`` and ``<cstdint>`` headers are not in the C++ standard until C++11.

## Rationale
This library gives peace of mind to those who want to use the fixed-width integer types while still writing completely standards-compliant, well-defined, and portable code, and don't want to rely on implementation-defined behavior. It provides a guarantee that the exact-width types may always be used. It is for those who need to use the size and bits of a number in a meaningful way. For most general purposes the "fast" or "least" integer types would still be preferred, since the replacements may differ in slight ways.

A practical example use case is using PRNGs, which make heavy use of overflow and fixed-width types.

## Differences from native exact-width integer types
Reminder: These differences are only for the replacements. If a type is defined in your implementation, the library leaves it alone.\
These differences arise from limitations:
* The ``sizeof`` operator will return the size of the corresponding minimum-width integer type (e.g. ``int_least32_t`` for ``int32_t``).
* The ``alignof`` operator may return a different result.
	* For GCC users, this library uses compiler directives to make the alignment the same.
* Debugging info will be different.
* Traits that would normally be true such as ``std::is_fundamental`` will return false.
	* Attempting to specialize them is undefined behavior, so this can't be fixed.
	* You can try to change this, see the Options section.

The following is undefined behavior for this library:
* All regular undefined behavior for the corresponding integer type (e.g. division by zero)
* Attempting to extend from the structs or classes used as implementation details
* Attempting to default initialize a const integer type (e.g. `uint32_t const x;`)
	* This is not possible to forbid for the replacements with the way C++ works.

## How to use
As a header-only library, simply include the ``stdint_exact.h`` file to use it. If you are using a git-based project, you can include the main repository as a submodule.

Due to the nature of this library, ordering matters, so you must include it before other libraries that use exact-width types.

```cpp
#include <iostream>
#include <stdint_exact.h> // The library includes <cstdint> if it is not included already (or <stdint.h> pre-C++11).

int main()
{
	int16_t x = 7;
	std::cout<<x<<'\n';

	//The above will always compile and print 7, on any C++ versison, on any standards-conforming compiler.
	return 0;
}
```

## Options
Define these macros before inclusion, either through compiler options or the ``#define`` directive, for their effects:
* ``STDINT_EXACT_NO_VOLATILE``: This allows the replacement to match more type traits (e.g. ``std::is_trivially_copyable``) at the cost of the ability to use volatile.
* ``STDINT_EXACT_ATTEMPT_UNDEFINED``: Enables all of the macros below. They attempt to perform undefined behavior in order to make replacements match more closely. The macros can also be enabled individually. This may be useful for using external libraries you have no control over.
	* ``STDINT_EXACT_INJECT_STD``: Attempt to add the replacements to the std namespace anyway, even though it is undefined behavior for user programs. This is useful when you must use an external library that you cannot change that uses fully qualified type names from ``<cstdint>``.
	*``STDINT_EXACT_FORCE_TYPE_TRAITS``: Specializes the templates in <type_traits> so that the replacements would match a native one.

