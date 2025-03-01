// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CICPInserter.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <limits.h>
#include <utility>

namespace {

	// error messages
	static constinit std::string_view cicp_chunk_already_exists       = "cICP chunk already exists in file.";
	static constinit std::string_view could_not_find_insertion_point  = "Could not find insertion point.";

	// utility
	static constinit std::string_view newline = "\n";


	std::array<char, 4> get_chunk_type(const std::span<char>& file_contents, size_t index) noexcept {
		return {
			file_contents[index + 4],
			file_contents[index + 5],
			file_contents[index + 6],
			file_contents[index + 7]
		};
	}

} // anonymous namespace

namespace CICP_Inserter {

	std::expected<size_t, GetInsertionIndexError> get_insertion_index(const std::span<char>& file_contents, const std::vector<size_t>& chunk_indices) noexcept {
		auto plte_index = size_t{ SIZE_MAX };
		auto idat_index = size_t{ SIZE_MAX };
		for (auto& index : chunk_indices) {
			auto chunk_type = get_chunk_type(file_contents, index);

			// Use first PLTE index if there are multiple.
			// There shouldn't be for PLTE but our goal isn't to identify invalid PNGs.
			if (plte_index == SIZE_MAX &&
				chunk_type[0] == 'P' &&
				chunk_type[1] == 'L' &&
				chunk_type[2] == 'T' &&
				chunk_type[3] == 'E') {
				plte_index = index;
			}
			// Use first IDAT index if there are multiple.
			else if (idat_index == SIZE_MAX &&
				chunk_type[0] == 'I' &&
				chunk_type[1] == 'D' &&
				chunk_type[2] == 'A' &&
				chunk_type[3] == 'T') {
				idat_index = index;
			}
			else if (chunk_type[0] == 'c' &&
			         chunk_type[1] == 'I' &&
			         chunk_type[2] == 'C' &&
			         chunk_type[3] == 'P') {
				return std::unexpected{ GetInsertionIndexError{ GetInsertionIndexErrorCode::CICPChunkAlreadyExists, { cicp_chunk_already_exists, newline } } };
			}
		}

		if (plte_index == SIZE_MAX && idat_index == SIZE_MAX) {
			return std::unexpected{ GetInsertionIndexError{ GetInsertionIndexErrorCode::CouldNotFindInsertionPoint, { could_not_find_insertion_point, newline } } };
		}

		// The cICP chunk must come before the PLTE and IDAT chunks.
		// It could come anywhere before that (but after IHDR).
		// Inserting it just before the first chunk it must proceed is fine.
		return std::min(plte_index, idat_index);
	}

} // namespace CICP_Inserter
