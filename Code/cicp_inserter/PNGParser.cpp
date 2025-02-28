// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "PNGParser.hpp"

#include <string_view>
#include <utility>

namespace {

	// error messages
	static const std::string_view not_a_png_file = "Not a valid PNG file.";

	// utility
	static const std::string_view png_header = "\x89PNG\x0d\x0a\x1a\x0a";

	uint32_t read_32_bits(const std::span<char>& file_contents, size_t index) noexcept {
		uint8_t first_byte  = file_contents[index + 0];
		uint8_t second_byte = file_contents[index + 1];
		uint8_t third_byte  = file_contents[index + 2];
		uint8_t fourth_byte = file_contents[index + 3];

		// PNGs are little endian
		// TODO: Make sure the target device is also little endian for this to work
		uint32_t combined_bytes = first_byte  << 24 |
		                          second_byte << 16 |
		                          third_byte  << 8  |
		                          fourth_byte << 0;
		return combined_bytes;
	}

} // anonymous namespace

namespace CICP_Inserter {

	GetChunkIndicesError::GetChunkIndicesError(GetChunkIndicesErrorCode error_code, std::vector<std::string_view> output_messages) noexcept
		: error_code_(std::move(error_code))
		, output_messages_(std::move(output_messages))
	{}

	std::expected<std::vector<size_t>, GetChunkIndicesError> get_chunk_indices(const std::span<char>& file_contents) noexcept {
		if (png_header.compare(file_contents.data()) != 0) {
			return std::unexpected{ GetChunkIndicesError{ GetChunkIndicesErrorCode::NotAPNGFile, { not_a_png_file } } };
		}

		std::vector<size_t> chunk_indices;
		size_t current_index = 8; // 8 comes from the the PNG header
		while (current_index < file_contents.size()) {
			chunk_indices.push_back(current_index);


			uint32_t chunk_length = read_32_bits(file_contents, current_index);
			current_index += chunk_length + 12; // 12 comes from the chunk length, type, and crc data
		}

		return chunk_indices;
	}

} // namespace CICP_Inserter
