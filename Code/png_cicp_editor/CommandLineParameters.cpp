// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CommandLineParameters.hpp"

#include <cstdlib>
#include <functional>
#include <string_view>
#include <utility>
#include <vector>

#include "StateMachine.hpp"
#include "SparseArray.hpp"

#include <max/Compiling/Unreachable.hpp>

namespace {

	enum class Actions {
		Version,
		Help,
		License,
		Add,
		Overwrite,
		Remove,
	};

	// error messages
	static constinit std::string_view unrecognized_parameter = "Unrecognized command line parameter: ";
	static constinit std::string_view value_outside_range    = "Value outside 0-255 range: ";
	static constinit std::string_view expected_value         = "File path provided where a value was expected: ";

	// utility
	static constinit std::string_view newline                = "\n";

	enum class ReadNumericValueErrorCode {
		UnrecognizedParameter,
		ValueOutsideRange,
	};
	using ReadNumericValueError = PNG_CICP_Editor::ErrorWithCode<ReadNumericValueErrorCode>;

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

	PNG_CICP_Editor::ParseCommandLineParametersError convert_error(ReadNumericValueError error) noexcept {
		PNG_CICP_Editor::ParseCommandLineParametersErrorCode new_error_code;
		switch (error.error_code_) {
		case ReadNumericValueErrorCode::UnrecognizedParameter:
			new_error_code = PNG_CICP_Editor::ParseCommandLineParametersErrorCode::UnrecognizedParameter;
			break;
		case ReadNumericValueErrorCode::ValueOutsideRange:
			new_error_code = PNG_CICP_Editor::ParseCommandLineParametersErrorCode::ValueOutsideRange;
			break;
		default:
			std::unreachable();
		}

		return PNG_CICP_Editor::ParseCommandLineParametersError{ std::move(new_error_code), std::move(error.output_messages_) };
	}

} // anonymous namespace

namespace PNG_CICP_Editor {

