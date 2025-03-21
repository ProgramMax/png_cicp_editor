// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CONFIGURATION_COMPILER_HPP
#define MAX_COMPILING_CONFIGURATION_COMPILER_HPP

// The order of these is important.
// Clang defines both __clang__ and __GNUC__.
// GCC does not define __clang__.
// So the GCC check must come after the Clang check.
// ICC also defines __GNUC__.
// So the check for __ICC must also come before the GCC check.
// Metrowerks and MSVC both define _MSC_VER.
// So check __MWERKS__ prior to checking _MSC_VER.

#if defined __clang__
	// Clang
	#include <max/Compiling/Configuration/Compiler/Clang.hpp>
#elif defined __GNUC__
	// GNU C++
	#include <max/Compiling/Configuration/Compiler/GCC.hpp>
#elif defined _MSC_VER
	// Microsoft Visual C++
	#include <max/Compiling/Configuration/Compiler/VC.hpp>
#else
	#error "Unknown compiler"
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_COMPILER_HPP
