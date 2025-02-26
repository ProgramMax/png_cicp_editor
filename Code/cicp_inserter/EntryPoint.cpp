// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CommandLineParameters.hpp"
#include "FileReader.hpp"

int main(int argc, char *argv[]) noexcept {
	auto command_line_parameters = CICP_Inserter::parse_command_line_parameters(argc, argv);
	if (!command_line_parameters.has_value()) {
		return 1;
	}

	auto file_contents = CICP_Inserter::read_file(command_line_parameters->png_file_path_);
	// TODO: Process

	return 0;
}