// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ActionsTest.hpp"

#include <filesystem>

#include <Actions.hpp>
#include <CICP.hpp>

#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>

namespace {

	auto cicp = PNG_CICP_Editor::CICP{ 1, 2, 3, 4 };
	auto file_path = std::filesystem::path{ R"(C:\images\test.png)" };

} // Anonymous namespace

namespace PNG_CICP_Editor {

	void RunActionsTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto ActionsTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "Actions test suite", std::move(ResultPolicy) };

		// TODO: Test the operator()s work. Maybe mocks here?

		ActionsTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "AddAction ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto add_action = AddAction{ cicp, file_path };

			CurrentTest.MAX_TESTING_ASSERT(add_action.cicp_ == cicp);
			CurrentTest.MAX_TESTING_ASSERT(add_action.file_path_ == file_path);
			}
		});

		ActionsTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "OverwriteAction ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto overwrite_action = OverwriteAction{ cicp, file_path };

			CurrentTest.MAX_TESTING_ASSERT(overwrite_action.cicp_ == cicp);
			CurrentTest.MAX_TESTING_ASSERT(overwrite_action.file_path_ == file_path);
			}
		});

		ActionsTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "RemoveAction ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto remove_action = RemoveAction{ file_path };

			CurrentTest.MAX_TESTING_ASSERT(remove_action.file_path_ == file_path);
			}
		});

		ActionsTestSuite.RunTests();
	}

} // namespace PNG_CICP_Editor
