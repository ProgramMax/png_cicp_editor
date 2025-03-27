// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CICPCreatorTest.hpp"

#include <CICPCreator.hpp>
#include <CICP.hpp>

#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>

namespace PNG_CICP_Editor {

	void RunCICPCreatorTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto CICPCreatorTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "CICPCreator test suite", std::move(ResultPolicy) };

		CICPCreatorTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "create_cicp_buffer works for sRGB", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto cicp = CICP{ /*color_primaries=*/1, /*transfer_function=*/13, /*matrix_coefficients=*/1, /*video_full_range_flag=*/1 };

			auto buffer = create_cicp_buffer(cicp);

			// length
			CurrentTest.MAX_TESTING_ASSERT(buffer[0] == 0);
			CurrentTest.MAX_TESTING_ASSERT(buffer[1] == 0);
			CurrentTest.MAX_TESTING_ASSERT(buffer[2] == 0);
			CurrentTest.MAX_TESTING_ASSERT(buffer[3] == 4);

			// chunk type
			CurrentTest.MAX_TESTING_ASSERT(buffer[4] == 'c');
			CurrentTest.MAX_TESTING_ASSERT(buffer[5] == 'I');
			CurrentTest.MAX_TESTING_ASSERT(buffer[6] == 'C');
			CurrentTest.MAX_TESTING_ASSERT(buffer[7] == 'P');

			// chunk data
			CurrentTest.MAX_TESTING_ASSERT(buffer[8] == cicp.color_primaries_);
			CurrentTest.MAX_TESTING_ASSERT(buffer[9] == cicp.transfer_function_);
			CurrentTest.MAX_TESTING_ASSERT(buffer[10] == cicp.matrix_coefficients_);
			CurrentTest.MAX_TESTING_ASSERT(buffer[11] == cicp.video_full_range_flag_);

			// crc - 0x85720a73
			// TODO: Fix this. The number is negative. Default char in VC is signed. The comparison fails as a result.
			CurrentTest.MAX_TESTING_ASSERT(static_cast<unsigned char>(buffer[12]) == 0x85);
			CurrentTest.MAX_TESTING_ASSERT(buffer[13] == 0x72);
			CurrentTest.MAX_TESTING_ASSERT(buffer[14] == 0x0a);
			CurrentTest.MAX_TESTING_ASSERT(buffer[15] == 0x73);
			}
		});

		CICPCreatorTestSuite.RunTests();
	}

} // namespace PNG_CICP_Editor
