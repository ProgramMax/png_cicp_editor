// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_FILEREADER_HPP
#define PNG_CICP_EDITOR_FILEREADER_HPP

#include <expected>
#include <string>
#include <vector>

#include "Error.hpp"

namespace PNG_CICP_Editor {

	enum class ReadFileErrorCode {
		CannotOpenFile,
		CannotReadFile,
	};
	using ReadFileError = ErrorWithCode<ReadFileErrorCode>;

	std::expected<std::vector<char>, ReadFileError> read_file(const std::string& file_path) noexcept;

} // namespace PNG_CICP_Editor

#endif // #ifndef PNG_CICP_EDITOR_FILEREADER_HPP
