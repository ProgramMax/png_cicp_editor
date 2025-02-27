// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CICP_INSERTER_COMMANDLINEPARAMETERS_HPP
#define CICP_INSERTER_COMMANDLINEPARAMETERS_HPP

#include <cstdint>
#include <expected>
#include <string>
#include <utility>
#include <vector>

namespace CICP_Inserter {

	class CommandLineParameters {
	public:

		CommandLineParameters(uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag, std::string png_file_path) noexcept;

		uint8_t color_primaries_;
		uint8_t transfer_function_;
		uint8_t matrix_coefficients_;
		uint8_t video_full_range_flag_;
		std::string png_file_path_;

	};

	enum class ParseCommandLineParametersErrorCode {
		UnrecognizedParameter,
		ValueOutsideRange,
		ExpectedValue,
		NotActuallyAnError, // TODO: Find a good way to separate actions (--help, --version) from returning a CommandLineParameters and remove this
	};

	class ParseCommandLineParametersError {
	public:

		explicit ParseCommandLineParametersError(ParseCommandLineParametersErrorCode error_code, std::vector<char const*> output_messages) noexcept;

		ParseCommandLineParametersErrorCode error_code_;
		std::vector<char const*> output_messages_;

	};

	std::expected<CommandLineParameters, ParseCommandLineParametersError> parse_command_line_parameters(int argc, char const* argv[]) noexcept;

} // namespace CICP_Inserter

#endif // #ifndef CICP_INSERTED_COMMANDLINEPARAMETERS_HPP