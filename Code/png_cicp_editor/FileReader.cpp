// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "FileReader.hpp"

#include <filesystem>
#include <fstream>
#include <utility>

namespace {

	// error messages
	static const std::string_view cannot_open_file  = "Cannot open file: ";
	static const std::string_view cannot_read_file =  "Cannot read file: ";

	// utility
	static const std::string_view newline           = "\n";

} // anonymous namespace

namespace PNG_CICP_Editor {

	std::expected<std::vector<char>, ReadFileError> read_file(const std::string& file_path) noexcept {
		// TODO: Do I really need filesystem here?
		// The parameter should be a filesystem::path.
		// Here, we just use it to open the file. Which could also take a string parameter. So this gains nothing.
		const std::filesystem::path png_file_path(file_path);

		auto png_file = std::ifstream{ png_file_path, std::ios::binary | std::ios::ate };
		if (!png_file.good()) {
			return std::unexpected{ ReadFileError{ ReadFileErrorCode::CannotOpenFile, { cannot_open_file, file_path, newline } } };
		}
		auto file_size = png_file.tellg();
		png_file.seekg(0, std::ios::beg);

		auto buffer = std::vector<char>( file_size );
		if (!png_file.read(buffer.data(), file_size))
		{
			return std::unexpected{ ReadFileError{ ReadFileErrorCode::CannotReadFile, { cannot_read_file, file_path, newline } } };
		}

		png_file.close();

		return buffer;
	}

} // namespace PNG_CICP_Editor