	std::expected<Action, ParseCommandLineParametersError> parse_command_line_parameters(int argc, char const* argv[]) noexcept {
		enum class ParserStates {
			ExpectingAction,
			ExpectingFlag,
			ExpectingPresetValue,
			ExpectingColorPrimariesValue,
			ExpectingTransferFunctionValue,
			ExpectingMatrixCoefficientsValue,
			ExpectingVideoFullRangeFlagValue,
			ExpectingFlagOrFile,
			ExpectingFile,
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

		auto action = Actions::Help;
		auto cicp = CICP{ /*color_primaires=*/0, /*transfer_function=*/0, /*matrix_coefficients=*/0, /*video_full_range_flag=*/1 };
		char const* file_path = "";


		auto version_action_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view version_string = "--version";
				static const std::string_view v_string         = "-v";
				if (version_string.compare(string) != 0 && v_string.compare(string) != 0) {
					return false;
				}
				action = Actions::Version;
				return true;
			},
			ParserStates::Done
		};
		auto help_action_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view help_string = "--help";
				static const std::string_view h_string    = "-h";
				if (help_string.compare(string) != 0 && h_string.compare(string) != 0) {
					return false;
				}
				action = Actions::Help;
				return true;
			},
			ParserStates::Done
		};
		auto license_action_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view license_string = "--license";
				if (license_string.compare(string) != 0) {
					return false;
				}
				action = Actions::License;
				return true;
			},
			ParserStates::Done
		};
		auto add_action_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view add_string = "add";
				if (add_string.compare(string) != 0) {
					return false;
				}
				action = Actions::Add;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto overwrite_action_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view overwrite_string = "overwrite";
				if (overwrite_string.compare(string) != 0) {
					return false;
				}
				action = Actions::Overwrite;
				return true;
			},
			ParserStates::ExpectingFlag
		};
		auto remove_action_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view remove_string = "remove";
				if (remove_string.compare(string) != 0) {
					return false;
				}
				action = Actions::Remove;
				return true;
			},
			ParserStates::ExpectingFile
		};
		auto preset_flag_matched_transition = Transition{
			[](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view preset_string = "--preset";
				static const std::string_view p_string      = "-p";
				return (preset_string.compare(string) == 0) || (p_string.compare(string) == 0);
			},
			ParserStates::ExpectingPresetValue
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
		auto narrow_flag_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view narrow_string = "--narrow";
				static const std::string_view n_string = "-n";
				if (narrow_string.compare(string) != 0 && n_string.compare(string) != 0) {
					return false;
				}
				cicp.video_full_range_flag_ = 0;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto full_flag_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view full_string = "--full";
				static const std::string_view f_string = "-f";
				if (full_string.compare(string) != 0 && f_string.compare(string) != 0) {
					return false;
				}
				cicp.video_full_range_flag_ = 1;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto file_found_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				file_path = string;
				return true;
			},
			ParserStates::Done
		};
		auto bt601_pal_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt601_pal_string = "bt.601-pal";
				if (bt601_pal_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 5;
				cicp.transfer_function_ = 6;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto bt601_ntsc_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt601_ntsc_string = "bt.601-ntsc";
				if (bt601_ntsc_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 6;
				cicp.transfer_function_ = 6;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto bt709_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt709_string = "bt.709";
				if (bt709_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 1;
				cicp.transfer_function_ = 1;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto linear_light_srgb_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view linear_light_srgb_string = "linear-light-srgb";
				if (linear_light_srgb_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 1;
				cicp.transfer_function_ = 8;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto srgb_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view srgb_string = "srgb";
				if (srgb_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 1;
				cicp.transfer_function_ = 13;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto bt2020_10bit_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt2020_10bit_string = "bt.2020-10-bit";
				if (bt2020_10bit_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 9;
				cicp.transfer_function_ = 14;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto bt2020_12bit_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt2020_12bit_string = "bt.2020-12-bit";
				if (bt2020_12bit_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 9;
				cicp.transfer_function_ = 15;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto bt2100_pq_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt2100_pq_string = "bt.2100-pq";
				if (bt2100_pq_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 9;
				cicp.transfer_function_ = 16;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto bt2100_hlg_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view bt2100_hlg_string = "bt.2100-hlg";
				if (bt2100_hlg_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 9;
				cicp.transfer_function_ = 18;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto dci_p3_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view dci_p3_string = "dci-p3";
				if (dci_p3_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 11;
				cicp.transfer_function_ = 17;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto display_p3_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view display_p3_string = "display-p3";
				if (display_p3_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 12;
				cicp.transfer_function_ = 13;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};
		auto p3_d65_pq_value_matched_transition = Transition{
			[&](char const* string) -> Transition::PredicateAndActionResultType {
				static const std::string_view p3_d65_pq_string = "p3-d65-pq";
				if (p3_d65_pq_string.compare(string) != 0) {
					return false;
				}
				cicp.color_primaries_ = 12;
				cicp.transfer_function_ = 16;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
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

				cicp.color_primaries_ = *result;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
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

				cicp.transfer_function_ = *result;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
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

				cicp.matrix_coefficients_ = *result;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
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

				cicp.video_full_range_flag_ = *result;
				return true;
			},
			ParserStates::ExpectingFlagOrFile
		};


		using TransitionsType = std::vector<Transition>;
		auto action_found_transitions = TransitionsType{
			std::move(version_action_matched_transition),
			std::move(help_action_matched_transition),
			std::move(license_action_matched_transition),
			std::move(add_action_matched_transition),
			std::move(overwrite_action_matched_transition),
			std::move(remove_action_matched_transition),
		};
		auto flag_found_transitions = TransitionsType{
			// Note: These are not moved because they are used below
			preset_flag_matched_transition,
			narrow_flag_matched_transition,
			full_flag_matched_transition,
			color_primaries_flag_matched_transition,
			transfer_function_flag_matched_transition,
			matrix_coefficients_flag_matched_transition,
			video_full_range_flag_flag_matched_transition,
		};
		auto flag_or_file_found_transitions = TransitionsType{
			std::move(preset_flag_matched_transition),
			std::move(narrow_flag_matched_transition),
			std::move(full_flag_matched_transition),
			std::move(color_primaries_flag_matched_transition),
			std::move(transfer_function_flag_matched_transition),
			std::move(matrix_coefficients_flag_matched_transition),
			std::move(video_full_range_flag_flag_matched_transition),
			// Note: These are not moved because they are used below
			file_found_transition,
		};
		auto preset_value_found_transitions = TransitionsType{
			std::move(bt601_pal_value_matched_transition),
			std::move(bt601_ntsc_value_matched_transition),
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
		auto file_found_transitions                  = TransitionsType{ std::move(file_found_transition) };

		auto parser_state_machine = StateMachine<ParserStates, Transition>{ ParserStates::ExpectingAction, SparseArray<ParserStates, TransitionsType>{ {
				{ ParserStates::ExpectingAction, action_found_transitions },
				{ ParserStates::ExpectingFlag, flag_found_transitions },
				{ ParserStates::ExpectingFlagOrFile, flag_or_file_found_transitions },
				{ ParserStates::ExpectingPresetValue, preset_value_found_transitions },
				{ ParserStates::ExpectingColorPrimariesValue, color_primaries_found_transitions },
				{ ParserStates::ExpectingTransferFunctionValue, transfer_function_found_transitions },
				{ ParserStates::ExpectingMatrixCoefficientsValue, matrix_coefficients_found_transitions },
				{ ParserStates::ExpectingVideoFullRangeFlagValue, video_full_range_flag_found_transitions },
				{ ParserStates::ExpectingFile, file_found_transitions },
		} } };

		// Start at 1 because the first command line parameter is the program name.
		// Loop until argc - 1 because the final parameter should be the file path.
		if (argc == 1) {
			// TODO: Handle this
		}
		for (int i = 1; i < argc; i++) {
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
		if (parser_state_machine.state_ != ParserStates::Done) {
			return std::unexpected{ ParseCommandLineParametersError{ ParseCommandLineParametersErrorCode::ExpectedValue, { expected_value, argv[argc - 1], newline } } };
		}


		// TODO: Test if a file path with a space and quotes ("C:\test images\test.png") is provided as one command line parameter

		switch (action) {
		case Actions::Version:
			return Action{ VersionAction{} };
		case Actions::Help:
			return Action{ HelpAction{} };
		case Actions::License:
			return Action{ LicenseAction{} };
		case Actions::Add:
			return Action{ AddAction{ std::move(cicp), std::move(file_path) } };
		case Actions::Overwrite:
			return Action{ OverwriteAction{ std::move(cicp), std::move(file_path) } };
		case Actions::Remove:
			return Action{ RemoveAction{ std::move(file_path) } };
		}
		MAX_UNREACHABLE;

	}

} // namespace PNG_CICP_Editor
