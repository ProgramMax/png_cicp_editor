// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <expected>
#include <span>
#include <string_view>
#include <vector>

namespace CICP_Inserter {

	enum class GetInsertionIndexErrorCode {
		CICPChunkAlreadyExists,
		CouldNotFindInsertionPoint,
	};

	class GetInsertionIndexError {
	public:

		explicit GetInsertionIndexError(GetInsertionIndexErrorCode error_code, std::vector<std::string_view> output_messages) noexcept;

		GetInsertionIndexErrorCode error_code_;
		std::vector<std::string_view> output_messages_;

	};

	std::expected<size_t, GetInsertionIndexError> get_insertion_index(const std::span<char>& file_contents, const std::vector<size_t>& chunk_indices) noexcept;

} // namespace CICP_Inserter
