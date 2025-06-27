// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <type_traits>
#include <utility>

#include "Actions.hpp"
#include "CommandLineParameters.hpp"
#include "Error.hpp"

namespace {

	using parsed_command_line_type = std::invoke_result_t<decltype(PNG_CICP_Editor::parse_command_line_parameters), int, char const*[]>;

	parsed_command_line_type execute_action(PNG_CICP_Editor::Action action) noexcept {
		std::visit(PNG_CICP_Editor::ActionExecutor(), action);
		return action;
	}

} // anonymous namespace

int main(int argc, char const* argv[]) noexcept {
	using namespace PNG_CICP_Editor;

	return ! PNG_CICP_Editor::parse_command_line_parameters(argc, argv)
		.transform_error(print_monad_error<ParseCommandLineParametersError>)
		.and_then(execute_action)
		.has_value();
}