// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CICPInserterTest.hpp"

#include <array>
#include <span>
#include <utility>
#include <vector>

#include <CICPInserter.hpp>
#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>

namespace {

	// This is a 1x1 black PNG
	static auto png_contents = std::array{ '\x89', 'P', 'N', 'G', '\x0d', '\x0a', '\x1a', '\x0a', '\x00', '\x00', '\x00', '\x0d', 'I', 'H', 'D', 'R', '\x00', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x01', '\x08', '\x02', '\x00', '\x00', '\x00', '\x90', '\x77', '\x53', '\xde', '\x00', '\x00', '\x00', '\x0c', 'I', 'D', 'A', 'T', '\x08', '\x99', '\x63', '\x60', '\x60', '\x60', '\x00', '\x00', '\x00', '\x04', '\x00', '\x01', '\xa3', '\x0a', '\x15', '\xe3', '\x00', '\x00', '\x00', '\x00', 'I', 'E', 'N', 'D', '\xae', '\x42', '\x60', '\x82' };
	static auto chunk_indices = std::vector<size_t>{ 8, 33, 57 };

	// A PNG with no PLTE or IDAT chunks
	static auto empty_png_contents = std::array{ '\x89', 'P', 'N', 'G', '\x0d', '\x0a', '\x1a', '\x0a', '\x00', '\x00', '\x00', '\x0d', 'I', 'H', 'D', 'R', '\x00', '\x00', '\x00', '\x01', '\x00', '\x00', '\x00', '\x01', '\x08', '\x02', '\x00', '\x00', '\x00', '\x90', '\x77', '\x53', '\xde', '\x00', '\x00', '\x00', '\x00', 'I', 'E', 'N', 'D', '\xae', '\x42', '\x60', '\x82' };
	static auto empty_chunk_indices = std::vector<size_t>{ 8, 33 };


	static constinit char const* test_error_message = "test";

} // anonymous namespace

namespace CICP_Inserter {

	void RunCICPInserterTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto CICPInserterTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "CICPInserter test suite", std::move(ResultPolicy) };

		CICPInserterTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "GetInsertionIndexError ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto error = GetInsertionIndexError{ GetInsertionIndexErrorCode::CICPChunkAlreadyExists, { test_error_message } };

			CurrentTest.MAX_TESTING_ASSERT(error.error_code_ == GetInsertionIndexErrorCode::CICPChunkAlreadyExists);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_.size() == 1);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_[0] == test_error_message);
			}
		});

		CICPInserterTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "get_insertion_index returns the correct insertion point", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto insertion_index = CICP_Inserter::get_insertion_index(png_contents, chunk_indices);
			CurrentTest.MAX_TESTING_ASSERT(insertion_index.has_value());

			CurrentTest.MAX_TESTING_ASSERT(*insertion_index == 33);
			}
		});

		CICPInserterTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "get_insertion_index handles no PLTE chunk", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto insertion_index = CICP_Inserter::get_insertion_index(png_contents, chunk_indices);
			CurrentTest.MAX_TESTING_ASSERT(insertion_index.has_value());

			CurrentTest.MAX_TESTING_ASSERT(*insertion_index == 33);
			}
		});

		/*
		* TODO: Get test data for a 1x1 black PNG with cICP
		CICPInserterTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "get_insertion_index errors if a cICP already exists", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto insertion_index = CICP_Inserter::get_insertion_index(png_contents, chunk_indices);

			CurrentTest.MAX_TESTING_ASSERT(!insertion_index.has_value());
			CurrentTest.MAX_TESTING_ASSERT(insertion_index.error().error_code_ == GetInsertionIndexErrorCode::CICPChunkAlreadyExists);
			}
		});
		*/

		CICPInserterTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "get_insertion_index errors with no PLTE and IDAT chunks", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto insertion_index = CICP_Inserter::get_insertion_index(empty_png_contents, empty_chunk_indices);

			CurrentTest.MAX_TESTING_ASSERT(!insertion_index.has_value());
			CurrentTest.MAX_TESTING_ASSERT(insertion_index.error().error_code_ == GetInsertionIndexErrorCode::CouldNotFindInsertionPoint);
			}
		});

		CICPInserterTestSuite.RunTests();
	}

} // namespace CICP_Inserter
