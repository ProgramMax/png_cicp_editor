// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CommandLineParameters.hpp"

#include <cstdlib>
#include <iostream>
#include <string_view>

// TODO: possibly add --narrow

namespace {

	// flags
	static const std::string_view version_string               = "--version";
	static const std::string_view help_string                  = "--help";
	static const std::string_view preset_string                = "--preset";
	static const std::string_view color_primaries_string       = "--color_primaries";
	static const std::string_view transfer_function_string     = "--transfer_function";
	static const std::string_view matrix_coefficients_string   = "--matrix_coefficients";
	static const std::string_view video_full_range_flag_string = "--video_full_range_flag";

	// presets
	static const std::string_view bt709_string             = "bt.709";
	static const std::string_view linear_light_srgb_string = "linear-light-srgb";
	static const std::string_view srgb_string              = "srgb";
	static const std::string_view bt2020_10bit_string      = "bt.2020-10-bit";
	static const std::string_view bt2020_12bit_string      = "bt.2020-12-bit";
	static const std::string_view bt2100_pq_string         = "bt.2100-pq";
	static const std::string_view bt2100_hlg_string        = "bt.2100-hlg";
	static const std::string_view dci_p3_string            = "dci-p3";
	static const std::string_view display_p3_string        = "display-p3";

	// error messages
	static const std::string_view unrecognized_parameter = "Unrecognized command line parameter: ";
	static const std::string_view value_outside_range    = "Value outside 0-255 range: ";
	static const std::string_view expected_value         = "File path provided where a value was expected: ";

	void print_version() noexcept {
		std::cout << "cicp_inserter version 0.1" << std::endl;
	}

	void print_help() noexcept {
		print_version();
		std::cout <<
R"(This program allows you to insert CICP data into a PNG file.
CICP is an efficient way to specify color space.
It is standardized in ITU-T H.273, which can be found here:
https://www.itu.int/rec/T-REC-H.273

Example usage: cicp_inserter.exe --preset display-p3 C:\\images\\test.png

Presets:
	bt.709             Rec. ITU-R BT.709-6
	linear-light-srgb  linear-light sRGB
	srgb               IEC 61966-2-1 sRGB
	bt.2020-10-bit     Rec. ITU-R BT.2020-2 (10-bit system)
	bt.2020-12-bit     Rec. ITU-R BT.2020-2 (12-bit system)
	bt.2100-pq         Rec. ITU-R BT.2100-2 perceptual quantization (PQ) system
	bt.2100-hlg        Rec. ITU-R BT.2100-2 hybrid log-gamma (HLG) system
	dci-p3             SMPTE RP 431-2 with SMPTE ST 428-1 D-Cinema Distribution Master (DCI-P3)
	display-p3         Display P3

You can also specify individual CICP values.
Example usage: cicp_inserter.exe --primaries 1 --transfer_function 2 --matrix_coefficients 3 --full_range 1 C:\\images\\test.png

These can be mixed to override defaults. Values specified later override prior values.
Example usage: cicp_inserter.exe --preset display-p3 --full_range 0 C:\\images\\test.png
)" << std::endl;
	}

	std::optional<uint8_t> read_numeric_value(char const* parameter) noexcept {
		static constinit int base = 10;
		char* end_pointer = nullptr;
		long value = std::strtol(parameter, &end_pointer, base);
		if (errno == ERANGE || parameter == end_pointer) {
			std::cerr << unrecognized_parameter << parameter << std::endl;
			return std::nullopt;
		}

		if (value < 0 || value > 255) {
			std::cerr << value_outside_range << parameter << std::endl;
			return std::nullopt;
		}

		return static_cast<uint8_t>(value);
	}

} // anonymous namespace

namespace CICP_Inserter {

	CommandLineParameters::CommandLineParameters(uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag, std::string png_file_path) noexcept
		: color_primaries_(std::move(color_primaries))
		, transfer_function_(std::move(transfer_function))
		, matrix_coefficients_(std::move(matrix_coefficients))
		, video_full_range_flag_(std::move(video_full_range_flag))
		, png_file_path_(std::move(png_file_path))
	{
	}

