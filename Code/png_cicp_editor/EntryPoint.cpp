// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Actions.hpp"
#include "CommandLineParameters.hpp"
#include "Error.hpp"

int main(int argc, char const* argv[]) noexcept {
	// Parse the command line parameters
	auto command_line_parameters = PNG_CICP_Editor::parse_command_line_parameters(argc, argv);
	if (!command_line_parameters.has_value()) {
		print_error(command_line_parameters.error());
		return 1;
	}

	std::visit(PNG_CICP_Editor::ActionExecutor(), *command_line_parameters);

	return 0;
}