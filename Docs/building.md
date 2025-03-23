# Building png_cicp_editor

## tl;dr
Linux & Mac users:
`cd Projects/Make && make`

Windows users:
Using Visual Studio, open Projects/VisualStudio/png_cicp_editor.sln

## Details
png_cicp_editor uses C++23 features.

Inside the Projects directory are directories for make, Visual Studio, and XCode.

Each of those will build both png_cicp_editor and its tests.

Visual Studio & XCode natively provide Debug and Release builds.
Make has these added via a DEBUG flag, which defaults to false.
Override it like this:
`make DEBUG=true`

Make also allows you explicitly specify the compiler, rather than use the system default via:
`make CXX=clang++`
