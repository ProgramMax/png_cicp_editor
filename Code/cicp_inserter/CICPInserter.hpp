// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CICP_INSERTER_CICPINSERTER_HPP
#define CICP_INSERTER_CICPINSERTER_HPP

#include <expected>
#include <span>
#include <string_view>
#include <vector>

#include "Error.hpp"

namespace CICP_Inserter {

	enum class GetInsertionIndexErrorCode {
		CICPChunkAlreadyExists,
		CouldNotFindInsertionPoint,
	};
	using GetInsertionIndexError = ErrorWithCode<GetInsertionIndexErrorCode>;

	std::expected<std::vector<std::span<char>>, GetInsertionIndexError> get_split_buffer_across_cicp_insertion_point(const std::span<char>& file_contents, const std::vector<size_t>& chunk_indices, bool overwrite_cicp) noexcept;

} // namespace CICP_Inserter

#endif // #ifndef CICP_INSERTER_CICPINSERTER_HPP
