// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CONFIGURATION_COMPILER_VC_HPP
#define MAX_COMPILING_CONFIGURATION_COMPILER_VC_HPP

#include <max/Compiling/Macros.hpp>

#define MAX_COMPILER_VC

#define MAX_COMPILER_MESSAGE( Message ) __pragma( message( Message ) )

#if _MSC_VER > 1943
	MAX_COMPILER_MESSAGE("Compiling with a newer version of MSVC than max recognizes. Using last known version.");
#elif _MSC_VER >= 1943
	// MSVC++ (Visual Studio 2022 / version 17.13)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 13
#elif _MSC_VER >= 1939
	// MSVC++ (Visual Studio 2022 / version 17.9)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 9
#elif _MSC_VER >= 1938
	// MSVC++ (Visual Studio 2022 / version 17.8)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 8
#elif _MSC_VER >= 1937
	// MSVC++ (Visual Studio 2022 / version 17.7)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 7
#elif _MSC_VER >= 1936
	// MSVC++ (Visual Studio 2022 / version 17.6)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 6
#elif _MSC_VER >= 1935
	// MSVC++ (Visual Studio 2022 / version 17.5)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 5
#elif _MSC_VER >= 1934
	// MSVC++ (Visual Studio 2022 / version 17.4)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 4
#elif _MSC_VER >= 1933
	// MSVC++ (Visual Studio 2022 / version 17.3)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 3
#elif _MSC_VER >= 1932
	// MSVC++ (Visual Studio 2022 / version 17.2)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 2
#elif _MSC_VER >= 1931
	// MSVC++ (Visual Studio 2022 / version 17.1)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 1
#elif _MSC_VER >= 1930
	// MSVC++ (Visual Studio 2022 Preview 3.0 & 4.0 / version 17.0)
	#define MAX_COMPILER_VERSION_MAJOR 17
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 1929
	// MSVC++ 14.30 (Visual Studio 2019 / version 16.10)
	// Note, 16.11 also shares this same _MSC_VER.
	// Note, Visual Studio 2022 Preview 1.0 (and possibly 2.0?) / version 17.0 also shares this same _MSC_VER.
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 10
#elif _MSC_VER >= 1928
	// MSVC++ 14.28 (Visual Studio 2019 / version 16.8)
	// Note, 16.9 also shares this same _MSC_VER.
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 8
#elif _MSC_VER >= 1927
	// MSVC++ 14.27 (Visual Studio 2019 / versoin 16.7)
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 7
#elif _MSC_VER >= 1926
	// MSVC++ 14.26 (Visual Studio 2019 / version 16.6)
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 6
#elif _MSC_VER >= 1925
	// MSVC++ 14.25 (Visual Studio 2019 / version 16.5)
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 5
#elif _MSC_VER >= 1924
	// MSVC++ 14.24 (Visual Studio 2019 / version 16.4)
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 4
#elif _MSC_VER >= 1923
	// MSVC++ 14.23 (Visual Studio 2019 / version 16.3)
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 3
#elif _MSC_VER >= 1922
	// MSVC++ 14.22 (Visual Studio 2019 / version 16.2)
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 2
#elif _MSC_VER >= 1921
	// MSVC++ 14.21 (Visual Studio 2019 / version 16.1)
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 1
#elif _MSC_VER >= 1920
	// MSVC++ 14.2 (Visual Studio 2019 / version 16.0)
	#define MAX_COMPILER_VERSION_MAJOR 16
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 1916
	// MSVC++ 14.16 (Visual Studio 2017 Update 9 / version 15.9)
	#define MAX_COMPILER_VERSION_MAJOR 15
	#define MAX_COMPILER_VERSION_MINOR 9
#elif _MSC_VER >= 1915
	// MSVC++ 14.15 (Visual Studio 2017 Update 8 / version 15.8)
	#define MAX_COMPILER_VERSION_MAJOR 15
	#define MAX_COMPILER_VERSION_MINOR 8
#elif _MSC_VER >= 1914
	// MSVC++ 14.14 (Visual Studio 2017 Update 7 / version 15.7)
	#define MAX_COMPILER_VERSION_MAJOR 15
	#define MAX_COMPILER_VERSION_MINOR 7
