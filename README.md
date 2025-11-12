# SchroederReverb
A lightweight cross-platform VST3 reverb plugin written in C++ with the JUCE framework

## Dependencies
- [CMake](https://cmake.org)
- pkg-config
- [JUCE dependencies](https://github.com/juce-framework/JUCE/blob/cbe7eb9c5211784e903cfd62fef18531e6a88579/docs/Linux%20Dependencies.md) (on linux)

## How to build this
```bash
git clone --recurse-submodules https://github.com/dkaisr/SchroederReverb.git
cd SchroederReverb
cmake -S . -B build
cmake --build build
```
