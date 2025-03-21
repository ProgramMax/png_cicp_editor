// Copyright 2019, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_MACROS_HPP
#define MAX_COMPILING_MACROS_HPP


// Documentation: Macros.md

#define MAX_STRINGIFY(Message) #Message
#define MAX_EXPAND_AND_STRINGIFY(Message) MAX_STRINGIFY(Message)

#define MAX_COMPILER_VERSION_AT_LEAST( Major, Minor, Patch ) \
	( ( MAX_COMPILER_VERSION_MAJOR > (Major) ) || \
	  ( MAX_COMPILER_VERSION_MAJOR == (Major) && MAX_COMPILER_VERSION_MINOR > (Minor) ) || \
	  ( MAX_COMPILER_VERSION_MAJOR == (Major) && MAX_COMPILER_VERSION_MINOR == (Minor) && MAX_COMPILER_VERSION_PATCH >= (Patch) ) )

#endif // #ifndef MAX_COMPILING_MACROS_HPP
