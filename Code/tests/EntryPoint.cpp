// Copyright 2025, The png_cicp_editor Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CICPCreatorTest.hpp"
#include "CICPInserterTest.hpp"
#include "CommandLineParametersTest.hpp"
#include "ErrorTest.hpp"
#include "FileReaderTest.hpp"
#include "FileWriterTest.hpp"
#include "PNGParserTest.hpp"
#include "SparseArrayTest.hpp"
#include "StateMachineTest.hpp"

int main() {
	PNG_CICP_Editor::RunCICPCreatorTestSuite();
	PNG_CICP_Editor::RunCICPInserterTestSuite();
	PNG_CICP_Editor::RunCommandLineParametersTestSuite();
	PNG_CICP_Editor::RunErrorTestSuite();
	PNG_CICP_Editor::RunFileReaderTestSuite();
	PNG_CICP_Editor::RunFileWriterTestSuite();
	PNG_CICP_Editor::RunPNGParserTestSuite();
	PNG_CICP_Editor::RunSparseArrayTestSuite();
	PNG_CICP_Editor::RunStateMachineTestSuite();

	return 0;
}
