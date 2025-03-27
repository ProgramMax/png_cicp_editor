// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_STATEMACHINE_HPP
#define PNG_CICP_EDITOR_STATEMACHINE_HPP

#include <concepts>
#include <expected>
#include <vector>

#include "Error.hpp"
#include "SparseArray.hpp"

namespace PNG_CICP_Editor {

	enum class TransitionErrorCode {
		StateNotInStateMachine,
		NoTransitionMatchedPredicate,

		// TODO: The state machine shouldn't know about errors from within the transitions.
		// However, designing a proper system like that is very complex.
		// Each handler would adds its error values to the grand error enum at compile time
		// and reference it.
		// I'm not even sure how to add enum values at compile time, let alone use their names.
		// Perhaps enums are the wrong mechanic, since the rest is already known at compile-time.
		// In any case, for now I'm just adding transition error codes here so they can propogate out.
		ValueOutsideRange,
	};
	using TransitionError = ErrorWithCode<TransitionErrorCode>;

	template<typename StateType, typename TransitionType>
	struct StateMachine {

		explicit constexpr StateMachine(StateType start_state, SparseArray<StateType, std::vector<TransitionType>> graph) noexcept;


		template <typename... PredicateParameterTypes>
		constexpr std::expected<void, TransitionError> Transition(PredicateParameterTypes... parameters) noexcept;

		StateType state_;
		SparseArray<StateType, std::vector<TransitionType>> graph_;

	};

} // namespace PNG_CICP_Editor

#include "StateMachine.inl"

#endif // #ifndef PNG_CICP_EDITOR_STATEMACHINE_HPP
