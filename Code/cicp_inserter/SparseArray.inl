// Copyright 2025, The png_cicp_editer Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <utility>

namespace PNG_CICP_Editer {

	template<typename IndexType, typename T>
	constexpr SparseArray<IndexType, T>::SparseArray(std::vector<std::pair<IndexType, T>> array) noexcept
		: array_(std::move(array))
	{}

	template<typename IndexType, typename T>
	constexpr const std::optional<T> SparseArray<IndexType, T>::operator[](IndexType index) const noexcept {
		for (const auto& current_pair : array_) {
			if (current_pair.first == index) {
				return current_pair.second;
			}
		}

		// No matching index
		return std::nullopt;
	}

	template<typename IndexType, typename T>
	constexpr auto SparseArray<IndexType, T>::begin() noexcept -> decltype(array_.begin()) {
		return array_.begin();
	}

	template<typename IndexType, typename T>
	constexpr auto SparseArray<IndexType, T>::end() noexcept -> decltype(array_.end()) {
		return array_.end();
	}

	template<typename IndexType, typename T>
	constexpr auto SparseArray<IndexType, T>::cbegin() noexcept -> decltype(array_.cbegin()) {
		return array_.cbegin();
	}

	template<typename IndexType, typename T>
	constexpr auto SparseArray<IndexType, T>::cend() noexcept -> decltype(array_.cend()) {
		return array_.cend();
	}

} // namespace PNG_CICP_Editer
