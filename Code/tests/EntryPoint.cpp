// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CICPInserterTest.hpp"
#include "CommandLineParametersTest.hpp"
#include "ErrorTest.hpp"
#include "FileReaderTest.hpp"
#include "FileWriterTest.hpp"
#include "PNGParserTest.hpp"

int main() {
	CICP_Inserter::RunCICPInserterTestSuite();
	CICP_Inserter::RunCommandLineParametersTestSuite();
	CICP_Inserter::RunErrorTestSuite();
	CICP_Inserter::RunFileReaderTestSuite();
	CICP_Inserter::RunFileWriterTestSuite();
	CICP_Inserter::RunPNGParserTestSuite();

	return 0;
}