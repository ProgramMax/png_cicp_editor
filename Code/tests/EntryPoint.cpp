// Copyright 2025, The cicp_inserter Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "CommandLineParametersTest.hpp"
#include "FileReaderTest.hpp"
#include "PNGParserTest.hpp"

int main() {
	CICP_Inserter::RunCommandLineParametersTestSuite();
	CICP_Inserter::RunFileReaderTestSuite();
	CICP_Inserter::RunPNGParserTestSuite();

	return 0;
}