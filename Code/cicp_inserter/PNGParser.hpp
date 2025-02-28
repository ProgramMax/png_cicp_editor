// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CICP_INSERTER_PNGPARSER_HPP
#define CICP_INSERTER_PNGPARSER_HPP

#include <expected>
#include <span>
#include <string_view>
#include <vector>

#include "Error.hpp"

namespace CICP_Inserter {

	enum class GetChunkIndicesErrorCode {
		NotAPNGFile,
	};
	using GetChunkIndicesError = ErrorWithCode<GetChunkIndicesErrorCode>;

	std::expected<std::vector<size_t>, GetChunkIndicesError> get_chunk_indices(const std::span<char>& file_contents) noexcept;

} // namespace CICP_Inserter

#endif // #ifndef CICP_INSERTER_PNGPARSER_HPP
