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

namespace CICP_Inserter {

	enum class WriteFileErrorCode {
		CannotOpenFile,
		CannotWriteFile,
	};

	class WriteFileError {
	public:

		explicit WriteFileError(WriteFileErrorCode error_code, std::vector<std::string_view> output_messages) noexcept;

		WriteFileErrorCode error_code_;
		std::vector<std::string_view> output_messages_;

	};

	std::expected<void, WriteFileError> write_file(const std::string& file_path, std::vector<std::span<char>> buffers) noexcept;

} // namespace CICP_Inserter

#endif // #ifndef CICP_INSERTER_FILEWRITER_HPP
