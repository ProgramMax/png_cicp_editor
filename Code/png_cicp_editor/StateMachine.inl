// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <utility>

namespace PNG_CICP_Editor {

	template<typename StateType, typename TransitionType>
	constexpr StateMachine<StateType, TransitionType>::StateMachine(StateType start_state, SparseArray<StateType, std::vector<TransitionType>> graph) noexcept
		: state_{std::move(start_state)}
		, graph_{std::move(graph)}
	{}

	template<typename StateType, typename TransitionType>
	template<typename... PredicateParameterTypes>
	std::expected<void, TransitionError> StateMachine<StateType, TransitionType>::Transition(PredicateParameterTypes... parameters) noexcept {
		for (const auto& node_and_edges : graph_) {
			// If current state found
			if (node_and_edges.first == state_) {
				// Loop over possible transitions, attempting to transition
				for (const auto& transition : node_and_edges.second) {
					auto predicate_and_action_result = transition.predicate_and_action_(std::forward<decltype(parameters)>(parameters)...);
					if (!predicate_and_action_result.has_value()) {
						return std::unexpected{ TransitionError{ std::move(predicate_and_action_result.error().error_code_), std::move(predicate_and_action_result.error().output_messages_) } };
					}

					if (*predicate_and_action_result) {
						state_ = transition.transition_to_;
						return std::expected<void, TransitionError>{};
					}
				}

				// Possible transitions not found
				return std::unexpected{ TransitionError{ TransitionErrorCode::NoTransitionMatchedPredicate, {} } };
			}
		}

		// State not found
		return std::unexpected{ TransitionError{ TransitionErrorCode::StateNotInStateMachine, {} } };
	}

} // namespace PNG_CICP_Editor
