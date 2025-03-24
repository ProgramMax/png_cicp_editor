// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_ACTIONS_HPP
#define PNG_CICP_EDITOR_ACTIONS_HPP

#include <string>

#include "CICP.hpp"

namespace PNG_CICP_Editor {

	enum class Actions {
		Version,
		Help,
		License,
		Add,
		Overwrite,
		Remove,
	};

	struct VersionAction {
		void operator()() const noexcept;
	};

	struct HelpAction {
		void operator()() const noexcept;
	};

	struct LicenseAction {
		void operator()() const noexcept;
	};

	struct AddAction {
		explicit AddAction(CICP cicp, std::string file_path) noexcept;

		void operator()() const noexcept;

		CICP cicp_;
		std::string file_path_;
	};

	struct OverwriteAction {
		explicit OverwriteAction(CICP cicp, std::string file_path) noexcept;

		void operator()() const noexcept;

		CICP cicp_;
		std::string file_path_;
	};

	struct RemoveAction {
		explicit RemoveAction(std::string file_path) noexcept;

		void operator()() const noexcept;

		std::string file_path_;
	};

	struct Action {

		explicit Action(VersionAction version) noexcept;
		explicit Action(HelpAction help) noexcept;
		explicit Action(LicenseAction license) noexcept;
		explicit Action(AddAction add) noexcept;
		explicit Action(OverwriteAction overwrite) noexcept;
		explicit Action(RemoveAction remove) noexcept;

		Action(const Action& rhs) noexcept;
		Action(Action&& rhs) noexcept;

		~Action() noexcept;

		Action& operator =(const Action& rhs) noexcept;
		Action& operator =(Action&& rhs) noexcept;

		Actions action_type_;
		union A {
			VersionAction version_;
			HelpAction help_;
			LicenseAction license_;
			AddAction add_;
			OverwriteAction overwrite_;
			RemoveAction remove_;

			~A() noexcept;
		} action_;
	};

} // namespace PNG_CICP_Editor

#endif // #ifndef PNG_CICP_EDITOR_ACTIONS_HPP
