// Copyright 2025, The png_cicp_editer Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITER_ERROR_HPP
#define PNG_CICP_EDITER_ERROR_HPP

#include <string_view>
#include <utility>
#include <vector>

namespace PNG_CICP_Editer {

	class Error {
	public:

		explicit Error(std::vector<std::string_view> output_messages) noexcept;

		std::vector<std::string_view> output_messages_;

	};

	void print_error(const Error& error) noexcept;

	template<typename T>
	class ErrorWithCode : public Error {
	public:

		explicit ErrorWithCode(T error_code, std::vector<std::string_view> output_messages) noexcept
			: Error(std::move(output_messages))
			, error_code_(std::move(error_code))
		{}

		T error_code_;

	};

} // namespace PNG_CICP_Editer

#endif // #ifndef PNG_CICP_EDITER_ERROR_HPP
