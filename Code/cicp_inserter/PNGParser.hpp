// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <array>
#include <expected>
#include <string_view>
#include <vector>

namespace CICP_Inserter {

	enum class GetChunkIndicesErrorCode {
		NotAPNGFile,
	};

	class GetChunkIndicesError {
	public:

		explicit GetChunkIndicesError(GetChunkIndicesErrorCode error_code, std::vector<std::string_view> output_messages) noexcept;

		GetChunkIndicesErrorCode error_code_;
		std::vector<std::string_view> output_messages_;

	};

	std::expected<std::vector<size_t>, GetChunkIndicesError> get_chunk_indices(const std::vector<char>& file_contents) noexcept;
	std::array<char, 4> get_chunk_type(const std::vector<char>& file_contents, size_t index) noexcept;

} // namespace CICP_Inserter
