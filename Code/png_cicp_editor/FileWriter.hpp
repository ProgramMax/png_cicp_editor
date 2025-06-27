// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_FILEWRITER_HPP
#define PNG_CICP_EDITOR_FILEWRITER_HPP

#include <expected>
#include <span>
#include <string>
#include <vector>

#include "Error.hpp"

namespace PNG_CICP_Editor {

	enum class WriteFileErrorCode {
		CannotOpenFile,
		CannotWriteFile,
	};
	using WriteFileError = ErrorWithCode<WriteFileErrorCode>;

	std::expected<void, WriteFileError> write_file(const std::string& file_path, std::vector<std::span<char>> buffers) noexcept;

} // namespace PNG_CICP_Editor

#endif // #ifndef PNG_CICP_EDITOR_FILEWRITER_HPP
