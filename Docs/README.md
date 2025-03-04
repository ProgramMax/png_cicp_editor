# cicp_inserter

cicp_inserter allows for easy insertion of CICP data into a PNG file.
CICP is an efficient way to specify explicit color space.
It is described in Recommendation ITU-T H.273, which can be found here:
https://www.itu.int/rec/T-REC-H.273


A typical instructions for compiling on MacOS and Linux looks like this:
1. cd into cd_inserter code directory
2. `clang++ -std=c++23 -arch arm64 -o cicp_inserter *.cpp`

A typical use case looks like this:
`cicp_inserter.exe --preset display-p3 C:\images\test.png`
This command updates the file to use Display P3.
> [!WARNING]
> This updates the existing file. Meaning any bugs or errors might clobber your file.
It does not update or alter any color values.
It simply updates the file (with all existing data unchanged) to be in a given color space.


| Preset         | Specification                                                            |
|----------------|--------------------------------------------------------------------------|
| bt.709         | Rec. ITU-R BT.709-6                                                      |
| srgb-linear    | linear-light sRGB                                                        |
| srgb           | IEC 61966-2-1 sRGB                                                       |
| bt.2020-10-bit | Rec. ITU-R BT.2020-2 (10-bit system)                                     |
| bt.2020-12-bit | Rec. ITU-R BT.2020-2 (12-bit system)                                     |
| bt.2100-pq     | Rec. ITU-R BT.2100-2 perceptual quantization (PQ) system                 |
| bt.2100-hlg    | Rec. ITU-R BT.2100-2 hybrid log-gamma (HLG) system                       |
| dci-p3         | SMPTE RP 431-2 with SMPTE ST 428-1 D-Cinema Distribution Master (DCI-P3) |
| display-p3     | Display P3                                                               |
| p3-d65-pq      | P3-D65 PQ                                                                |

You can also specify individual CICP values.
Example usage: `cicp_inserter.exe --color_primaries 1 --transfer_function 2 --matrix_coefficients 3 --video_full_range_flag 1 C:\images\test.png`

[![Build and test](https://github.com/ProgramMax/cicp_inserter/actions/workflows/build-and-test.yaml/badge.svg)](https://github.com/ProgramMax/cicp_inserter/actions/workflows/build-and-test.yaml)

If cicp_inserter is missing a feature you need, submit a [feature request](https://github.com/ProgramMax/cicp_inserter/issues/new?assignees=&labels=&template=feature_request.md&title=).

## Dependencies

cicp_inserter has no dependencies beyond the C and C++ standard libraries. However, the tests depend on [max](https://github.com/ProgramMax/max), which also has a [BSD 3-Clause license](https://github.com/ProgramMax/max/blob/master/LICENSE).
You can find some parts of max under [Dependencies/max](https://github.com/ProgramMax/cicp_inserter/blob/master/Dependencies/max).

## Engage

* **Community:** We have a welcoming community which follows the [Code of Conduct](https://github.com/ProgramMax/cicp_inserter/blob/master/Docs/code_of_conduct.md).
* **Contribute:** We accept pull requests. Take a look at some [good first tasks](https://github.com/ProgramMax/cicp_inserter/issues?q=is%3Aissue+is%3Aopen+label%3A"good+first+issue").
* **Support:** You can [report bugs](https://github.com/ProgramMax/cicp_inserter/issues/new?assignees=&labels=&template=bug_report.md&title=) and [request changes](https://github.com/ProgramMax/cicp_inserter/issues/new?assignees=&labels=&template=feature_request.md&title=) using GitHub issues.
