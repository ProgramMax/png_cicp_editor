// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

namespace max
{
namespace Testing
{

	template< typename ResultPolicyType >
	Test< ResultPolicyType >::Test( char const * const Name, std::function< void( max::Testing::Test< ResultPolicyType > & CurrentTest, ResultPolicyType const & ResultPolicy ) > const & TestFunction )
		: Name( Name )
		, TestFunction( TestFunction )
		, DidAllAssertionsPass( true )
	{
	}

	template< typename ResultPolicyType >
	bool Test< ResultPolicyType >::DidTestPass() const
	{
		return DidAllAssertionsPass;
	}

	template< typename ResultPolicyType >
	void Test< ResultPolicyType >::Assert( char const * const FileName, int LineNumber, char const * const ExpressionString, bool const Expression, ResultPolicyType const & ResultPolicy )
	{
		bool const AssertionPassed = Expression;
		DidAllAssertionsPass &= AssertionPassed;
		if( ! AssertionPassed )
		{
			ResultPolicy.OnAssert( FileName, LineNumber, ExpressionString );
		}
	}

	template< typename ResultPolicyType >
	template< typename ExceptionType, typename FunctorType >
	void Test< ResultPolicyType >::AssertThrows( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor, ResultPolicyType const & ResultPolicy )
	{
		bool ThrewExpectedType = false;
		try
		{
			Functor();
		}
		catch( ExceptionType & )
		{
			ThrewExpectedType = true;
		}
		catch( ... )
		{
		}

		bool const AssertionPassed = ThrewExpectedType;
		DidAllAssertionsPass &= AssertionPassed;
		if( ! AssertionPassed )
		{
			ResultPolicy.OnAssert( FileName, LineNumber, ExpressionString );
		}
	}

	template< typename ResultPolicyType >
	template< typename ExceptionType, typename FunctorType >
	void Test< ResultPolicyType >::AssertDoesNotThrow( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor, ResultPolicyType const & ResultPolicy )
	{
		bool ThrewUnexpectedType = false;
		try
		{
			Functor();
		}
		catch( ExceptionType & )
		{
			ThrewUnexpectedType = true;
		}
		catch( ... )
		{
		}

		bool const AssertionPassed = ! ThrewUnexpectedType;
		DidAllAssertionsPass &= AssertionPassed;
		if( ! AssertionPassed )
		{
			ResultPolicy.OnAssert( FileName, LineNumber, ExpressionString );
		}
	}

} // namespace Testing
} // namespace max
