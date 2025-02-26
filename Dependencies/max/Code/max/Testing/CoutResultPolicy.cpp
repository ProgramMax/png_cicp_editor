// Copyright 2019, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "max/Testing/CoutResultPolicy.hpp"
#include <iostream>

namespace max
{
namespace Testing
{

	void CoutResultPolicy::OnTestSuiteRun( std::string const & TestSuiteName )
	{
		std::cout << "Running test suite " << TestSuiteName << std::endl;
	}

	void CoutResultPolicy::OnTestSuiteSetup( std::string const & TestSuiteName )
	{
		std::cout << "Setting up test suite " << TestSuiteName << "." << std::endl;
	}

	void CoutResultPolicy::OnTestSuiteSetupComplete( std::string const & TestSuiteName )
	{
		std::cout << "Done setting up test suites " << TestSuiteName << "." << std::endl;
	}

	void CoutResultPolicy::OnTestRun( std::string const & TestName )
	{
		std::cout << "Running test " << TestName << "." << std::endl;
	}

	void CoutResultPolicy::OnTestPassed( std::string const & TestName )
	{
		std::cout << "Passed test " << TestName << "." << std::endl;
	}

	void CoutResultPolicy::OnTestFailed( std::string const & TestName )
	{
		std::cout << "Failed test " << TestName << "." << std::endl;
	}

	void CoutResultPolicy::OnAssert( std::string const & FileName,
	                                 int LineNumber,
	                                 char const * const ExpressionString )
	{
		std::cout << "Assert failed: " << ExpressionString << "\n";
		std::cout << "\tin file " << FileName << "\n";
		std::cout << "\ton line " << LineNumber << std::endl;
	}

	void CoutResultPolicy::OnTestSuiteTearDown( std::string const & TestSuiteName )
	{
		std::cout << "Tearing down test suite " << TestSuiteName << "." << std::endl;
	}

	void CoutResultPolicy::OnTestSuiteDone( std::string const & TestSuiteName,
	                                        int TestsPassed,
	                                        int TestsFailed )
	{
		std::cout << "Done tearing down test suite " << TestSuiteName << "." << "\n";
		std::cout << "Tests passed: " << TestsPassed << "\n";
		std::cout << "Tests failed: " << TestsFailed << std::endl;
	}

} // namespace Testing
} // namespace max
