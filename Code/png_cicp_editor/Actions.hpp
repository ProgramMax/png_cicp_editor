// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PNG_CICP_EDITOR_ACTIONS_HPP
#define PNG_CICP_EDITOR_ACTIONS_HPP

#include <string>
#include <variant>

#include "CICP.hpp"

namespace PNG_CICP_Editor {

	struct VersionAction {};

	struct HelpAction {};

	struct LicenseAction {};

	struct AddAction {
		explicit AddAction(CICP cicp, std::string file_path) noexcept;

		CICP cicp_;
		std::string file_path_;
	};

	struct OverwriteAction {
		explicit OverwriteAction(CICP cicp, std::string file_path) noexcept;

		CICP cicp_;
		std::string file_path_;
	};

	struct RemoveAction {
		explicit RemoveAction(std::string file_path) noexcept;

		std::string file_path_;
	};

	using Action = std::variant<VersionAction, HelpAction, LicenseAction, AddAction, OverwriteAction, RemoveAction>;

	struct ActionExecutor {

		void operator()(const PNG_CICP_Editor::VersionAction& action) const noexcept;
		void operator()(const PNG_CICP_Editor::HelpAction& action) const noexcept;
		void operator()(const PNG_CICP_Editor::LicenseAction& action) const noexcept;
		void operator()(const PNG_CICP_Editor::AddAction& action) const noexcept;
		void operator()(const PNG_CICP_Editor::OverwriteAction& action) const noexcept;
		void operator()(const PNG_CICP_Editor::RemoveAction& action) const noexcept;

	};

} // namespace PNG_CICP_Editor

#endif // #ifndef PNG_CICP_EDITOR_ACTIONS_HPP
