// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "Error.hpp"

#include <iostream>

namespace CICP_Inserter {

	Error::Error(std::vector<std::string_view> output_messages) noexcept
		: output_messages_(std::move(output_messages))
	{
	}

	void print_error(const Error& error) noexcept {
		for (auto& message : error.output_messages_) {
			std::cerr << message;
		}
	}

} // namespace CICP_Inserter
