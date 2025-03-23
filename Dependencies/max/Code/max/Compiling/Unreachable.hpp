// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_UNREACHABLE_HPP
#define MAX_COMPILING_UNREACHABLE_HPP

#include <max/Compiling/Configuration/Compiler.hpp>

#if defined( NDEBUG )
	#if defined( MAX_COMPILER_VC )
		#define MAX_UNREACHABLE __assume( 0 )
	#elif defined( MAX_COMPILER_GCC ) | defined( MAX_COMPILER_CLANG )
		#define MAX_UNREACHABLE __builtin_unreachable()
	#else
		#error "Unsupported compiler"
	#endif
#else
	#define MAX_UNREACHABLE std::terminate()
#endif

#endif // #ifndef MAX_COMPILING_UNREACHABLE_HPP
