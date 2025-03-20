// Copyright 2025, The png_cicp_editer Contributors. All rights reserved.
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
	PNG_CICP_Editer::RunCICPCreatorTestSuite();
	PNG_CICP_Editer::RunCICPInserterTestSuite();
	PNG_CICP_Editer::RunCommandLineParametersTestSuite();
	PNG_CICP_Editer::RunErrorTestSuite();
	PNG_CICP_Editer::RunFileReaderTestSuite();
	PNG_CICP_Editer::RunFileWriterTestSuite();
	PNG_CICP_Editer::RunPNGParserTestSuite();
	PNG_CICP_Editer::RunSparseArrayTestSuite();
	PNG_CICP_Editer::RunStateMachineTestSuite();

	return 0;
}
