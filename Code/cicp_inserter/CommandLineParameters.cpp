// Copyright 2025, The png_cicp_editer Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CommandLineParameters.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string_view>
#include <utility>

#include "StateMachine.hpp"
#include "SparseArray.hpp"

namespace {

	// error messages
	static constinit char const* unrecognized_parameter = "Unrecognized command line parameter: ";
	static constinit char const* value_outside_range    = "Value outside 0-255 range: ";
	static constinit char const* expected_value         = "File path provided where a value was expected: ";

	// utility
	static constinit char const* newline                = "\n";

	void print_version() noexcept {
		std::cout << "png_cicp_editer version 2.2" << std::endl;
	}

	void print_help() noexcept {
		print_version();
		std::cout <<
R"(This program allows you to insert CICP data into a PNG file.
CICP is an efficient way to specify color space.
It is standardized in ITU-T H.273, which can be found here:
https://www.itu.int/rec/T-REC-H.273

Example usage: png_cicp_editer.exe --preset display-p3 C:\images\test.png

Presets:
	bt.709          Rec. ITU-R BT.709-6
	srgb-linear     linear-light sRGB
	srgb            IEC 61966-2-1 sRGB
	bt.2020-10-bit  Rec. ITU-R BT.2020-2 (10-bit system)
	bt.2020-12-bit  Rec. ITU-R BT.2020-2 (12-bit system)
	bt.2100-pq      Rec. ITU-R BT.2100-2 perceptual quantization (PQ) system
	bt.2100-hlg     Rec. ITU-R BT.2100-2 hybrid log-gamma (HLG) system
	dci-p3          SMPTE RP 431-2 with SMPTE ST 428-1 D-Cinema Distribution Master (DCI-P3)
	display-p3      Display P3
	p3-d65-pq       P3-D65 PQ

You can also specify individual CICP values. For example, to label an RGB image decoded from a SECAM video:
Example usage: png_cicp_editer.exe --color_primaries 5 --transfer_function 4 --matrix_coefficients 0 --video_full_range_flag 1 C:\images\test.png

These can be mixed to override defaults. Values specified later override prior values.
Example usage: png_cicp_editer.exe --preset display-p3 --video_full_range_flag 0 C:\images\test.png

General flags:
	-h --help             Show help information (what you are viewing now)
	-v --version          Show version information
	-p --preset [value]   Use [value]'s CICP values
	-n --narrow           Use narrow range (--video_full_range_flag 0)
	-f --full             Use full range (--video_full_range_flag 1)
	-o --overwrite        Overwrite an existing CICP value in the file

Specific flags to match CICP parameter names from ITU-T H.273 (experts only):
	   --color_primaries [value]
	   --transfer_function [value]
	   --matrix_coefficients [value]
	   --video_full_range_flag [value]
Note: Specific flags use values from ITU-T H.273. Not all values are valid.
PNG puts further restrictions on which values are valid.
)" << std::endl;
	}

	enum class ReadNumericValueErrorCode {
		UnrecognizedParameter,
		ValueOutsideRange,
	};
	using ReadNumericValueError = PNG_CICP_Editer::ErrorWithCode<ReadNumericValueErrorCode>;

	std::expected<uint8_t, ReadNumericValueError> read_numeric_value(char const* parameter) noexcept {
		static constinit int base = 10;
		char* end_pointer = nullptr;
		long value = std::strtol(parameter, &end_pointer, base);
		if (errno == ERANGE || parameter == end_pointer) {
			return std::unexpected{ ReadNumericValueError{ ReadNumericValueErrorCode::UnrecognizedParameter, { unrecognized_parameter, parameter, newline } } };
		}

		if (value < 0 || value > 255) {
			return std::unexpected{ ReadNumericValueError{ ReadNumericValueErrorCode::ValueOutsideRange, { value_outside_range, parameter, newline } } };
		}

		return static_cast<uint8_t>(value);
	}

	PNG_CICP_Editer::ParseCommandLineParametersError convert_error(ReadNumericValueError error) noexcept {
		PNG_CICP_Editer::ParseCommandLineParametersErrorCode new_error_code;
		switch (error.error_code_) {
		case ReadNumericValueErrorCode::UnrecognizedParameter:
			new_error_code = PNG_CICP_Editer::ParseCommandLineParametersErrorCode::UnrecognizedParameter;
			break;
		case ReadNumericValueErrorCode::ValueOutsideRange:
			new_error_code = PNG_CICP_Editer::ParseCommandLineParametersErrorCode::ValueOutsideRange;
			break;
		default:
			std::unreachable();
		}

		return PNG_CICP_Editer::ParseCommandLineParametersError{ std::move(new_error_code), std::move(error.output_messages_) };
	}

} // anonymous namespace

