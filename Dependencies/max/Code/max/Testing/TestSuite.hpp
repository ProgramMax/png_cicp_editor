// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_TESTING_TESTSUITE_HPP
#define MAX_TESTING_TESTSUITE_HPP

#include <string>
#include <vector>
#include <max/Testing/Test.hpp>

namespace max
{
namespace Testing
{

	template< typename ResultPolicyType >
	class TestSuite
	{
	public:

		TestSuite( char const * const Name, ResultPolicyType const &  ResultPolicy );
		TestSuite( char const * const Name, ResultPolicyType       && ResultPolicy );

		void AddTest( max::Testing::Test< ResultPolicyType > const &  TestToAdd );
		void AddTest( max::Testing::Test< ResultPolicyType >       && TestToAdd );
		void RunTests();

	protected:

		virtual void Setup();
		virtual void TearDown();

	private:

		std::string Name;
		ResultPolicyType ResultPolicy;
		std::vector< max::Testing::Test< ResultPolicyType > > Tests;

	};

} // namespace Testing
} // namespace max

#include <max/Testing/TestSuite.inl>

#endif // #ifndef MAX_TESTING_TESTSUITE_HPP
