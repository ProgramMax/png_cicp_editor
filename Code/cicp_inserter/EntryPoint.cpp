// Copyright 2025, The png_cicp_editer Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

#include "CICPCreator.hpp"
#include "CICPInserter.hpp"
#include "CommandLineParameters.hpp"
#include "Error.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "PNGParser.hpp"

int main(int argc, char const* argv[]) noexcept {
	// Parse the command line parameters
	auto command_line_parameters = PNG_CICP_Editer::parse_command_line_parameters(argc, argv);
	if (!command_line_parameters.has_value()) {
		if (command_line_parameters.error().error_code_ == PNG_CICP_Editer::ParseCommandLineParametersErrorCode::NotActuallyAnError) {
			return 0;
		}

		print_error(command_line_parameters.error());
		return 1;
	}


	// Read the file
	auto file_contents = PNG_CICP_Editer::read_file(command_line_parameters->png_file_path_);
	if (!file_contents.has_value()) {
		print_error(file_contents.error());
		return 1;
	}


	// Get indicies of all chunks
	auto chunk_indices = PNG_CICP_Editer::get_chunk_indices(file_contents.value());
	if (!chunk_indices.has_value()) {
		print_error(chunk_indices.error());
		return 1;
	}


	// Find insertion index for cICP chunk
	auto split_buffer= PNG_CICP_Editer::get_split_buffer_across_cicp_insertion_point(file_contents.value(), chunk_indices.value(), command_line_parameters->overwrite_cicp_);
	if (!split_buffer.has_value()) {
		print_error(split_buffer.error());
		return 1;
	}


	// Prepare cICP buffer to write
	auto cicp_buffer = PNG_CICP_Editer::create_cicp_buffer(command_line_parameters->color_primaries_, command_line_parameters->transfer_function_, command_line_parameters->matrix_coefficients_, command_line_parameters->video_full_range_flag_);


	// Prepare file before & after buffers for write
	std::vector<std::span<char>> buffers;
	buffers.push_back({ split_buffer.value()[0] });
	buffers.push_back({ cicp_buffer });
	buffers.push_back({ split_buffer.value()[1] });


	// Write the file with cICP inserted
	auto write_result = PNG_CICP_Editer::write_file(command_line_parameters->png_file_path_, buffers);
	if (!write_result.has_value()) {
		print_error(write_result.error());
		return 1;
	}


	return 0;
}