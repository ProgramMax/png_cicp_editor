// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CONFIGURATION_PLATFORM_LINUX_HPP
#define MAX_COMPILING_CONFIGURATION_PLATFORM_LINUX_HPP

#include <max/Compiling/Configuration/Compiler.hpp>

#define MAX_PLATFORM_LINUX

#if defined( MAX_COMPILER_GCC ) || defined( MAX_COMPILER_CLANG )
	#if defined( __x86_64__ )
		#define MAX_64BIT_WORD_SIZE
		#define MAX_X86_64
	#elif defined( __i386__ )
		#define MAX_32BIT_WORD_SIZE
		#define MAX_X86
	#elif defined( __IA64__ )
		#define MAX_64BIT_WORD_SIZE
		#define MAX_IA64
	#elif defined( __aarch64__ )
		#define MAX_64BIT_WORD_SIZE
		#define MAX_AARCH64
	#elif defined( __arm__ )
		#define MAX_32BIT_WORD_SIZE
		#define MAX_ARM
	#elif defined( __thumb__ )
		#define MAX_16BIT_WORD_SIZE
		#define MAX_THUMB
	#else
		static_assert( false, "Unknown platform" );
	#endif

	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		#define MAX_LITTLE_ENDIAN
	#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		#define MAX_BIG_ENDIAN
	#endif
#else
	static_assert( false, "Unknown platform" );
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_PLATFORM_LINUX_HPP
