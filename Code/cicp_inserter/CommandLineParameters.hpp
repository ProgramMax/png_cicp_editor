// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CICP_INSERTER_COMMANDLINEPARAMETERS_HPP
#define CICP_INSERTER_COMMANDLINEPARAMETERS_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <utility>

namespace CICP_Inserter {

	class CommandLineParameters {
	public:

		CommandLineParameters(uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag, std::string png_file_path) noexcept;

		uint8_t color_primaries_;
		uint8_t transfer_function_;
		uint8_t matrix_coefficients_;
		uint8_t video_full_range_flag_;
		std::string png_file_path_;

	};

	std::optional<CommandLineParameters> parse_command_line_parameters(int argc, char const* argv[]) noexcept;

} // namespace CICP_Inserter

#endif // #ifndef CICP_INSERTED_COMMANDLINEPARAMETERS_HPP