// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_CICP_HPP
#define PNG_CICP_EDITOR_CICP_HPP

#include <cstdint>

namespace PNG_CICP_Editor {

	struct CICP {
		explicit CICP(uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag) noexcept;

		bool operator ==(const CICP& rhs) noexcept;
		bool operator !=(const CICP& rhs) noexcept;

		uint8_t color_primaries_;
		uint8_t transfer_function_;
		uint8_t matrix_coefficients_;
		uint8_t video_full_range_flag_;
	};

} // namespace PNG_CICP_Editor

#endif // #ifndef PNG_CICP_EDITOR_CICP_HPP
