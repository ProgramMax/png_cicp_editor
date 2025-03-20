// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ErrorTest.hpp"

#include <utility>

#include <Error.hpp>
#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>

namespace {

	static constinit char const* test_string = "test string";

} // anonymous namespace

namespace PNG_CICP_Editor {

	void RunErrorTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto ErrorTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "Error test suite", std::move(ResultPolicy) };

		ErrorTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "Error ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto error = Error{ { test_string } };

			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_.size() == 1);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_[0] == test_string);
			}
		});

		ErrorTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "ErrorWithCode ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto error = ErrorWithCode<int>{ 1, { test_string } };

			CurrentTest.MAX_TESTING_ASSERT(error.error_code_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_.size() == 1);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_[0] == test_string);
			}
		});

		ErrorTestSuite.RunTests();
	}

} // namespace PNG_CICP_Editor
