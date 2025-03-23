// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CICPTest.hpp"

#include <CICP.hpp>
#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>

namespace PNG_CICP_Editor {

	void RunCICPTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto CICPTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "CICP test suite", std::move(ResultPolicy) };

		CICPTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto cicp = CICP{ 1, 2, 3, 4 };

			CurrentTest.MAX_TESTING_ASSERT(cicp.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(cicp.transfer_function_ == 2);
			CurrentTest.MAX_TESTING_ASSERT(cicp.matrix_coefficients_ == 3);
			CurrentTest.MAX_TESTING_ASSERT(cicp.video_full_range_flag_ == 4);
			}
		});

		CICPTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "operator == returns true on match", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto cicp_1 = CICP{ 1, 2, 3, 4 };
			auto cicp_2 = CICP{ 1, 2, 3, 4 };

			CurrentTest.MAX_TESTING_ASSERT(cicp_1 == cicp_2);
			}
		});

		CICPTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "operator == returns false on non-match", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto cicp_1 = CICP{ 1, 2, 3, 4 };
			auto cicp_2 = CICP{ 5, 6, 7, 8 };

			CurrentTest.MAX_TESTING_ASSERT(!(cicp_1 == cicp_2));
			}
		});

		CICPTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "operator != returns false on match", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto cicp_1 = CICP{ 1, 2, 3, 4 };
			auto cicp_2 = CICP{ 1, 2, 3, 4 };

			CurrentTest.MAX_TESTING_ASSERT(!(cicp_1 != cicp_2));
			}
		});

		CICPTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "operator != returns true on non-match", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto cicp_1 = CICP{ 1, 2, 3, 4 };
			auto cicp_2 = CICP{ 5, 6, 7, 8 };

			CurrentTest.MAX_TESTING_ASSERT(cicp_1 != cicp_2);
			}
		});

		CICPTestSuite.RunTests();
	}

} // namespace PNG_CICP_Editor
