# png_cicp_editor

PNG is an image file format.

CICP is an efficient (4 bytes), industry standard ([Recommendation ITU-T H.273](https://www.itu.int/rec/T-REC-H.273)) way to specify color space.

This tool enables CICP editing within a PNG file.

[![Build and test](https://github.com/ProgramMax/png_cicp_editor/actions/workflows/build-and-test.yaml/badge.svg)](https://github.com/ProgramMax/png_cicp_editor/actions/workflows/build-and-test.yaml)

## Usage

A typical use case looks like this:
```png_cicp_editor.exe --preset display-p3 C:\images\test.png```
This command updates the file to use Display P3.

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

You can also specify individual CICP values. For example, to label an RGB image decoded from a SECAM video:
```png_cicp_editor.exe --color_primaries 5 --transfer_function 4 --matrix_coefficients 0 --video_full_range_flag 1 secam-test.png```

 
## Engage

* **Community:** We have a welcoming community which follows the [Code of Conduct](https://github.com/ProgramMax/png_cicp_editor/blob/master/Docs/code_of_conduct.md).
* **Contribute:** We accept pull requests. Take a look at some [good first tasks](https://github.com/ProgramMax/png_cicp_editor/issues?q=is%3Aissue+is%3Aopen+label%3A"good+first+issue").
* **Support:** You can [report bugs](https://github.com/ProgramMax/png_cicp_editor/issues/new?assignees=&labels=&template=bug_report.md&title=) and [request changes](https://github.com/ProgramMax/png_cicp_editor/issues/new?assignees=&labels=&template=feature_request.md&title=) using GitHub issues.

## Building

Refer to [Building](building.md).

## Dependencies

png_cicp_editor and its tests depend on [max](https://github.com/ProgramMax/max), which also has a [BSD 3-Clause license](https://github.com/ProgramMax/max/blob/master/LICENSE).
You can find some parts of max under [Dependencies/max](https://github.com/ProgramMax/png_cicp_editor/blob/master/Dependencies/max).
