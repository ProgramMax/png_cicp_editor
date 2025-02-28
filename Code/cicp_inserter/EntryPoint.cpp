// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

#include "CICPInserter.hpp"
#include "CommandLineParameters.hpp"
#include "Error.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "PNGParser.hpp"

int main(int argc, char const* argv[]) noexcept {
	// Parse the command line parameters
	auto command_line_parameters = CICP_Inserter::parse_command_line_parameters(argc, argv);
	if (!command_line_parameters.has_value()) {
		if (command_line_parameters.error().error_code_ == CICP_Inserter::ParseCommandLineParametersErrorCode::NotActuallyAnError) {
			return 0;
		}

		print_error(command_line_parameters.error());
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


	// Prepare cICP buffer to write


	// Prepare file before & after buffers for write
	std::vector<std::span<char>> buffers;
	auto file_contents_start = file_contents.value().data();
	auto insertion_index_value = insertion_index.value();
	buffers.push_back({ file_contents_start, file_contents_start + insertion_index_value });
	buffers.push_back({ file_contents_start + insertion_index_value, file_contents.value().size() - insertion_index_value });


	// Write the file with cICP inserted
	auto write_result = CICP_Inserter::write_file(command_line_parameters->png_file_path_, buffers);
	if (!write_result.has_value()) {
		print_error(write_result.error());
		return 1;
	}


	return 0;
}