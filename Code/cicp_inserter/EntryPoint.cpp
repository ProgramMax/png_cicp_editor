// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

#include "CommandLineParameters.hpp"
#include "FileReader.hpp"

namespace {

	template<typename T>
	void print_error(T error) noexcept {
		for (auto& message : error.output_messages_) {
			std::cerr << message;
		}
	}

} // anonymous namespace

int main(int argc, char const* argv[]) noexcept {
	// Parse the command line parameters
	auto command_line_parameters = CICP_Inserter::parse_command_line_parameters(argc, argv);
	if (!command_line_parameters.has_value()) {
		if (command_line_parameters.error().error_code_ == CICP_Inserter::ParseCommandLineParametersErrorCode::NotActuallyAnError) {
			return 0;
		}

		print_error(std::move(command_line_parameters.error()));
		return 1;
	}

	auto file_contents = CICP_Inserter::read_file(command_line_parameters->png_file_path_);
	// TODO: Process

	return 0;
}