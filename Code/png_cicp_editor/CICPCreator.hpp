// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_CICPCREATOR_HPP
#define PNG_CICP_EDITOR_CICPCREATOR_HPP

#include <array>
#include <cstdint>

namespace PNG_CICP_Editor {

	std::array<char, 16> create_cicp_buffer(uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag) noexcept;

} // namespace PNG_CICP_Editor

#endif // #ifndef PNG_CICP_EDITOR_CICPCREATOR_HPP
