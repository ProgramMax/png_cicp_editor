// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "FileReaderTest.hpp"
#include <FileReader.hpp>
#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>
#include <utility>

namespace {

	static constinit char const* test_string = "test string";

} // anonymous namespace

namespace CICP_Inserter {

	void RunFileReaderTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto FileReaderTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "FileReader test suite", std::move(ResultPolicy) };

		FileReaderTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "ReadFileError ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto error = ReadFileError{ ReadFileErrorCode::CannotOpenFile, { test_string } };

			CurrentTest.MAX_TESTING_ASSERT(error.error_code_ == ReadFileErrorCode::CannotOpenFile);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_.size() == 1);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_[0] == test_string);
			}
		});

		FileReaderTestSuite.RunTests();
	}

} // namespace CICP_Inserter
