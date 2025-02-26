// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <utility>

namespace max
{
namespace Testing
{

	template< typename ResultPolicyType >
	TestSuite< ResultPolicyType >::TestSuite( char const * const Name,
	                                          ResultPolicyType const & ResultPolicy )
		: Name( Name )
		, ResultPolicy( ResultPolicy )
	{
	}

	template< typename ResultPolicyType >
	TestSuite< ResultPolicyType >::TestSuite( char const * const Name,
	                                          ResultPolicyType && ResultPolicy )
		: Name( Name )
		, ResultPolicy( std::move( ResultPolicy ) )
	{
	}

	template< typename ResultPolicyType >
	void TestSuite< ResultPolicyType >::AddTest( max::Testing::Test< ResultPolicyType > const & TestToAdd )
	{
		Tests.push_back( TestToAdd );
	}

	template< typename ResultPolicyType >
	void TestSuite< ResultPolicyType >::AddTest( max::Testing::Test< ResultPolicyType > && TestToAdd )
	{
		Tests.push_back( std::move( TestToAdd ) );
	}

	template< typename ResultPolicyType >
	void TestSuite< ResultPolicyType >::RunTests()
	{
		ResultPolicy.OnTestSuiteRun( Name );
		ResultPolicy.OnTestSuiteSetup( Name );
		Setup();
		ResultPolicy.OnTestSuiteSetupComplete( Name );

		int TestsPassed = 0;
		int TestsFailed = 0;
		for( auto & CurrentTest : Tests )
		{
			ResultPolicy.OnTestRun( CurrentTest.Name );
			CurrentTest.TestFunction( CurrentTest, ResultPolicy );
			auto TestPassed = CurrentTest.DidTestPass();
			if( TestPassed )
			{
				TestsPassed++;
				ResultPolicy.OnTestPassed( CurrentTest.Name );
			} else {
				TestsFailed++;
				ResultPolicy.OnTestFailed( CurrentTest.Name );
			}
		}

		ResultPolicy.OnTestSuiteTearDown( Name );
		TearDown();
		ResultPolicy.OnTestSuiteDone( Name, TestsPassed, TestsFailed );
	}

	template< typename ResultPolicyType >
	void TestSuite< ResultPolicyType >::Setup()
	{
	}

	template< typename ResultPolicyType >
	void TestSuite< ResultPolicyType >::TearDown()
	{
	}

} // namespace Testing
} // namespace max
