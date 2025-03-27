// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
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
	static constinit std::string_view cicp_chunk_in_invalid_position  = "cICP chunk being overwritten is in an invalid location";

	// utility
	static constinit std::string_view newline = "\n";


	constexpr std::array<char, 4> get_chunk_type(const std::span<char>& file_contents, size_t index) noexcept {
		return {
			file_contents[index + 4],
			file_contents[index + 5],
			file_contents[index + 6],
			file_contents[index + 7]
		};
	}

} // anonymous namespace

namespace PNG_CICP_Editor {

	std::expected<std::vector<std::span<char>>, GetInsertionIndexError> get_split_buffer_across_cicp_insertion_point(const std::span<char>& file_contents, const std::vector<size_t>& chunk_indices, bool overwrite_cicp) noexcept {
		auto plte_index = size_t{ SIZE_MAX };
		auto idat_index = size_t{ SIZE_MAX };
		auto cicp_index = size_t{ SIZE_MAX };
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
				if (!overwrite_cicp) {
					return std::unexpected{ GetInsertionIndexError{ GetInsertionIndexErrorCode::CICPChunkAlreadyExists, { cicp_chunk_already_exists, newline } } };
				}
				// TODO: Handle multiple cICP chunks
				cicp_index = index;
			}
		}

		if (plte_index == SIZE_MAX && idat_index == SIZE_MAX) {
			return std::unexpected{ GetInsertionIndexError{ GetInsertionIndexErrorCode::CouldNotFindInsertionPoint, { could_not_find_insertion_point, newline } } };
		}


		// There are several combinations of potential splits.
		// 
		// A PNG might look like {IHDR, PLTE, IDAT, IEND}.
		// In this case, we can split as {IHDR}, {PLTE, IDAT, IEND}.
		// 
		// After the cICP chunk is inserted, picking the first of (PLTE/IDAT)
		// and overwriting the cICP results in the same split:
		// {IHDR}, {PLTE, IDAT, IEND}
		//
		// However, what if the PNG looked like {IHDR, PLTE, cICP, IDAT, IEND}.
		// If we split in front of the first (PLTE/IDAT) & remove the cICP, we'll see these splits:
		// {IHDR}, {PLTE}, {IDAT, IEND}
		//
		// Alternatively, we could simply overwrite the cICP in-place, falling back to first of
		// (PLTE/IDAT) if no cICP is found. Then that last PNG's splits would look like:
		// {IHDR, PLTE}, {IDAT, IEND}
		//
		// This gives us a consistent before & after scenario.

		std::vector<std::span<char>> buffers;
		auto file_contents_start = file_contents.data();

		if (cicp_index != SIZE_MAX) {
			// A cICP chunk was found. Split before and after this chunk
			buffers.push_back({ file_contents_start, file_contents_start + cicp_index });

			// find the chunk after cICP
			auto index_after_cicp = size_t{ 0 };
			for (size_t i = 0; i < chunk_indices.size(); i++) {
				if (chunk_indices[i] == cicp_index) {
					if (i + 1 == chunk_indices.size()) {
						// there is no next chunk
						return std::unexpected{ GetInsertionIndexError{ GetInsertionIndexErrorCode::CouldNotFindInsertionPoint, { cicp_chunk_in_invalid_position, newline } } };
					}
					index_after_cicp = chunk_indices[i + 1];
					break;
				}
			}

			buffers.push_back({ file_contents_start + index_after_cicp, file_contents.size() - index_after_cicp });
		}
		else {
			// A cICP chunk was not found

			// The cICP chunk must come before the PLTE and IDAT chunks.
			// It could come anywhere before that (but after IHDR).
			// Inserting it just before the first chunk it must proceed is fine.
			auto split_index = std::min(plte_index, idat_index);
			buffers.push_back({ file_contents_start, file_contents_start + split_index });
			buffers.push_back({ file_contents_start + split_index, file_contents.size() - split_index });
		}

		return buffers;
	}

} // namespace PNG_CICP_Editor
