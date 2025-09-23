cmake_minimum_required(VERSION 3.22)
project(SchroederReverb VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

find_package(PkgConfig REQUIRED)

add_subdirectory(JUCE)

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME "Dominik Kaiser"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE DKsr
    PLUGIN_CODE Shrv
    FORMATS VST3
    PRODUCT_NAME "Schroeder Reverb"
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

file(GLOB_RECURSE SOURCES
     src/*.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
)
