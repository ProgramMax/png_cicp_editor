// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "StateMachineTest.hpp"

#include <expected>
#include <utility>

#include <SparseArray.hpp>
#include <StateMachine.hpp>
#include <max/Testing/TestSuite.hpp>
#include <max/Testing/CoutResultPolicy.hpp>


namespace {

	struct Transition {
		constexpr explicit Transition(int transition_to) noexcept
			: transition_to_{ std::move(transition_to) }
		{}
		constexpr std::expected<bool, PNG_CICP_Editor::TransitionError> predicate_and_action_() const noexcept { return true; }
		int transition_to_;
	};

	auto test_graph = PNG_CICP_Editor::SparseArray<int, std::vector<Transition>>{
		{
			{ 1, { Transition{ 2 } } },
			{ 2, { Transition{ 1 } } }
		}
	};

} // anonymous namespace

namespace PNG_CICP_Editor {

	void RunStateMachineTestSuite()
	{
		max::Testing::CoutResultPolicy ResultPolicy;
		auto StateMachineTestSuite = max::Testing::TestSuite< max::Testing::CoutResultPolicy >{ "StateMachine test suite", std::move(ResultPolicy) };

		StateMachineTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "StateMachine ctor assigns members", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto state_machine = StateMachine<int, Transition>{ 1, test_graph };

			CurrentTest.MAX_TESTING_ASSERT(state_machine.state_ == 1);
			// TODO: Do I want to add operator ==? Maybe for test only?
			// I think not.
			// But this is observable state change so I do want to test it.
			//CurrentTest.MAX_TESTING_ASSERT(state_machine.graph_ == test_graph);
			}
		});

		StateMachineTestSuite.AddTest(max::Testing::Test< max::Testing::CoutResultPolicy >{ "Transition moves to a new state", [](max::Testing::Test< max::Testing::CoutResultPolicy >& CurrentTest, max::Testing::CoutResultPolicy const& ResultPolicy) {
			auto state_machine = StateMachine<int, Transition>{ 1, test_graph };

			auto transition_result = state_machine.Transition();

			CurrentTest.MAX_TESTING_ASSERT(transition_result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(state_machine.state_ == 2);

			transition_result = state_machine.Transition();

			CurrentTest.MAX_TESTING_ASSERT(transition_result.has_value());
			CurrentTest.MAX_TESTING_ASSERT(state_machine.state_ == 1);
			}
		});

		// TODO: Test invalid transition?

		StateMachineTestSuite.RunTests();
	}

} // namespace PNG_CICP_Editor
