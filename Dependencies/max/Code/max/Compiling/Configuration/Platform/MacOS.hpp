// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CONFIGURATION_PLATFORM_MACOS_HPP
#define MAX_COMPILING_CONFIGURATION_PLATFORM_MACOS_HPP

#define MAX_PLATFORM_MACOS

#if defined( __i386__ )
	#define MAX_32BIT_WORD_SIZE
	#define MAX_X86
	#define MAX_LITTLE_ENDIAN
#elif defined( __x86_64__ )
	#define MAX_64BIT_WORD_SIZE
	#define MAX_X86_64
	#define MAX_LITTLE_ENDIAN
#elif defined( __ppc__ )
	#define MAX_32BIT_WORD_SIZE
	#define MAX_PPC
	#define MAX_BIG_ENDIAN
#elif #defined( __ppc64__ )
	#define MAX_64BIT_WORD_SIZE
	#define MAX_PPC64
	#define MAX_BIG_ENDIAN
#else
	static_assert( false, "Unknown platform" );
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_PLATFORM_MACOS_HPP
