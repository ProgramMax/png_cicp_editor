// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CURRENTVERSIONNAMESPACE_HPP
#define MAX_COMPILING_CURRENTVERSIONNAMESPACE_HPP

// Note: These two macro definitions do not behave identically.
// Inline namespaces from C++11 allow templated types to be specialized
// from their included namespace. Using namespace does not allow that.
// Additionally, the parent namespace is included in ADL with
// inline namespaces.

#include <max/Compiling/Configuration/Compiler.hpp>

#ifndef MAX_INLINE_NAMESPACES_SUPPORTED
	#define MAX_CURRENT_VERSION_NAMESPACE_BEGIN( Name ) inline namespace Name
	#define MAX_CURRENT_VERSION_NAMESPACE_END( Name )
#else
	#define MAX_CURRENT_VERSION_NAMESPACE_BEGIN( Name ) namespace Name
	#define MAX_CURRENT_VERSION_NAMESPACE_END( Name )   using namespace Name;
#endif

#endif // #ifndef MAX_COMPILING_CURRENTVERSIONNAMESPACE_HPP
