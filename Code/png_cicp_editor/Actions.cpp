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

namespace PNG_CICP_Editor {

	void VersionAction::operator()() const noexcept {
		std::cout << "png_cicp_editor version 2.2" << std::endl;
	}

	void HelpAction::operator()() const noexcept {
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
		auto version_action = VersionAction{};
		version_action();

		std::cout <<
			R"(This program enabled CICP editing within a PNG file.
CICP is an efficient way to specify color space.
It is standardized in ITU-T H.273, which can be found here:
https://www.itu.int/rec/T-REC-H.273

Example usage: )" << program_name << R"( add --preset display-p3 )" << file_path << R"(

Presets:
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
Example usage: )" << program_name << R"( --color_primaries 5 --transfer_function 4 --matrix_coefficients 0 --video_full_range_flag 1 )" << file_path << R"(

These can be mixed to override defaults. Values specified later override prior values.
Example usage: )" << program_name << R"( --preset display-p3 --video_full_range_flag 0 )" << file_path << R"(

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

	void LicenseAction::operator()() const noexcept {
		std::cout << R"(Copyright 2025, The png_cicp_editor Contributors
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
    * Neither the name of png_cicp_editor nor the names of its
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


png_cicp_editor depends on max:

Copyright 2015, The max Contributors
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
    * Neither the name of max nor the names of its contributors may be
used to endorse or promote products derived from this software without
specific prior written permission.

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
)" << std::endl;
	}

	AddAction::AddAction(CICP cicp, std::string file_path) noexcept
		: cicp_(std::move(cicp))
		, file_path_(std::move(file_path))
	{}

	void AddAction::operator()() const noexcept {
		// TODO: Return error values
		// Read the file
		auto file_contents = read_file(file_path_);
		if (!file_contents.has_value()) {
			print_error(file_contents.error());
			//return 1;
			return;
		}


		// Get indicies of all chunks
		auto chunk_indices = get_chunk_indices(file_contents.value());
		if (!chunk_indices.has_value()) {
			print_error(chunk_indices.error());
			//return 1;
			return;
		}


		// Find insertion index for cICP chunk
		auto split_buffer = get_split_buffer_across_cicp_insertion_point(file_contents.value(), chunk_indices.value(), /*overwrite_cicp*/ false);
		if (!split_buffer.has_value()) {
			print_error(split_buffer.error());
			//return 1;
			return;
		}


		// Prepare cICP buffer to write
		auto cicp_buffer = create_cicp_buffer(cicp_.color_primaries_, cicp_.transfer_function_, cicp_.matrix_coefficients_, cicp_.video_full_range_flag_);


		// Prepare file before & after buffers for write
		std::vector<std::span<char>> buffers;
		buffers.push_back({ split_buffer.value()[0] });
		buffers.push_back({ cicp_buffer });
		buffers.push_back({ split_buffer.value()[1] });


		// Write the file with cICP inserted
		auto write_result = PNG_CICP_Editor::write_file(file_path_, buffers);
		if (!write_result.has_value()) {
			print_error(write_result.error());
			//return 1;
			return;
		}
	}

	OverwriteAction::OverwriteAction(CICP cicp, std::string file_path) noexcept
		: cicp_(std::move(cicp))
		, file_path_(std::move(file_path))
	{}

	void OverwriteAction::operator()() const noexcept {
		// TODO: Return error values
		// Read the file
		auto file_contents = read_file(file_path_);
		if (!file_contents.has_value()) {
			print_error(file_contents.error());
			//return 1;
			return;
		}


		// Get indicies of all chunks
		auto chunk_indices = get_chunk_indices(file_contents.value());
		if (!chunk_indices.has_value()) {
			print_error(chunk_indices.error());
			//return 1;
			return;
		}


		// Find insertion index for cICP chunk
		auto split_buffer = get_split_buffer_across_cicp_insertion_point(file_contents.value(), chunk_indices.value(), /*overwrite_cicp*/ true);
		if (!split_buffer.has_value()) {
			print_error(split_buffer.error());
			//return 1;
			return;
		}


		// Prepare cICP buffer to write
		auto cicp_buffer = create_cicp_buffer(cicp_.color_primaries_, cicp_.transfer_function_, cicp_.matrix_coefficients_, cicp_.video_full_range_flag_);


		// Prepare file before & after buffers for write
		std::vector<std::span<char>> buffers;
		buffers.push_back({ split_buffer.value()[0] });
		buffers.push_back({ cicp_buffer });
		buffers.push_back({ split_buffer.value()[1] });


		// Write the file with cICP inserted
		auto write_result = PNG_CICP_Editor::write_file(file_path_, buffers);
		if (!write_result.has_value()) {
			print_error(write_result.error());
			//return 1;
			return;
		}
	}

	RemoveAction::RemoveAction(std::string file_path) noexcept
		: file_path_(std::move(file_path))
	{}

	void RemoveAction::operator()() const noexcept {
		std::cerr << "Remove not yet implemented" << std::endl;
	}

	Action::Action(VersionAction version) noexcept
		: action_type_(Actions::Version)
		, action_{.version_ = std::move(version)}
	{
		action_.version_ = std::move(version);
	}

	Action::Action(HelpAction help) noexcept
		: action_type_(Actions::Help)
		, action_{.help_ = std::move(help)}
	{}

	Action::Action(LicenseAction license) noexcept
		: action_type_(Actions::License)
		, action_{.license_ = std::move(license)}
	{}

	Action::Action(AddAction add) noexcept
		: action_type_(Actions::Add)
		, action_{.add_ = std::move(add)}
	{}

	Action::Action(OverwriteAction overwrite) noexcept
		: action_type_(Actions::Overwrite)
		, action_{.overwrite_ = std::move(overwrite)}
	{}

	Action::Action(RemoveAction remove) noexcept
		: action_type_(Actions::Remove)
		, action_{.remove_ = std::move(remove)}
	{}

	Action::Action(const Action& rhs) noexcept
		: action_type_(rhs.action_type_)
		, action_{.version_{}}
	{
		switch (action_type_) {
		case Actions::Version:
			action_.version_ = rhs.action_.version_;
			break;
		case Actions::Help:
			action_.help_ = rhs.action_.help_;
			break;
		case Actions::License:
			action_.license_ = rhs.action_.license_;
			break;
		case Actions::Add:
			action_.add_ = rhs.action_.add_;
			break;
		case Actions::Overwrite:
			action_.overwrite_ = rhs.action_.overwrite_;
			break;
		case Actions::Remove:
			action_.remove_ = rhs.action_.remove_;
			break;
		}
	}

	Action::Action(Action&& rhs) noexcept
		: action_type_(std::move(rhs.action_type_))
		, action_{.version_{}}
	{
		switch (action_type_) {
		case Actions::Version:
			action_.version_ = std::move(rhs.action_.version_);
			break;
		case Actions::Help:
			action_.help_ = std::move(rhs.action_.help_);
			break;
		case Actions::License:
			action_.license_ = std::move(rhs.action_.license_);
			break;
		case Actions::Add:
			action_.add_ = std::move(rhs.action_.add_);
			break;
		case Actions::Overwrite:
			action_.overwrite_ = std::move(rhs.action_.overwrite_);
			break;
		case Actions::Remove:
			action_.remove_ = std::move(rhs.action_.remove_);
			break;
		}
	}

} // namespace PNG_CICP_Editor
