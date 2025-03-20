// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CICP_INSERTER_SPARSEARRAY_HPP
#define CICP_INSERTER_SPARSEARRAY_HPP

#include <optional>
#include <utility>
#include <vector>

namespace CICP_Inserter {

	template<typename IndexType, typename T>
	class SparseArray {
	public:

		explicit constexpr SparseArray(std::vector<std::pair<IndexType, T>> array) noexcept;

		constexpr const std::optional<T> operator[](IndexType index) const noexcept;

		std::vector<std::pair<IndexType, T>> array_;

		// TODO: These probably shouldn't just hand off to the array_.
		// Investigate how other k:v containers iterate.
		constexpr auto begin()  noexcept -> decltype(array_.begin());
		constexpr auto end()    noexcept -> decltype(array_.end());
		constexpr auto cbegin() noexcept -> decltype(array_.cbegin());
		constexpr auto cend()   noexcept -> decltype(array_.cend());

	};

} // namespace CICP_Inserter

#include "SparseArray.inl"

#endif // #ifndef CICP_INSERTED_SPARSEARRAY_HPP
