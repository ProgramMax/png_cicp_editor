// Copyright 2019, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>

namespace max
{
namespace Testing
{

	class CoutResultPolicy
	{
	public:

		static void OnTestSuiteRun(           std::string const & TestSuiteName );
		static void OnTestSuiteSetup(         std::string const & TestSuiteName );
		static void OnTestSuiteSetupComplete( std::string const & TestSuiteName );
		static void OnTestRun(                std::string const & TestName );
		static void OnTestPassed(             std::string const & TestName );
		static void OnTestFailed(             std::string const & TestName );
		static void OnAssert(                 std::string const & FileName,
		                                      int LineNumber,
		                                      char const * const ExpressionString );
		static void OnTestSuiteTearDown(      std::string const & TestSuiteName );
		static void OnTestSuiteDone(          std::string const & TestSuiteName,
		                                      int TestsPassed,
		                                      int TestsFailed );

	};

} // namespace Testing
} // namespace max
