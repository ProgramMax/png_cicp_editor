# cicp_inserter

cicp_inserter allows for easy insertion of CICP data into a PNG file.

A typical use case looks like this:
`cicp_inserter.exe --preset display-p3 C:\images\test.png`

This command updates the file to use Display P3.
It does not update or alter any color values.
It simply updates the file (with all existing data unchanged) to be in a given color space.

[![Build and test](https://github.com/ProgramMax/cicp_inserter/actions/workflows/build-and-test.yaml/badge.svg)](https://github.com/ProgramMax/cicp_inserter/actions/workflows/build-and-test.yaml)

If cicp_inserter is missing a feature you need, submit a [feature request](https://github.com/ProgramMax/cicp_inserter/issues/new?assignees=&labels=&template=feature_request.md&title=).

## Dependencies

cicp_inserter has no dependencies beyond the C and C++ standard libraries. However, the tests depend on [max](https://github.com/ProgramMax/max), which also has a [BSD 3-Clause license](https://github.com/ProgramMax/max/blob/master/LICENSE).
You can find some parts of max under [Dependencies/max](https://github.com/ProgramMax/cicp_inserter/blob/master/Dependencies/max).

## Engage

* **Community:** We have a welcoming community which follows the [Code of Conduct](https://github.com/ProgramMax/cicp_inserter/blob/master/Docs/code_of_conduct.md).
* **Contribute:** We accept pull requests. Take a look at some [good first tasks](https://github.com/ProgramMax/cicp_inserter/issues?q=is%3Aissue+is%3Aopen+label%3A"good+first+issue").
* **Support:** You can [report bugs](https://github.com/ProgramMax/cicp_inserter/issues/new?assignees=&labels=&template=bug_report.md&title=) and [request changes](https://github.com/ProgramMax/cicp_inserter/issues/new?assignees=&labels=&template=feature_request.md&title=) using GitHub issues.
