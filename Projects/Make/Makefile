# You can specify values like:
# make target FOO=bar
# This can be used to override CXX with different compilers. For example:
# make Build/cicp_inserter CXX=clang++


IS_64_BIT = false
ifeq ($(shell getconf LONG_BIT), 64)
	IS_64_BIT = true
else
	IS_64_BIT = false
endif

IS_X86 = false
IS_ARM = false
ifneq (,$(findstring $(shell uname -m), x86_64 amd64))
	IS_X86 = true
else ifneq (,$(findstring $(shell uname -m), aarch64 arm64))
	IS_ARM = true
endif

# Default overrides which can be provided by environment variables
ifeq (1, $(64_BIT))
	IS_64_BIT = true
endif
ifeq (1, $(32_BIT))
	IS_64_BIT = false
endif

PROGRAM = Build/cicp_inserter

CXX_SRCS = \
	../../Code/cicp_inserter/CICPCreator.cpp \
	../../Code/cicp_inserter/CICPInserter.cpp \
	../../Code/cicp_inserter/CommandLineParameters.cpp \
	../../Code/cicp_inserter/EntryPoint.cpp \
	../../Code/cicp_inserter/Error.cpp \
	../../Code/cicp_inserter/FileReader.cpp \
	../../Code/cicp_inserter/FileWriter.cpp \
	../../Code/cicp_inserter/PNGParser.cpp
CXX_OBJS = $(patsubst ../../%.cpp,Build/Objects/%.o,$(CXX_SRCS))

INCLUDE_PATHS = \
	../../Code/cicp_inserter \
	../../Dependencies/max/Code
INCLUDE_PATHS_FLAGS = $(foreach d, $(INCLUDE_PATHS), -I$d)

LIBRARY_PATHS = \
	.
LIBRARY_PATHS_FLAGS = $(foreach d, $(LIBRARY_PATHS), -L$d)


TEST_PROGRAM = Build/tests

TEST_CXX_SRCS = \
	../../Code/cicp_inserter/CICPCreator.cpp \
	../../Code/cicp_inserter/CICPInserter.cpp \
	../../Code/cicp_inserter/CommandLineParameters.cpp \
	../../Code/cicp_inserter/Error.cpp \
	../../Code/cicp_inserter/FileReader.cpp \
	../../Code/cicp_inserter/FileWriter.cpp \
	../../Code/cicp_inserter/PNGParser.cpp \
	../../Code/tests/CICPCreatorTest.cpp \
	../../Code/tests/CICPInserterTest.cpp \
	../../Code/tests/CommandLineParametersTest.cpp \
	../../Code/tests/EntryPoint.cpp \
	../../Code/tests/ErrorTest.cpp \
	../../Code/tests/FileReaderTest.cpp \
	../../Code/tests/FileWriterTest.cpp \
	../../Code/tests/PNGParserTest.cpp \
	../../Dependencies/max/Code/max/Testing/CoutResultPolicy.cpp
TEST_CXX_OBJS = $(patsubst ../../%.cpp,Build/Objects/%.o,$(TEST_CXX_SRCS))

ifeq ($(IS_64_BIT), true)
	TARGET_BIT_FLAG = -m64
else
	TARGET_BIT_FLAG = -m32
endif

CPP_FLAGS += $(INCLUDE_PATHS_FLAGS) -std=c++23 $(TARGET_BIT_FLAG)
LINKER_FLAGS += $(LIBRARY_PATH_FLAGS)

# Clang exposes an older version of concepts, which prevents
# libstdc++'s <expected> from working as expected.
# As a result, we need to use GCC's libc++ for now.
ifeq 'clang++' '$(findstring clang++,$(CXX))'
	CPP_FLAGS += -std=gnu++23 -stdlib=libc++
	LINKER_FLAGS += -stdlib=libc++
endif



all: $(PROGRAM) $(TEST_PROGRAM)

$(PROGRAM): $(CXX_OBJS)
	$(CXX) -g $(CXX_OBJS) $(LINKER_FLAGS) -o $(PROGRAM)

$(CXX_OBJS): $(CXX_SRCS)
	mkdir -p $(dir $@)
	$(CXX) -g $(CPP_FLAGS) -c $(patsubst Build/Objects/%.o,../../%.cpp,$@) -o $@

$(TEST_PROGRAM): $(TEST_CXX_OBJS)
	$(CXX) -g $(TEST_CXX_OBJS) $(LINKER_FLAGS) -o $(TEST_PROGRAM)

$(TEST_CXX_OBJS): $(TEST_CXX_SRCS)
	mkdir -p $(dir $@)
	$(CXX) -g $(CPP_FLAGS) -c $(patsubst Build/Objects/%.o,../../%.cpp,$@) -o $@

.PHONY: clean
distclean: clean
clean:
	for file in $(PROGRAM) $(CXX_OBJS) $(TEST_PROGRAM) $(TEST_CXX_OBJS) ; do \
		rm $${file} ; \
	done
