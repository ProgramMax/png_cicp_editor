// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "FileWriter.hpp"

#include <filesystem>
#include <fstream>
#include <utility>

namespace {

	// error messages
	static const std::string_view cannot_open_file  = "Cannot open file: ";
	static const std::string_view cannot_write_file = "Cannot write file: ";

	// utility
	static const std::string_view newline = "\n";

} // anonymous namespace

namespace CICP_Inserter {

	WriteFileError::WriteFileError(WriteFileErrorCode error_code, std::vector<std::string_view> output_messages) noexcept
		: error_code_(std::move(error_code))
		, output_messages_(std::move(output_messages))
	{
	}

	std::expected<void, WriteFileError> write_file(const std::string& file_path, std::vector<std::span<char>> buffers) noexcept {
		// TODO: Do I really need filesystem here?
		// The parameter should be a filesystem::path.
		// Here, we just use it to open the file. Which could also take a string parameter. So this gains nothing.
		const std::filesystem::path png_file_path(file_path);

		auto png_file = std::ofstream{ png_file_path, std::ios::binary };
		if (!png_file.good()) {
			return std::unexpected{ WriteFileError{ WriteFileErrorCode::CannotOpenFile, { cannot_open_file, file_path, newline } } };
		}

		for (auto& buffer : buffers) {
			png_file.write(buffer.data(), buffer.size_bytes());
			if (png_file.bad())
			{
				return std::unexpected{ WriteFileError{ WriteFileErrorCode::CannotWriteFile, { cannot_write_file, file_path, newline } } };
			}
		}

		png_file.close();
	}

} // namespace CICP_Inserter
