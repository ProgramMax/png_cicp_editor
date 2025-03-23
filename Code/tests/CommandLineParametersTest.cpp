// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CommandLineParametersTest.hpp"
#include <CommandLineParameters.hpp>
#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>
#include <utility>

namespace {

	// actions
	static constinit char const* version   = "--version";
	static constinit char const* v_string  = "-v";
	static constinit char const* help      = "--help";
	static constinit char const* h_string  = "-h";
	static constinit char const* license   = "--license";
	static constinit char const* add       = "add";
	static constinit char const* overwrite = "overwrite";
	static constinit char const* remove_string = "remove";

	static constinit char const* preset    = "--preset";
	static constinit char const* narrow    = "--narrow";
	static constinit char const* full      = "--full";
	static constinit char const* p_string  = "-p";
	static constinit char const* n_string  = "-n";
	static constinit char const* f_string  = "-f";

	static constinit char const* color_primaries       = "--color_primaries";
	static constinit char const* transfer_function     = "--transfer_function";
	static constinit char const* matrix_coefficients   = "--matrix_coefficients";
	static constinit char const* video_full_range_flag = "--video_full_range_flag";

	static constinit char const* program_name    = "png_cicp_editor.exe";
	static constinit char const* test_image_path = "C:\\test\\image.png";

} // anonymous namespace

namespace PNG_CICP_Editor {

	void RunCommandLineParametersTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto CommandLineParametersTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "CommandLineParameters test suite", std::move(ResultPolicy) };

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "ParseCommandLineParametersError ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto error = ParseCommandLineParametersError{ ParseCommandLineParametersErrorCode::UnrecognizedParameter, { preset } };

			CurrentTest.MAX_TESTING_ASSERT(error.error_code_ == ParseCommandLineParametersErrorCode::UnrecognizedParameter);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_.size() == 1);
			CurrentTest.MAX_TESTING_ASSERT(error.output_messages_[0] == preset);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--version returns correct action", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 2;
			char const* argv[argc] = { program_name, version };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Version);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "-v returns correct action", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 2;
			char const* argv[argc] = { program_name, v_string };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Version);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--help returns correct action", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 2;
			char const* argv[argc] = { program_name, help };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Help);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "-h returns correct action", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 2;
			char const* argv[argc] = { program_name, h_string };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Help);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--license returns correct action", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 2;
			char const* argv[argc] = { program_name, license };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::License);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset bt.709 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "bt.709", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset linear-light-srgb returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "linear-light-srgb", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 8);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset srgb returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "srgb", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 13);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset bt.2020-10-bit returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "bt.2020-10-bit", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 9);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 14);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset bt.2020-12-bit returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "bt.2020-12-bit", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 9);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 15);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset bt.2100-pq returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "bt.2100-pq", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 9);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 16);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset bt.2100-hlg returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "bt.2100-hlg", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 9);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 18);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset dci-p3 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "dci-p3", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 11);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 17);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset display-p3 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "display-p3", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 12);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 13);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset p3-d65-pq returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "p3-d65-pq", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 12);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 16);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "-p bt.709 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, p_string, "bt.709", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--color_primaries 42 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, color_primaries, "42", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 42);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--transfer_function 42 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, transfer_function, "42", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 42);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--matrix_coefficients 42 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, matrix_coefficients, "42", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 42);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--video_full_range_flag 42 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, video_full_range_flag, "42", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 42);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--color_primaries 42 --transfer_function 43 --matrix_coefficients 44 --video_full_range_flag 45 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 11;
			char const* argv[argc] = { program_name, add, color_primaries, "42", transfer_function, "43", matrix_coefficients, "44", video_full_range_flag, "45", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 42);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 43);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 44);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 45);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "--preset srgb --color_primaries 42 returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 7;
			char const* argv[argc] = { program_name, add, preset, "srgb", color_primaries, "42", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 42);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 13);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "-p srgb --narrow returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 6;
			char const* argv[argc] = { program_name, add, preset, "srgb", narrow, test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 13);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "-p srgb -n returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 6;
			char const* argv[argc] = { program_name, add, preset, "srgb", n_string, test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 13);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "-p srgb -n --full returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 7;
			char const* argv[argc] = { program_name, add, preset, "srgb", n_string, full, test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 13);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "-p srgb -n -f returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 7;
			char const* argv[argc] = { program_name, add, preset, "srgb", n_string, f_string, test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Add);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.transfer_function_ == 13);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.add_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "overwrite -p srgb returns correct CICP values", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, overwrite, preset, "srgb", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Overwrite);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.overwrite_.cicp_.color_primaries_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.overwrite_.cicp_.transfer_function_ == 13);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.overwrite_.cicp_.matrix_coefficients_ == 0);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.overwrite_.cicp_.video_full_range_flag_ == 1);
			CurrentTest.MAX_TESTING_ASSERT(result->action_.overwrite_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "remove return correct action and file path", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 3;
			char const* argv[argc] = { program_name, remove_string, test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(result.has_value());

			CurrentTest.MAX_TESTING_ASSERT(result->action_type_ == Actions::Remove);

			CurrentTest.MAX_TESTING_ASSERT(result->action_.remove_.file_path_ == test_image_path);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "Missing file path errors", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 3;
			char const* argv[argc] = { program_name, preset, "srgb" };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(!result.has_value());
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "Unrecognized flag errors", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 2;
			char const* argv[argc] = { program_name, "not-an-action" };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(!result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result.error().error_code_ == ParseCommandLineParametersErrorCode::UnrecognizedParameter);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "Unrecognized flag errors", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 4;
			char const* argv[argc] = { program_name, add, "--not-a-flag", "0" };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(!result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result.error().error_code_ == ParseCommandLineParametersErrorCode::UnrecognizedParameter);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "Unrecognized preset errors", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, preset, "foo", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(!result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result.error().error_code_ == ParseCommandLineParametersErrorCode::UnrecognizedParameter);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "Non-number values error", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, color_primaries, "foo", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(!result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result.error().error_code_ == ParseCommandLineParametersErrorCode::UnrecognizedParameter);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "Negative number value errors", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, color_primaries, "-1", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(!result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result.error().error_code_ == ParseCommandLineParametersErrorCode::ValueOutsideRange);
			}
		});

		CommandLineParametersTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "Overflowing number value errors", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			const int argc = 5;
			char const* argv[argc] = { program_name, add, color_primaries, "256", test_image_path };
			auto result = parse_command_line_parameters(argc, argv);
			CurrentTest.MAX_TESTING_ASSERT(!result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(result.error().error_code_ == ParseCommandLineParametersErrorCode::ValueOutsideRange);
			}
		});

		CommandLineParametersTestSuite.RunTests();
	}

} // namespace PNG_CICP_Editor