#elif _MSC_VER >= 1913
	// MSVC++ 14.13 (Visual Studio 2017 Update 6 / version 15.6)
	#define MAX_COMPILER_VERSION_MAJOR 15
	#define MAX_COMPILER_VERSION_MINOR  6
#elif _MSC_VER >= 1912
	// MSVC++ 14.12 (Visual Studio 2017 Update 5 / version 15.5)
	#define MAX_COMPILER_VERSION_MAJOR 15
	#define MAX_COMPILER_VERSION_MINOR  5
#elif _MSC_VER >= 1911
	// MSVC++ 14.11 (Visual Studio 2017 Update 3 & 4 / version 15.3, 15.4)
	#define MAX_COMPILER_VERSION_MAJOR 15
	#define MAX_COMPILER_VERSION_MINOR  3
#elif _MSC_VER >= 1910
	// MSVC++ 14.1 (Visual Studio 2017 and Update 1 & 2 / version 15.0, 15.1, 15.2)
	#define MAX_COMPILER_VERSION_MAJOR 15
	#define MAX_COMPILER_VERSION_MINOR  0
#elif _MSC_VER >= 1900
	// MSVC++ 14.0 and updates 1, 2, & 3 (Visual Studio 2015 / version 14.0)
	#define MAX_COMPILER_VERSION_MAJOR 14
	#define MAX_COMPILER_VERSION_MINOR  0
	// All of MSVC++ 14.0's updates show up with _MSC_VER 1900.
	// So check _MSC_FULL_VER.
	#if _MSC_FULL_VER >= 190024210
		// MSVC++ 14.3 (Visual Studio 2015 Update 3)
	#elif _MSC_FULL_VER >= 190023918
		// MSVC++ 14.2 (Visual Studio 2015 Update 2)
	#elif _MSC_FULL_VER >= 190023506
		// MSVC++ 14.1 (Visual Studio 2015 Update 1)
	#endif
#elif _MSC_VER >= 1800
	// MSVC++ 12.0 (Visual Studio 2013 / version 12.0)
	#define MAX_COMPILER_VERSION_MAJOR 12
	#define MAX_COMPILER_VERSION_MINOR  0
#elif _MSC_VER >= 1700
	// MSVC++ 11.0 (Visual Studio 2012 / version 11.0)
	#define MAX_COMPILER_VERSION_MAJOR 11
	#define MAX_COMPILER_VERSION_MINOR  0
#elif _MSC_VER >= 1600
	// MSVC++ 10.0 (Visual Studio 2010 / version 10.0)
	#define MAX_COMPILER_VERSION_MAJOR 10
	#define MAX_COMPILER_VERSION_MINOR  0
	#if _MSC_FULL_VER >= 160040219
		// MSVC++ 10.1 SP 1
	#endif
#elif _MSC_VER >= 1500
	// MSVC++ 9.0 (Visual Studio 2008 / version 9.0)
	#define MAX_COMPILER_VERSION_MAJOR 9
	#define MAX_COMPILER_VERSION_MINOR 0
	#if _MSC_FULL_VER >= 150030729
		// MSVC++ 9.0 SP1
	#endif
#elif _MSC_VER >= 1400
	// MSVC++ 8.0 (Visual Studio 2005 / version 8.0)
	#define MAX_COMPILER_VERSION_MAJOR 8
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 1310
	// MSVC++ 7.1 (Visual Studio .NET 2003 / version 7.1)
	#define MAX_COMPILER_VERSION_MAJOR 7
	#define MAX_COMPILER_VERSION_MINOR 1
	#if _MSC_FULL_VER >= 13106030
		// Visual Studio .NET 2003 SP 1
	#elif _MSC_FULL_VER >= 13103077
		// Visual Studio .NET 2003
	#elif _MSC_FULL_VER >= 13102292
		// Visual Studio .NET 2003 Beta
	#endif
#elif _MSC_VER >= 1300
	// MSVC++ 7.0 (Visual Studio .NET 2002 / version 7.0)
	#define MAX_COMPILER_VERSION_MAJOR 7
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 1200
	// MSVC++ 6.0 (Visual Studio 6.0 / version 6.0)
	#define MAX_COMPILER_VERSION_MAJOR 6
	#define MAX_COMPILER_VERSION_MINOR 0
	#if _MSC_FULL_VER >= 12008804
		// MSVC++ 6.0 SP6
	#endif
