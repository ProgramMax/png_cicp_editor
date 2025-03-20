// Copyright 2025, The png_cicp_editer Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITER_PNGPARSER_HPP
#define PNG_CICP_EDITER_PNGPARSER_HPP

#include <expected>
#include <span>
#include <string_view>
#include <vector>

#include "Error.hpp"

namespace PNG_CICP_Editer {

	enum class GetChunkIndicesErrorCode {
		NotAPNGFile,
	};
	using GetChunkIndicesError = ErrorWithCode<GetChunkIndicesErrorCode>;

	std::expected<std::vector<size_t>, GetChunkIndicesError> get_chunk_indices(const std::span<char>& file_contents) noexcept;

} // namespace PNG_CICP_Editer

#endif // #ifndef PNG_CICP_EDITER_PNGPARSER_HPP
