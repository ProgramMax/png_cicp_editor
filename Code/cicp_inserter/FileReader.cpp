// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "FileReader.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

namespace CICP_Inserter {

	std::optional<std::string> read_file(const std::string& file_path) noexcept {
		// TODO: Do I really need filesystem here?
		// The parameter should be a filesystem::path.
		// Here, we just use it to open the file. Which could also take a string parameter. So this gains nothing.
		const std::filesystem::path png_file_path(file_path);

		std::ifstream png_file(png_file_path);
		if (!png_file.good()) {
			std::cerr << "Could not open file: " << png_file_path << std::endl;
			return std::nullopt;
		}

		return std::string(std::istreambuf_iterator<char>(png_file), std::istreambuf_iterator<char>());
	}

} // namespace CICP_Inserter
