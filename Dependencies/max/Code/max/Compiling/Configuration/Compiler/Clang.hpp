// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CONFIGURATION_COMPILER_CLANG_HPP
#define MAX_COMPILING_CONFIGURATION_COMPILER_CLANG_HPP

#include <version>

#include <max/Compiling/Macros.hpp>

#define MAX_COMPILER_CLANG

#define MAX_COMPILER_MESSAGE( Message ) _Pragma( MAX_STRINGIFY( message( Message ) ) )

#define MAX_COMPILER_VERSION_MAJOR __clang_major__
#define MAX_COMPILER_VERSION_MINOR __clang_minor__
#define MAX_COMPILER_VERSION_PATCH __clang_patchlevel__

#if __cplusplus > 202101L
	MAX_COMPILER_MESSAGE( "Compiling with a newer version of C++ than max recognizes. Using last known version." );
#elif __cplusplus >= 202101L
	#define MAX_CPP_2B
	#define MAX_CPP_20
#elif __cplusplus >= 202002L
	#define MAX_CPP_2A
	#define MAX_CPP_20
#elif __cplusplus >= 201703L
	#define MAX_CPP_2A
	#define MAX_CPP_1Z
	#define MAX_CPP_17
#elif __cplusplus >= 201402L
	#define MAX_CPP_1Z
	#define MAX_CPP_14
#elif __cplusplus >= 201103L
	#define MAX_CPP_11
#elif __cplusplus >= 199711L
	#define MAX_CPP_03
#endif

#if __has_feature(cxx_exceptions)
	#define MAX_EXCEPTIONS_SUPPORTED
#endif

#if __has_feature(cxx_noexcept)
	#define MAX_NOEXCEPT_SUPPORTED
#endif

#if __has_feature(cxx_inline_namespaces)
	#define MAX_INLINE_NAMESPACES_SUPPORTED
#endif

#define MAX_INTRINSICS_ALLOWED_INSIDE_CONSTEXPR

#if MAX_COMPILER_VERSION_AT_LEAST( 3, 1, 0 )
	#define MAX_CONSTEXPR_SUPPORTED
#endif

#if ( MAX_COMPILER_VERSION_AT_LEAST( 9, 0, 0 ) && __cplusplus > 201703L ) || __cpp_lib_is_constant_evaluated
	#define MAX_IS_CONSTANT_EVALUATED_SUPPORTED
#endif

#if MAX_COMPILER_VERSION_AT_LEAST( 10, 0, 0 )
	#if __cpp_concepts
		#define MAX_CONCEPTS_SUPPORTED
	#endif
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_COMPILER_CLANG_HPP
