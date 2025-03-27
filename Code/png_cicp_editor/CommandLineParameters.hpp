// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_COMMANDLINEPARAMETERS_HPP
#define PNG_CICP_EDITOR_COMMANDLINEPARAMETERS_HPP

#include <expected>

#include "Actions.hpp"
#include "Error.hpp"

namespace PNG_CICP_Editor {

	enum class ParseCommandLineParametersErrorCode {
		UnrecognizedParameter,
		ValueOutsideRange,
		ExpectedValue,
	};
	using ParseCommandLineParametersError = ErrorWithCode<ParseCommandLineParametersErrorCode>;

	std::expected<Action, ParseCommandLineParametersError> parse_command_line_parameters(int argc, char const* argv[]) noexcept;

} // namespace PNG_CICP_Editor

#endif // #ifndef PNG_CICP_EDITOR_COMMANDLINEPARAMETERS_HPP
