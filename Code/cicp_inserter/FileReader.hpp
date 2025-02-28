// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CICP_INSERTER_FILEREADER_HPP
#define CICP_INSERTER_FILEREADER_HPP

#include <expected>
#include <string>
#include <string_view>
#include <vector>

#include "Error.hpp"

namespace CICP_Inserter {

	enum class ReadFileErrorCode {
		CannotOpenFile,
		CannotReadFile,
	};
	using ReadFileError = ErrorWithCode<ReadFileErrorCode>;

	std::expected<std::vector<char>, ReadFileError> read_file(const std::string& file_path) noexcept;

} // namespace CICP_Inserter

#endif // #ifndef CICP_INSERTER_FILEREADER_HPP
