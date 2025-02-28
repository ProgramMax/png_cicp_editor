// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PNGParserTest.hpp"

#include <array>
#include <span>
#include <utility>

#include <PNGParser.hpp>
#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>


namespace {

	// test
	static constinit char const* test_string = "test string";

	// file contents
	// This is a 1x1 black PNG
	static auto valid_png = std::array{ '\x89', 'P', 'N', 'G', '\x0d', '\x0a', '\x1a', '\x0a', '\x00', '\x00', '\x00', '\x0d', 'I', 'H', 'D', 'R', '\x00', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x01', '\x08', '\x02', '\x00', '\x00', '\x00', '\x90', '\x77', '\x53', '\xde', '\x00', '\x00', '\x00', '\x0c', 'I', 'D', 'A', 'T', '\x08', '\x99', '\x63', '\x60', '\x60', '\x60', '\x00', '\x00', '\x00', '\x04', '\x00', '\x01', '\xa3', '\x0a', '\x15', '\xe3', '\x00', '\x00', '\x00', '\x00', 'I', 'E', 'N', 'D', '\xae', '\x42', '\x60', '\x82' };
	static auto invalid_png = std::array{ 'f', 'o', 'o' };

} // anonymous namespace

namespace CICP_Inserter {

	void RunPNGParserTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto FileReaderTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "PNGParser test suite", std::move(ResultPolicy) };

		FileReaderTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "GetChunkIndicesError ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto error = GetChunkIndicesError{ GetChunkIndicesErrorCode::NotAPNGFile, { test_string } };

			CurrentTest.MAX_TESTING_ASSERT(error.error_code_ == GetChunkIndicesErrorCode::NotAPNGFile);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_.size() == 1);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_[0] == test_string);
			}
		});

		FileReaderTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "get_chunk_indices errors on invalid PNG file", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto indices = CICP_Inserter::get_chunk_indices(std::span{ invalid_png });

			CurrentTest.MAX_TESTING_ASSERT(!indices.has_value());
			CurrentTest.MAX_TESTING_ASSERT(indices.error().error_code_ == GetChunkIndicesErrorCode::NotAPNGFile);
			}
		});

		FileReaderTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "get_chunk_indices returns indices of the PNG file's chunks", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto indices = CICP_Inserter::get_chunk_indices(std::span<char>{ valid_png });

			CurrentTest.MAX_TESTING_ASSERT(indices.has_value());
			CurrentTest.MAX_TESTING_ASSERT(indices.value().size() == 3);
			CurrentTest.MAX_TESTING_ASSERT(indices.value()[0] == 8);
			CurrentTest.MAX_TESTING_ASSERT(indices.value()[1] == 33);
			CurrentTest.MAX_TESTING_ASSERT(indices.value()[2] == 57);
			}
		});

		FileReaderTestSuite.RunTests();
	}

} // namespace CICP_Inserter
