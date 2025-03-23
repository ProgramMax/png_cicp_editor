// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>
#include <variant>

#include "CommandLineParameters.hpp"
#include "Error.hpp"


int main(int argc, char const* argv[]) noexcept {
	// Parse the command line parameters
	auto command_line_parameters = PNG_CICP_Editor::parse_command_line_parameters(argc, argv);
	if (!command_line_parameters.has_value()) {
		if (command_line_parameters.error().error_code_ == PNG_CICP_Editor::ParseCommandLineParametersErrorCode::NotActuallyAnError) {
			return 0;
		}

		print_error(command_line_parameters.error());
		return 1;
	}

	switch (command_line_parameters->action_type_) {
	case PNG_CICP_Editor::Actions::Version:
		command_line_parameters->action_.version_();
		break;
	case PNG_CICP_Editor::Actions::Help:
		command_line_parameters->action_.help_();
		break;
	case PNG_CICP_Editor::Actions::License:
		command_line_parameters->action_.license_();
		break;
	case PNG_CICP_Editor::Actions::Add:
		command_line_parameters->action_.add_();
		break;
	case PNG_CICP_Editor::Actions::Overwrite:
		command_line_parameters->action_.overwrite_();
		break;
	case PNG_CICP_Editor::Actions::Remove:
		command_line_parameters->action_.remove_();
		break;
	}

	return 0;
}