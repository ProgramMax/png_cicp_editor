// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "SparseArrayTest.hpp"

#include <SparseArray.hpp>
#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>

namespace CICP_Inserter {

	void RunSparseArrayTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto SparseArrayTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "SparseArray test suite", std::move(ResultPolicy) };

		SparseArrayTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "SparseArray ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto sparse_array = SparseArray<int, int>{ { { 1, 2 } } };

			CurrentTest.MAX_TESTING_ASSERT(sparse_array.array_.size() == 1);
			CurrentTest.MAX_TESTING_ASSERT(sparse_array.array_[0].first == 1);
			CurrentTest.MAX_TESTING_ASSERT(sparse_array.array_[0].second == 2);
			}
		});

		SparseArrayTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "const index operator finds element", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto sparse_array = SparseArray<int, int>{ { { 1, 2 }, { 3, 4 } } };

			auto index_result = sparse_array[3];

			CurrentTest.MAX_TESTING_ASSERT(index_result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(*index_result == 4);
			}
		});

		SparseArrayTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "const index operator returns empty on no match", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto sparse_array = SparseArray<int, int>{ { { 1, 2 }, { 3, 4 } } };

			auto index_result = sparse_array[5];

			CurrentTest.MAX_TESTING_ASSERT(!index_result.has_value());
			}
		});

		SparseArrayTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "begin returns correct iterator", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto sparse_array = SparseArray<int, int>{ { { 1, 2 }, { 3, 4 } } };

			auto iterator = sparse_array.begin();

			CurrentTest.MAX_TESTING_ASSERT(iterator == sparse_array.array_.begin());
			}
		});

		SparseArrayTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "end returns correct iterator", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto sparse_array = SparseArray<int, int>{ { { 1, 2 }, { 3, 4 } } };

			auto iterator = sparse_array.end();

			CurrentTest.MAX_TESTING_ASSERT(iterator == sparse_array.array_.end());
			}
		});

		SparseArrayTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "cbegin returns correct iterator", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto sparse_array = SparseArray<int, int>{ { { 1, 2 }, { 3, 4 } } };

			auto iterator = sparse_array.cbegin();

			CurrentTest.MAX_TESTING_ASSERT(iterator == sparse_array.array_.cbegin());
			}
		});

		SparseArrayTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "cend returns correct iterator", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto sparse_array = SparseArray<int, int>{ { { 1, 2 }, { 3, 4 } } };

			auto iterator = sparse_array.cend();

			CurrentTest.MAX_TESTING_ASSERT(iterator == sparse_array.array_.cend());
			}
		});

		SparseArrayTestSuite.RunTests();
	}

} // namespace CICP_Inserter
