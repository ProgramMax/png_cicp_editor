// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "FileWriterTest.hpp"

#include <utility>

#include <FileWriter.hpp>
#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>

namespace {

	static constinit char const* test_string = "test string";

} // anonymous namespace

namespace CICP_Inserter {

	void RunFileWriterTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto FileWriterTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "FileWriter test suite", std::move(ResultPolicy) };

		FileWriterTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "WriteFileError ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto error = WriteFileError{ WriteFileErrorCode::CannotOpenFile, { test_string } };

			CurrentTest.MAX_TESTING_ASSERT(error.error_code_ == WriteFileErrorCode::CannotOpenFile);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_.size() == 1);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_[0] == test_string);
			}
		});

		FileWriterTestSuite.RunTests();
	}

} // namespace CICP_Inserter
