// Copyright 2025, The png_cicp_editer Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITER_FILEREADER_HPP
#define PNG_CICP_EDITER_FILEREADER_HPP

#include <expected>
#include <string>
#include <string_view>
#include <vector>

#include "Error.hpp"

namespace PNG_CICP_Editer {

	enum class ReadFileErrorCode {
		CannotOpenFile,
		CannotReadFile,
	};
	using ReadFileError = ErrorWithCode<ReadFileErrorCode>;

	std::expected<std::vector<char>, ReadFileError> read_file(const std::string& file_path) noexcept;

} // namespace PNG_CICP_Editer

#endif // #ifndef PNG_CICP_EDITER_FILEREADER_HPP
