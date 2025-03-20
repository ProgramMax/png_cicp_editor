// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Error.hpp"

#include <iostream>

namespace PNG_CICP_Editor {

	Error::Error(std::vector<std::string_view> output_messages) noexcept
		: output_messages_(std::move(output_messages))
	{
	}

	void print_error(const Error& error) noexcept {
		for (auto& message : error.output_messages_) {
			std::cerr << message;
		}
	}

} // namespace PNG_CICP_Editor
