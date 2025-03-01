// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CICP_INSERTER_CICPCREATOR_HPP
#define CICP_INSERTER_CICPCREATOR_HPP

#include <array>

namespace CICP_Inserter {

	std::array<char, 16> create_cicp_buffer(uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag) noexcept;

} // namespace CICP_Inserter

#endif // #ifndef CICP_INSERTER_CICPCREATOR_HPP
