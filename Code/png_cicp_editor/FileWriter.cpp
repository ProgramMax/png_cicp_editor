// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "FileWriter.hpp"

#include <fstream>
#include <utility>

namespace {

	// error messages
	static const std::string_view cannot_open_file  = "Cannot open file: ";
	static const std::string_view cannot_write_file = "Cannot write file: ";

	// utility
	static const std::string_view newline = "\n";

} // anonymous namespace

namespace PNG_CICP_Editor {

	std::expected<void, WriteFileError> write_file(const std::string& file_path, std::vector<std::span<char>> buffers) noexcept {
		auto png_file = std::ofstream{ file_path.c_str(), std::ios::binary };
		if (!png_file.good()) {
			return std::unexpected{ WriteFileError{ WriteFileErrorCode::CannotOpenFile, { cannot_open_file, file_path.c_str(), newline } } };
		}

		for (auto& buffer : buffers) {
			png_file.write(buffer.data(), buffer.size_bytes());
			if (png_file.bad())
			{
				return std::unexpected{ WriteFileError{ WriteFileErrorCode::CannotWriteFile, { cannot_write_file, file_path.c_str(), newline } } };
			}
		}

		png_file.close();

		return std::expected<void, WriteFileError>{};
	}

} // namespace PNG_CICP_Editor