	std::optional<CommandLineParameters> parse_command_line_parameters(int argc, char const* argv[]) noexcept {
		// This operates as a state machine.
		// 
		// The ExpectedState enum is used to indicate which variable should come next.
		// For example, "--preset srgb". Parsing "--preset" puts the state machine in the Preset state.
		// That way, we know to expect a preset as the next parameter.
		// 
		// This also works for "--color_primaries" which is followed by a numeric value.
		enum ExpectedState {
			None,
			Preset,
			ColorPrimaries,
			TransferFunction,
			MatrixCoefficients,
			VideoFullRangeFlag,
		};
		auto expected_state = ExpectedState::None;

		uint8_t color_primaries = 0;
		uint8_t transfer_function = 0;
		uint8_t matrix_coefficients = 1;
		uint8_t video_full_range_flag = 1;

		// Start at 1 because the first command line parameter is the program name.
		// Loop until argc - 1 because the final parameter should be the file path.
		if (argc == 1) {

		}
		for (int i = 1; i < argc - 1; i++) {
			if (expected_state == ExpectedState::None) {
				if (version_string.compare(argv[i]) == 0) {
					print_version();
				}
				else if (help_string.compare(argv[i]) == 0) {
					print_help();
				}
				else if (preset_string.compare(argv[i]) == 0) {
					expected_state = ExpectedState::Preset;
				}
				else if (color_primaries_string.compare(argv[i]) == 0) {
					expected_state = ExpectedState::ColorPrimaries;
				}
				else if (transfer_function_string.compare(argv[i]) == 0) {
					expected_state = ExpectedState::TransferFunction;
				}
				else if (matrix_coefficients_string.compare(argv[i]) == 0) {
					expected_state = ExpectedState::MatrixCoefficients;
				}
				else if (video_full_range_flag_string.compare(argv[i]) == 0) {
					expected_state = ExpectedState::VideoFullRangeFlag;
				}
				else {
					std::cerr << unrecognized_parameter << argv[i] << std::endl;
					return std::nullopt;
				}
			}
			else if (expected_state == ExpectedState::Preset) {
				if (bt709_string.compare(argv[i]) == 0) {
					color_primaries = 1;
					transfer_function = 1;
					expected_state = ExpectedState::None;
				}
				else if (linear_light_srgb_string.compare(argv[i]) == 0) {
					color_primaries = 1;
					transfer_function = 8;
					expected_state = ExpectedState::None;
				}
				else if (srgb_string.compare(argv[i]) == 0) {
					color_primaries = 1;
					transfer_function = 13;
					expected_state = ExpectedState::None;
				}
				else if (bt2020_10bit_string.compare(argv[i]) == 0) {
					color_primaries = 9;
					transfer_function = 14;
					expected_state = ExpectedState::None;
				}
				else if (bt2020_12bit_string.compare(argv[i]) == 0) {
					color_primaries = 9;
					transfer_function = 15;
					expected_state = ExpectedState::None;
				}
				else if (bt2100_pq_string.compare(argv[i]) == 0) {
					color_primaries = 9;
					transfer_function = 16;
					expected_state = ExpectedState::None;
				}
				else if (bt2100_hlg_string.compare(argv[i]) == 0) {
					color_primaries = 9;
					transfer_function = 18;
					expected_state = ExpectedState::None;
				}
				else if (dci_p3_string.compare(argv[i]) == 0) {
					color_primaries = 11;
					transfer_function = 17;
					expected_state = ExpectedState::None;
				}
				else if (display_p3_string.compare(argv[i]) == 0) {
					color_primaries = 12;
					transfer_function = 13;
					expected_state = ExpectedState::None;
				}
				else {
					std::cerr << unrecognized_parameter << argv[i] << std::endl;
					return std::nullopt;
				}
			}
			else if (expected_state == ExpectedState::ColorPrimaries) {
				auto value = read_numeric_value(argv[i]);
				if (!value.has_value()) {
					return std::nullopt;
				}

				color_primaries = *value;
				expected_state = ExpectedState::None;
			}
			else if (expected_state == ExpectedState::TransferFunction) {
				auto value = read_numeric_value(argv[i]);
				if (!value.has_value()) {
					return std::nullopt;
				}

				transfer_function = *value;
				expected_state = ExpectedState::None;
			}
			else if (expected_state == ExpectedState::MatrixCoefficients) {
				auto value = read_numeric_value(argv[i]);
				if (!value.has_value()) {
					return std::nullopt;
				}

				matrix_coefficients = *value;
				expected_state = ExpectedState::None;
			}
			else if (expected_state == ExpectedState::VideoFullRangeFlag) {
				auto value = read_numeric_value(argv[i]);
				if (!value.has_value()) {
					return std::nullopt;
				}

				video_full_range_flag = *value;
				expected_state = ExpectedState::None;
			}
			else {
				std::cerr << unrecognized_parameter << argv[i] << std::endl;
				return std::nullopt;
			}
		}

		// TODO: Test if a file path with a space and quotes ("C:\test images\test.png") is provided as one command line parameter
		if (expected_state != ExpectedState::None) {
			std::cerr << expected_value << argv[argc - 1] << std::endl;
			return std::nullopt;
		}
		std::string png_file_path(argv[argc - 1]);

		return CommandLineParameters(std::move(color_primaries), std::move(transfer_function), std::move(matrix_coefficients), std::move(video_full_range_flag), std::move(png_file_path));
	}

} // namespace CICP_Inserter
