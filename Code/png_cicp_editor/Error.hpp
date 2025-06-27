// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_ERROR_HPP
#define PNG_CICP_EDITOR_ERROR_HPP

#include <expected>
#include <string_view>
#include <utility>
#include <vector>

namespace PNG_CICP_Editor {

	struct Error {
		explicit Error(std::vector<std::string_view> output_messages) noexcept;

		std::vector<std::string_view> output_messages_;
	};

	void print_error(const Error& error) noexcept;

	template<typename T>
	T print_monad_error(const T& error) noexcept {
		print_error(error);
		return error;
	}

	template<typename T>
	struct ErrorWithCode : public Error {
		explicit ErrorWithCode(T error_code, std::vector<std::string_view> output_messages) noexcept
			: Error{ std::move(output_messages) }
			, error_code_{ std::move(error_code) }
		{}

		T error_code_;

	};

} // namespace PNG_CICP_Editor

#endif // #ifndef PNG_CICP_EDITOR_ERROR_HPP
