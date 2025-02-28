// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

#include "CICPInserter.hpp"
#include "CommandLineParameters.hpp"
#include "FileReader.hpp"
#include "PNGParser.hpp"

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


	// Read the file
	auto file_contents = CICP_Inserter::read_file(command_line_parameters->png_file_path_);
	if (!file_contents.has_value()) {
		print_error(file_contents.error());
		return 1;
	}


	// Get indicies of all chunks
	auto chunk_indices = CICP_Inserter::get_chunk_indices(file_contents.value());
	if (!chunk_indices.has_value()) {
		print_error(chunk_indices.error());
		return 1;
	}


	// Find insertion index for cICP chunk
	auto insertion_index = CICP_Inserter::get_insertion_index(file_contents.value(), chunk_indices.value());
	if (!insertion_index.has_value()) {
		print_error(insertion_index.error());
		return 1;
	}


	return 0;
}