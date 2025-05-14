// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_COMMANDLINEPARAMETERS_HPP
#define PNG_CICP_EDITOR_COMMANDLINEPARAMETERS_HPP

#include <cstdint>
#include <expected>
#include <optional>
#include <string>

#include "Actions.hpp"
#include "Error.hpp"

namespace PNG_CICP_Editor {

	/*
	class foo {
		Actions action_type_;
		std::optional<uint8_t> color_primaries_;
		std::optional<uint8_t> transfer_function_;
		uint8_t matrix_coefficients_;
		uint8_t video_full_range_flag_;
		std::string file_path_;
	};
	*/

	enum class ParseCommandLineParametersErrorCode {
		UnrecognizedParameter,
		ValueOutsideRange,
		ExpectedValue,
	};
	using ParseCommandLineParametersError = ErrorWithCode<ParseCommandLineParametersErrorCode>;

	std::expected<Action, ParseCommandLineParametersError> parse_command_line_parameters(int argc, char const* argv[]) noexcept;

} // namespace PNG_CICP_Editor

#endif // #ifndef PNG_CICP_EDITOR_COMMANDLINEPARAMETERS_HPP
