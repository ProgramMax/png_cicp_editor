// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Actions.hpp"

#include <iostream>
#include <utility>

#include <max/Compiling/Configuration.hpp>

#include "CICPCreator.hpp"
#include "CICPInserter.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "PNGParser.hpp"

namespace {

	void print_bsd_3_clause_license(const std::string_view year, const std::string_view copyright_holder) noexcept {
		std::cout << "Copyright " << year << ", " << copyright_holder << R"(
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

    * Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the
distribution.
    * Neither the name of copyright holder nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
)";
	}

} // anonymous namespace

namespace PNG_CICP_Editor {

	AddAction::AddAction(CICP cicp, std::string file_path) noexcept
		: cicp_(std::move(cicp))
		, file_path_(std::move(file_path))
	{}

	OverwriteAction::OverwriteAction(CICP cicp, std::string file_path) noexcept
		: cicp_(std::move(cicp))
		, file_path_(std::move(file_path))
	{}

	RemoveAction::RemoveAction(std::string file_path) noexcept
		: file_path_(std::move(file_path))
	{}

	void ActionExecutor::operator()(const VersionAction&) const noexcept {
		std::cout << "png_cicp_editor version 3.0" << std::endl;
	}

	void ActionExecutor::operator()(const HelpAction&) const noexcept {
#if defined(MAX_PLATFORM_WINDOWS)
		static constinit auto program_name = std::string_view{ "png_cicp_editor.exe" };
		static constinit auto file_path = std::string_view{ R"(C:\images\test.png)" };
#elif defined(MAX_PLATFORM_LINUX) || defined(MAX_PLATFORM_MACOS)
		static constinit auto program_name = std::string_view{ "png_cicp_editor" };
		static constinit auto file_path = std::string_view{ R"(/images/test.png)" };
#else
		static_assert( false, "Unknown platform" );
#endif

		// Print version
		operator()(VersionAction{});

		std::cout <<
			R"(This program enabled CICP editing within a PNG file.
CICP is an efficient way to specify color space.
It is standardized in ITU-T H.273, which can be found here:
https://www.itu.int/rec/T-REC-H.273

Example usage: )" << program_name << R"( add --preset display-p3 )" << file_path << R"(

Presets:
	bt.601-pal      Rec. ITU-R BT.601 625-line 50 Hz (PAL)
	bt.601-ntsc     Rec. ITU-R BT.601 525-line 60 Hz (NTSC)
	bt.709          Rec. ITU-R BT.709-6
	srgb-linear     linear-light sRGB
	srgb            IEC 61966-2-1 sRGB
	bt.2020-10-bit  Rec. ITU-R BT.2020-2 (10-bit system)
	bt.2020-12-bit  Rec. ITU-R BT.2020-2 (12-bit system)
	bt.2100-pq      Rec. ITU-R BT.2100-2 perceptual quantization (PQ) system
	bt.2100-hlg     Rec. ITU-R BT.2100-2 hybrid log-gamma (HLG) system
	dci-p3          SMPTE RP 431-2 with SMPTE ST 428-1 D-Cinema Distribution Master (DCI-P3)
	display-p3      Display P3
	p3-d65-pq       P3-D65 PQ

You can also specify individual CICP values. For example, to label an RGB image decoded from a SECAM video:
Example usage: )" << program_name << R"( add --color_primaries 5 --transfer_function 4 --matrix_coefficients 0 --video_full_range_flag 1 )" << file_path << R"(

These can be mixed to override defaults. Values specified later override prior values.
Example usage: )" << program_name << R"( add --preset display-p3 --video_full_range_flag 0 )" << file_path << R"(

Actions:
	-h --help             Show help information (what you are viewing now)
	-v --version          Show version information
	   --license          Show license information
	add [flags]           Adds a new cICP chunk to the PNG file
	overwrite [flags]     Adds a new or overwrites an existing cICP chunk
	remove                Removes the cICP chunk from the PNG file

General flags:
	-p --preset [value]   Use [value]'s CICP values
	-n --narrow           Use narrow range (--video_full_range_flag 0)
	-f --full             Use full range (--video_full_range_flag 1)

Specific flags to match CICP parameter names from ITU-T H.273 (experts only):
	   --color_primaries [value]
	   --transfer_function [value]
	   --matrix_coefficients [value]
	   --video_full_range_flag [value]
Note: Specific flags use values from ITU-T H.273. Not all values are valid.
PNG puts further restrictions on which values are valid.
)" << std::endl;
	}

	void ActionExecutor::operator()(const LicenseAction&) const noexcept {
		static const auto png_cicp_editor_year = std::string_view{"2025"};
		static const auto png_cicp_editor_copyright_holder = std::string_view{"The png_cicp_editor Contributors"};
		print_bsd_3_clause_license(png_cicp_editor_year, png_cicp_editor_copyright_holder);

		std::cout << R"(
png_cicp_editor depends on max:
)";

		static const auto max_year = std::string_view{"2025"};
		static const auto max_copyright_holder = std::string_view{"The max Contributors"};
		print_bsd_3_clause_license(max_year, max_copyright_holder);
	}

	void ActionExecutor::operator()(const AddAction& action) const noexcept {
		// TODO: Return error values

		auto file_contents = read_file(action.file_path_)
			.transform_error(print_monad_error<ReadFileError>);
		if (!file_contents.has_value()) {
			return;
		}

		auto chunk_indices = get_chunk_indices(file_contents.value())
			.transform_error(print_monad_error<GetChunkIndicesError>);
		if (!chunk_indices.has_value()) {
			return;
		}

		auto split_buffer = get_split_buffer_across_cicp_insertion_point(file_contents.value(), chunk_indices.value(), /*overwrite_cicp*/ false)
			.transform_error(print_monad_error<GetInsertionIndexError>);
		if (!split_buffer.has_value()) {
			return;
		}

		// Prepare cICP buffer to write
		auto cicp_buffer = create_cicp_buffer(action.cicp_);


		// Prepare file before & after buffers for write
		std::vector<std::span<char>> buffers;
		buffers.push_back({ split_buffer.value()[0] });
		buffers.push_back({ cicp_buffer });
		buffers.push_back({ split_buffer.value()[1] });


		// Write the file with cICP inserted
		auto write_result = PNG_CICP_Editor::write_file(action.file_path_, buffers)
			.transform_error(print_monad_error<WriteFileError>);
		if (!write_result.has_value()) {
			return;
		}
	}

	void ActionExecutor::operator()(const OverwriteAction& action) const noexcept {
		// TODO: Return error values
		// Read the file
		auto file_contents = read_file(action.file_path_)
			.transform_error(print_monad_error<ReadFileError>);
		if (!file_contents.has_value()) {
			return;
		}


		// Get indicies of all chunks
		auto chunk_indices = get_chunk_indices(file_contents.value())
			.transform_error(print_monad_error<GetChunkIndicesError>);
		if (!chunk_indices.has_value()) {
			return;
		}


		// Find overwrite index for cICP chunk
		auto split_buffer = get_split_buffer_across_cicp_insertion_point(file_contents.value(), chunk_indices.value(), /*overwrite_cicp*/ true)
			.transform_error(print_monad_error<GetInsertionIndexError>);
		if (!split_buffer.has_value()) {
			return;
		}


		// Prepare cICP buffer to write
		auto cicp_buffer = create_cicp_buffer(action.cicp_);


		// Prepare file before & after buffers for write
		std::vector<std::span<char>> buffers;
		buffers.push_back({ split_buffer.value()[0] });
		buffers.push_back({ cicp_buffer });
		buffers.push_back({ split_buffer.value()[1] });


		// Write the file with cICP inserted
		auto write_result = PNG_CICP_Editor::write_file(action.file_path_, buffers)
			.transform_error(print_monad_error<WriteFileError>);
		if (!write_result.has_value()) {
			return;
		}
	}

	void ActionExecutor::operator()(const RemoveAction& action) const noexcept {
		// TODO: Return error values
		// Read the file
		auto file_contents = read_file(action.file_path_)
			.transform_error(print_monad_error<ReadFileError>);
		if (!file_contents.has_value()) {
			return;
		}


		// Get indicies of all chunks
		auto chunk_indices = get_chunk_indices(file_contents.value())
			.transform_error(print_monad_error<GetChunkIndicesError>);
		if (!chunk_indices.has_value()) {
			return;
		}


		// TODO: Right now, this only removes the first cICP chunk found
		// There might incorrectly be multiple.
		auto cicp_index = size_t{ SIZE_MAX };
		auto after_cicp_index = size_t{ SIZE_MAX };
		auto chunk_count = chunk_indices->size();
		for (size_t i = 0; i < chunk_count; i++) {
			auto index = (*chunk_indices)[i];
			if ((*file_contents)[index + 4] == 'c' &&
				(*file_contents)[index + 5] == 'I' &&
				(*file_contents)[index + 6] == 'C' &&
				(*file_contents)[index + 7] == 'P') {
				cicp_index = index;
				// the cICP chunk may incorrectly be the last chunk in the file,
				// so there is no chunk after it
				if (i < chunk_count - 1) {
					after_cicp_index = (*chunk_indices)[i + 1];
				}
				break;
			}
		}

		if (cicp_index == SIZE_MAX) {
			// no cICP chunk found
			print_error( Error{ { "no cICP chunk found" } } );
			return;
		}
		if (after_cicp_index == SIZE_MAX) {
			// cICP was last chunk, which isn't allowed
			print_error( Error{ { "Ill-formed file: cICP was the final chunk" } } );
			return;
		}

		// Prepare file before & after buffers for write
		auto file_contents_start = file_contents->data();
		std::vector<std::span<char>> buffers;
		buffers.push_back({ file_contents_start, file_contents_start + cicp_index });
		buffers.push_back({ file_contents_start + after_cicp_index, file_contents->size() - after_cicp_index });


		// Write the file with cICP inserted
		auto write_result = PNG_CICP_Editor::write_file(action.file_path_, buffers)
			.transform_error(print_monad_error<WriteFileError>);
		if (!write_result.has_value()) {
			return;
		}
	}

} // namespace PNG_CICP_Editor
