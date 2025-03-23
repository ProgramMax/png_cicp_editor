// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CICP.hpp"

#include <utility>

namespace PNG_CICP_Editor {

	CICP::CICP(uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag) noexcept
		: color_primaries_(std::move(color_primaries))
		, transfer_function_(std::move(transfer_function))
		, matrix_coefficients_(std::move(matrix_coefficients))
		, video_full_range_flag_(std::move(video_full_range_flag))
	{}

	bool CICP::operator ==(const CICP& rhs) noexcept {
		return color_primaries_       == rhs.color_primaries_ &&
		       transfer_function_     == rhs.transfer_function_ &&
		       matrix_coefficients_   == rhs.matrix_coefficients_ &&
		       video_full_range_flag_ == rhs.video_full_range_flag_;
	}

	bool CICP::operator !=(const CICP& rhs) noexcept {
		return ! operator==(rhs);
	}


} // namespace PNG_CICP_Editor
