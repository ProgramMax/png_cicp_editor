// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CICPCreator.hpp"

namespace {

	// TODO: This implementation is ripped directly from the example CRC implementation in the spec:
	// https://w3c.github.io/png/#samplecrc
	// Surely, there is a better way for this use case.
	unsigned long crc_table[256];
	int crc_table_computed = 0;

	void make_crc_table() noexcept {
		unsigned long c;
		int n, k;

		for (n = 0; n < 256; n++) {
			c = (unsigned long)n;
			for (k = 0; k < 8; k++) {
				if (c & 1) {
					c = 0xedb88320L ^ (c >> 1);
				}
				else {
					c = c >> 1;
				}
			}
			crc_table[n] = c;
		}
		crc_table_computed = 1;
	}

	unsigned long update_crc(unsigned long crc, char* buf, int len) noexcept {
		unsigned long c = crc;
		int n;

		if (!crc_table_computed) {
			make_crc_table();
		}

		for (n = 0; n < len; n++) {
			c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
		}

		return c;
	}

	unsigned long crc(char* buf, int len) noexcept {
		return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;
	}

} // anonymous namespace

namespace CICP_Inserter {

	std::array<char, 16> create_cicp_buffer(uint8_t color_primaries, uint8_t transfer_function, uint8_t matrix_coefficients, uint8_t video_full_range_flag) noexcept {
		std::array<char, 16> buffer;

		// length
		buffer[0] = 0;
		buffer[1] = 0;
		buffer[2] = 0;
		buffer[3] = 4;

		// chunk type
		buffer[4] = 'c';
		buffer[5] = 'I';
		buffer[6] = 'C';
		buffer[7] = 'P';

		// chunk data
		buffer[8] = color_primaries;
		buffer[9] = transfer_function;
		buffer[10] = matrix_coefficients;
		buffer[11] = video_full_range_flag;

		// crc
		unsigned long calculated_crc = crc(&buffer[4], 8);
		buffer[12] = calculated_crc >> 24;
		buffer[13] = calculated_crc >> 16;
		buffer[14] = calculated_crc >> 8;
		buffer[15] = calculated_crc >> 0;

		return buffer;
	}

} // namespace CICP_Inserter
