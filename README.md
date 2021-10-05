# 🏅 QuicPlus

[![GitHub Actions status](https://github.com/Kiddinglife/quicplus/workflows/pipeline/badge.svg)](https://github.com/Kiddinglife/quicplus/actions)

This is a minimum working template project for C++ with vcpkg and GitHub actions. This template uses the minimum amount of configuration to create a working C++ project out of the box.

**Features:**

- 💢 Uses CMake
- 💢 Each commit is automatically compiled on x64 plateforms: Windows, Linux, and OSX via GitHub actions.
- 💢 Each new tag is automatically released into [GitHub Releases](https://github.com/Kiddinglife/QuicPlus/releases) with the built binary, library, header files and the installed cmake files used by FindPackage().
- 💢 Uses vcpkg to handle dependencies and also uses cache on the GitHub actions to cache vcpkg install directory. This is done based on the vcpkg.txt file via hashing.
- 💢 Use semantic-release to automatically manage release and version bumps.
- 💢 The example project is structured as: library + example + tests
- 💢 Everything is automatic, minimal configuration, works out of the box.
- 💢 Testing via gtest and gmock
- 💢 works well with vscode and vs2022 and vs2019 (prefer vscode for daily dev).
