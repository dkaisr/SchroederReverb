# SchroederReverb
A lightweight cross-platform VST3 reverb plugin written in C++ with the JUCE framework

## My motivation
I'm rather new to digital audio, but as a tinkerer of course my first thought was: "How can I make this myself?"
Reverb seemed simple enough to understand, so I implemented this Schroeder reverberator.
This is my first real C++ project and I was also able to learn the basics of CMake and the JUCE framework along the way.

## Implementation
The Schroeder reverberator works by first feeding the signal into four parallel comb filters.
After that the result is sent through two all-pass filters in a row.

I added UI knobs in order to change Dry/Wet mix, Pre-Delay and Decay easily.

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
