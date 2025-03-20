// Copyright 2025, The png_cicp_editer Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITER_COMMANDLINEPARAMETERS_HPP
#define PNG_CICP_EDITER_COMMANDLINEPARAMETERS_HPP

#include <cstdint>
#include <expected>
#include <string>
#include <utility>
#include <vector>

#include "Error.hpp"

namespace PNG_CICP_Editer {

	class CommandLineParameters {
	public:

		CommandLineParameters(bool overwrite_cicp, uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag, std::string png_file_path) noexcept;

		bool overwrite_cicp_;
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
	using ParseCommandLineParametersError = ErrorWithCode<ParseCommandLineParametersErrorCode>;

	std::expected<CommandLineParameters, ParseCommandLineParametersError> parse_command_line_parameters(int argc, char const* argv[]) noexcept;

} // namespace PNG_CICP_Editer

#endif // #ifndef PNG_CICP_EDITER_COMMANDLINEPARAMETERS_HPP
