// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_TESTING_TEST_HPP
#define MAX_TESTING_TEST_HPP

#include <string>
#include <functional>

#define MAX_TESTING_ASSERT( CONDITION ) \
	Assert( __FILE__, __LINE__, #CONDITION, CONDITION, ResultPolicy )

#define MAX_TESTING_ASSERT_THROWS( FUNCTOR ) \
	AssertThrows( __FILE__, __LINE__, #FUNCTOR, FUNCTOR, ResultPolicy )

#define MAX_TESTING_ASSERT_DOES_NOT_THROW( FUNCTOR ) \
	AssertDoesNotThrow( __FILE__, __LINE__, #FUNCTOR, FUNCTOR, ResultPolicy )

namespace max
{
namespace Testing
{

	template< typename ResultPolicyType >
	class Test
	{
	public:

		Test( char const * const Name, std::function< void( max::Testing::Test< ResultPolicyType > & CurrentTest, ResultPolicyType const & ResultPolicy ) > const & TestFunction  );

		bool DidTestPass() const;

		void Assert( char const * const FileName, int LineNumber, char const * const ExpressionString, bool Expression, ResultPolicyType const & ResultPolicy  );

		template< typename ExceptionType, typename FunctorType >
		void AssertThrows( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor, ResultPolicyType const & ResultPolicy );

		template< typename ExceptionType, typename FunctorType >
		void AssertDoesNotThrow( char const * const FileName, int LineNumber, char const * const ExpressionString, FunctorType const & Functor, ResultPolicyType const & ResultPolicy );


		const std::string Name;
		std::function< void( max::Testing::Test< ResultPolicyType > & CurrentTest, ResultPolicyType const & ResultPolicy ) > TestFunction;

	private:

		bool DidAllAssertionsPass;

	};

} // namespace Testing
} // namespace max

#include <max/Testing/Test.inl>

#endif // #ifndef MAX_TESTING_TEST_HPP
