// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CONFIGURATION_COMPILER_GCC_HPP
#define MAX_COMPILING_CONFIGURATION_COMPILER_GCC_HPP

#include <version>

#include <max/Compiling/Macros.hpp>

#define MAX_COMPILER_GCC

#define MAX_COMPILER_MESSAGE( Message ) _Pragma( MAX_STRINGIFY( message( Message ) ) )

#define MAX_COMPILER_VERSION_MAJOR __GNUC__
#define MAX_COMPILER_VERSION_MINOR __GNUC_MINOR__
#if __GNUC__ >= 3
	// __GNUC_PATCHLEVEL__ is new to GCC 3.0
	#define MAX_COMPILER_VERSION_PATCH __GNUC_PATCHLEVEL__
#else
	#define MAX_COMPILER_VERSION_PATCH 0
#endif


#if __cplusplus > 202100L
	MAX_COMPILER_MESSAGE( "Compiling with a newer version of C++ than max recognizes. Using last known version." );
#elif __cplusplus >= 202100L
	#define MAX_CPP_2B
	#define MAX_CPP_20
#elif __cplusplus >= 202002L
	#define MAX_CPP_2A
	#define MAX_CPP_20
#elif __cplusplus >= 201709L
	#define MAX_CPP_2A
	#define MAX_CPP_17
#elif __cplusplus >= 201703L
	#define MAX_CPP_1Z
	#define MAX_CPP_17
#elif __cplusplus >= 201500L
	#define MAX_CPP_1Z
	#define MAX_CPP_17
#elif __cplusplus >= 201402L
	#define MAX_CPP_14
#elif __cplusplus >= 201103L
	#define MAX_CPP_11
#elif __cplusplus >= 199711L
	#define MAX_CPP_03
#endif

#if defined(__EXCEPTIONS)
	#define MAX_EXCEPTIONS_SUPPORTED
#endif

#if MAX_COMPILER_VERSION_AT_LEAST( 4, 4, 0 ) && defined( __GXX_EXPERIMENTAL_CXX0X__ )
	#define MAX_INLINE_NAMESPACES_SUPPORTED
#endif

#if MAX_COMPILER_VERSION_AT_LEAST( 4, 6, 0 )
	#define MAX_CONSTEXPR_SUPPORTED
	#if defined( __GXX_EXPERIMENTAL_CXX0X__ )
		#define MAX_NOEXCEPT_SUPPORTED
	#endif
#endif

#define MAX_INTRINSICS_ALLOWED_INSIDE_CONSTEXPR

#if ( MAX_COMPILER_VERSION_AT_LEAST( 9, 0, 0 ) && defined( MAX_CPP_20 ) ) || __cpp_lib_is_constant_evaluated
	#define MAX_IS_CONSTANT_EVALUATED_SUPPORTED
#endif

#if MAX_COMPILER_VERSION_AT_LEAST( 10, 0, 0 )
	#if __cpp_concepts
		#define MAX_CONCEPTS_SUPPORTED
	#endif
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_COMPILER_GCC_HPP
