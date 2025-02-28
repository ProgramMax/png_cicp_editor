// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CICP_INSERTER_FILEWRITER_HPP
#define CICP_INSERTER_FILEWRITER_HPP

#include <expected>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "Error.hpp"

namespace CICP_Inserter {

	enum class WriteFileErrorCode {
		CannotOpenFile,
		CannotWriteFile,
	};
	using WriteFileError = ErrorWithCode<WriteFileErrorCode>;

	std::expected<void, WriteFileError> write_file(const std::string& file_path, std::vector<std::span<char>> buffers) noexcept;

} // namespace CICP_Inserter

#endif // #ifndef CICP_INSERTER_FILEWRITER_HPP