namespace PNG_CICP_Editer {

	CommandLineParameters::CommandLineParameters(bool overwrite_cicp, uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag, std::string png_file_path) noexcept
		: overwrite_cicp_(std::move(overwrite_cicp))
		, color_primaries_(std::move(color_primaries))
		, transfer_function_(std::move(transfer_function))
		, matrix_coefficients_(std::move(matrix_coefficients))
		, video_full_range_flag_(std::move(video_full_range_flag))
		, png_file_path_(std::move(png_file_path))
	{}

	std::expected<CommandLineParameters, ParseCommandLineParametersError> parse_command_line_parameters(int argc, char const* argv[]) noexcept {
		enum class ParserStates {
			ExpectingAction,
			ExpectingFlag,
			ExpectingPresetValue,
			ExpectingColorPrimariesValue,
			ExpectingTransferFunctionValue,
			ExpectingMatrixCoefficientsValue,
			ExpectingVideoFullRangeFlagValue,
			Done,
		};
		class Transition {
		public:

			using PredicateAndActionResultType = std::expected<bool, TransitionError>;
			//using PredicateAndActionType = std::move_only_function<bool(char const* string)>;
			using PredicateAndActionType = std::function<PredicateAndActionResultType(char const* string)>;

			explicit Transition(PredicateAndActionType predicate_and_action, ParserStates transition_to) noexcept
				: predicate_and_action_(std::move(predicate_and_action))
				, transition_to_(std::move(transition_to))
			{}

			PredicateAndActionType predicate_and_action_;
			ParserStates transition_to_;

		};


		bool overwrite_cicp = false;
		uint8_t color_primaries = 0;
		uint8_t transfer_function = 0;
		uint8_t matrix_coefficients = 0;
		uint8_t video_full_range_flag = 1;


		auto version_flag_matched_transition = Transition{
			[](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view version_string = "--version";
				static const std::string_view v_string         = "-v";
				if (version_string.compare(string) != 0 && v_string.compare(string) != 0) {
					return false;
				}
				print_version();
				return true;
			},
			ParserStates::Done
		};
		auto help_flag_matched_transition = Transition{
			[](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view help_string = "--help";
				static const std::string_view h_string    = "-h";
				if (help_string.compare(string) != 0 && h_string.compare(string) != 0) {
					return false;
				}
				print_help();
				return true;
			},
			ParserStates::Done
		};
		auto preset_flag_matched_transition = Transition{
			[](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view preset_string = "--preset";
				static const std::string_view p_string      = "-p";
				return (preset_string.compare(string) == 0) || (p_string.compare(string) == 0);
			},
			ParserStates::ExpectingPresetValue
		};
		auto bt709_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt709_string = "bt.709";
				if (bt709_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 1;
				transfer_function = 1;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto linear_light_srgb_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view linear_light_srgb_string = "linear-light-srgb";
				if (linear_light_srgb_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 1;
				transfer_function = 8;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto srgb_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view srgb_string = "srgb";
				if (srgb_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 1;
				transfer_function = 13;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto bt2020_10bit_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt2020_10bit_string = "bt.2020-10-bit";
				if (bt2020_10bit_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 9;
				transfer_function = 14;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto bt2020_12bit_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt2020_12bit_string = "bt.2020-12-bit";
				if (bt2020_12bit_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 9;
				transfer_function = 15;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto bt2100_pq_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt2100_pq_string = "bt.2100-pq";
				if (bt2100_pq_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 9;
				transfer_function = 16;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto bt2100_hlg_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt2100_hlg_string = "bt.2100-hlg";
				if (bt2100_hlg_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 9;
				transfer_function = 18;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto dci_p3_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view dci_p3_string = "dci-p3";
				if (dci_p3_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 11;
				transfer_function = 17;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto display_p3_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view display_p3_string = "display-p3";
				if (display_p3_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 12;
				transfer_function = 13;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto p3_d65_pq_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view p3_d65_pq_string = "p3-d65-pq";
				if (p3_d65_pq_string.compare(string) != 0) {
					return false;
				}
				color_primaries = 12;
				transfer_function = 16;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto narrow_flag_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view narrow_string = "--narrow";
				static const std::string_view n_string = "-n";
				if (narrow_string.compare(string) != 0 && n_string.compare(string) != 0) {
					return false;
				}
				video_full_range_flag = 0;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto full_flag_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view full_string = "--full";
				static const std::string_view f_string = "-f";
				if (full_string.compare(string) != 0 && f_string.compare(string) != 0) {
					return false;
				}
				video_full_range_flag = 1;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto overwrite_flag_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view overwrite_string = "--overwrite";
				static const std::string_view o_string = "-o";
				if (overwrite_string.compare(string) != 0 && o_string.compare(string) != 0) {
					return false;
				}
				overwrite_cicp = true;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto color_primaries_flag_matched_transition = Transition{
			[](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view color_primaries_string = "--color_primaries";
				return color_primaries_string.compare(string) == 0;
			},
			ParserStates::ExpectingColorPrimariesValue
		};
		auto transfer_function_flag_matched_transition = Transition{
			[](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view transfer_function_string = "--transfer_function";
				return transfer_function_string.compare(string) == 0;
			},
			ParserStates::ExpectingTransferFunctionValue
		};
		auto matrix_coefficients_flag_matched_transition = Transition{
			[](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view matrix_coefficients_string = "--matrix_coefficients";
				return matrix_coefficients_string.compare(string) == 0;
			},
			ParserStates::ExpectingMatrixCoefficientsValue
		};
		auto video_full_range_flag_flag_matched_transition = Transition{
			[](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view video_full_range_flag_string = "--video_full_range_flag";
				return video_full_range_flag_string.compare(string) == 0;
			},
			ParserStates::ExpectingVideoFullRangeFlagValue
		};
		auto color_primaries_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				auto result = read_numeric_value(string);

				if (!result.has_value()) {
					switch (result.error().error_code_) {
					case ReadNumericValueErrorCode::UnrecognizedParameter:
						return false;
					case ReadNumericValueErrorCode::ValueOutsideRange:
						return std::unexpected{ TransitionError{ TransitionErrorCode::ValueOutsideRange, std::move(result.error().output_messages_) } };
					}
					return false;
				}

				color_primaries = *result;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto transfer_function_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				auto result = read_numeric_value(string);

				if (!result.has_value()) {
					switch (result.error().error_code_) {
					case ReadNumericValueErrorCode::UnrecognizedParameter:
						return false;
					case ReadNumericValueErrorCode::ValueOutsideRange:
						return std::unexpected{ TransitionError{ TransitionErrorCode::ValueOutsideRange, std::move(result.error().output_messages_) } };
					}
					return false;
				}

				transfer_function = *result;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto matrix_coefficients_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				auto result = read_numeric_value(string);

				if (!result.has_value()) {
					switch (result.error().error_code_) {
					case ReadNumericValueErrorCode::UnrecognizedParameter:
						return false;
					case ReadNumericValueErrorCode::ValueOutsideRange:
						return std::unexpected{ TransitionError{ TransitionErrorCode::ValueOutsideRange, std::move(result.error().output_messages_) } };
					}
					return false;
				}

				matrix_coefficients = *result;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto video_full_range_flag_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				auto result = read_numeric_value(string);

				if (!result.has_value()) {
					switch (result.error().error_code_) {
					case ReadNumericValueErrorCode::UnrecognizedParameter:
						return false;
					case ReadNumericValueErrorCode::ValueOutsideRange:
						return std::unexpected{ TransitionError{ TransitionErrorCode::ValueOutsideRange, std::move(result.error().output_messages_) } };
					}
					return false;
				}

				video_full_range_flag = *result;
				return true;
			},
			ParserStates::ExpectingFlag
		};


		using TransitionsType = std::vector<Transition>;
		auto action_found_transitions = TransitionsType{
			std::move(version_flag_matched_transition),
			std::move(help_flag_matched_transition),
			// The following transitions are reused in the flag found transitions
			preset_flag_matched_transition,
			narrow_flag_matched_transition,
			full_flag_matched_transition,
			overwrite_flag_matched_transition,
			color_primaries_flag_matched_transition,
			transfer_function_flag_matched_transition,
			matrix_coefficients_flag_matched_transition,
			video_full_range_flag_flag_matched_transition,
		};
		auto flag_found_transitions = TransitionsType{
			std::move(preset_flag_matched_transition),
			std::move(narrow_flag_matched_transition),
			std::move(full_flag_matched_transition),
			std::move(overwrite_flag_matched_transition),
			std::move(color_primaries_flag_matched_transition),
			std::move(transfer_function_flag_matched_transition),
			std::move(matrix_coefficients_flag_matched_transition),
			std::move(video_full_range_flag_flag_matched_transition),
		};
		auto preset_found_transitions = TransitionsType{
			std::move(bt709_value_matched_transition),
			std::move(linear_light_srgb_value_matched_transition),
			std::move(srgb_value_matched_transition),
			std::move(bt2020_10bit_value_matched_transition),
			std::move(bt2020_12bit_value_matched_transition),
			std::move(bt2100_pq_value_matched_transition),
			std::move(bt2100_hlg_value_matched_transition),
			std::move(dci_p3_value_matched_transition),
			std::move(display_p3_value_matched_transition),
			std::move(p3_d65_pq_value_matched_transition),
		};
		auto color_primaries_found_transitions       = TransitionsType{ std::move(color_primaries_value_matched_transition) };
		auto transfer_function_found_transitions     = TransitionsType{ std::move(transfer_function_value_matched_transition) };
		auto matrix_coefficients_found_transitions   = TransitionsType{ std::move(matrix_coefficients_value_matched_transition) };
		auto video_full_range_flag_found_transitions = TransitionsType{ std::move(video_full_range_flag_value_matched_transition) };

		auto parser_state_machine = StateMachine<ParserStates, Transition>{ ParserStates::ExpectingAction, SparseArray<ParserStates, TransitionsType>{ {
				{ ParserStates::ExpectingAction, action_found_transitions },
				{ ParserStates::ExpectingFlag, flag_found_transitions },
				{ ParserStates::ExpectingPresetValue, preset_found_transitions },
				{ ParserStates::ExpectingColorPrimariesValue, color_primaries_found_transitions },
				{ ParserStates::ExpectingTransferFunctionValue, transfer_function_found_transitions },
				{ ParserStates::ExpectingMatrixCoefficientsValue, matrix_coefficients_found_transitions },
				{ ParserStates::ExpectingVideoFullRangeFlagValue, video_full_range_flag_found_transitions }
		} } };

		// Start at 1 because the first command line parameter is the program name.
		// Loop until argc - 1 because the final parameter should be the file path.
		if (argc == 1) {
			// TODO: Handle this
		}
		for (int i = 1; i < argc - 1; i++) {
			auto transition_result = parser_state_machine.Transition(argv[i]);
			if (!transition_result.has_value()) {
				switch (transition_result.error().error_code_) {
				case TransitionErrorCode::StateNotInStateMachine:
					return std::unexpected{ ParseCommandLineParametersError{ ParseCommandLineParametersErrorCode::UnrecognizedParameter, { unrecognized_parameter, argv[i], newline } } };
				case TransitionErrorCode::NoTransitionMatchedPredicate:
					return std::unexpected{ ParseCommandLineParametersError{ ParseCommandLineParametersErrorCode::UnrecognizedParameter, { expected_value, argv[i], newline } } };
				case TransitionErrorCode::ValueOutsideRange:
					return std::unexpected{ ParseCommandLineParametersError{ ParseCommandLineParametersErrorCode::ValueOutsideRange, std::move(transition_result.error().output_messages_) } };
				}
			}
		}
		if (parser_state_machine.state_ != ParserStates::ExpectingFlag) {
			return std::unexpected{ ParseCommandLineParametersError{ ParseCommandLineParametersErrorCode::ExpectedValue, { expected_value, argv[argc - 1], newline } } };
		}


		// TODO: Test if a file path with a space and quotes ("C:\test images\test.png") is provided as one command line parameter
		std::string png_file_path(argv[argc - 1]);

		return CommandLineParameters(std::move(overwrite_cicp), std::move(color_primaries), std::move(transfer_function), std::move(matrix_coefficients), std::move(video_full_range_flag), std::move(png_file_path));
	}

} // namespace PNG_CICP_Editer