#elif _MSC_VER >= 1100
	// MSVC++ 5.0 (Visual Studio 97 / version 5.0)
	#define MAX_COMPILER_VERSION_MAJOR 5
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 1020
	// MSVC++ 4.2 (Developer Studio 4.2)
	#define MAX_COMPILER_VERSION_MAJOR 4
	#define MAX_COMPILER_VERSION_MINOR 2
#elif _MSC_VER >= 1010
	// MSVC++ 4.1 (Developer Studio 4.1)
	#define MAX_COMPILER_VERSION_MAJOR 4
	#define MAX_COMPILER_VERSION_MINOR 1
#elif _MSC_VER >= 1000
	// MSVC++ 4.0 (Developer Studio 4.0)
	#define MAX_COMPILER_VERSION_MAJOR 4
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 900
	// MSVC++ 2.0
	#define MAX_COMPILER_VERSION_MAJOR 2
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 800
	// MSVC++ 1.0
	#define MAX_COMPILER_VERSION_MAJOR 1
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 700
	// MSC/C++ 7.0
	#define MAX_COMPILER_VERSION_MAJOR 7
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 600
	// MSC 6.0
	#define MAX_COMPILER_VERSION_MAJOR 6
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 500
	// MSC 5.0
	#define MAX_COMPILER_VERSION_MAJOR 5
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 400
	// MSC 4.0
	#define MAX_COMPILER_VERSION_MAJOR 4
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 300
	// MSC 3.0
	#define MAX_COMPILER_VERSION_MAJOR 3
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 200
	// MSC 2.0
	#define MAX_COMPILER_VERSION_MAJOR 2
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER >= 100
	// MSC 1.0
	#define MAX_COMPILER_VERSION_MAJOR 1
	#define MAX_COMPILER_VERSION_MINOR 0
#else
	#error "Unknown compiler version"
#endif
#define MAX_COMPILER_VERSION_PATCH 0

#if _MSC_FULL_VER >= 190024210 // MSVC++ 14.3 (Visual Studio 2015 Update 3)
	// Visual Studio 2015 Update 3 introduced the _MSVC_LANG pre-defined macro
	#if _MSVC_LANG > 202400L
		MAX_COMPILER_MESSAGE("Compiling with a newer version of C++ than max recognizes. Using last known version.");
	#elif _MSVC_LANG >= 202400L
		#define MAX_CPP_23
	#elif _MSVC_LANG >= 202004L
		#define MAX_CPP_20
	#elif _MSVC_LANG >= 201705L
		#define MAX_CPP_17
	#elif _MSVC_LANG >= 201704L
		#define MAX_CPP_17
	#elif _MSVC_LANG >= 201703L
		#define MAX_CPP_17
	#elif _MSVC_LANG >= 201402L
		#define MAX_CPP_14
	#elif _MSVC_LANG >= 201103L
		#define MAX_CPP_11
	#elif _MSVC_LANG >= 199711L
		#define MAX_CPP_03
	#endif
#else
	#define MAX_CPP_03
#endif

// VC sets _CPPUNWIND on /EHsc but not /EHa ... I think?
#if defined(_CPPUNWIND)
	#define MAX_EXCEPTIONS_SUPPORTED
#endif

#if _MSC_FULL_VER >= 180021114
	#define MAX_NOEXCEPT_SUPPORTED
#endif

#if MAX_COMPILER_VERSION_AT_LEAST( 14, 0, 0 )
	#define	MAX_INLINE_NAMESPACES_SUPPORTED
	#define MAX_CONSTEXPR_SUPPORTED
#endif

#if MAX_COMPILER_VERSION_AT_LEAST( 15, 3, 0 )
	#define MAX_HAS_INCLUDE_SUPPORTED
#endif

#if MAX_COMPILER_VERSION_AT_LEAST( 16, 2, 0 )
	#include <version>
	#if ( MAX_COMPILER_VERSION_AT_LEAST( 16, 5, 0 ) && defined ( _MSVC_LANG ) && _MSVC_LANG >= 201704L ) || __cpp_lib_is_constant_evaluated
		#define MAX_IS_CONSTANT_EVALUATED_SUPPORTED
	#endif
#endif

#if MAX_COMPILER_VERSION_AT_LEAST( 17, 0, 0 )
	#if __cpp_concepts
		#define MAX_CONCEPTS_SUPPORTED
	#endif
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_COMPILER_VC_HPP
