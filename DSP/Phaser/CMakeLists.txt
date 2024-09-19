# Minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

# Project name and version
project(PhaserPlugin VERSION 1.0.0)

# Include JUCE as a submodule or find it in your system
# add_subdirectory(JUCE)                    # If JUCE is a submodule
# or
# find_package(JUCE CONFIG REQUIRED)        # If JUCE is installed on your system

# Add the Phaser plugin
juce_add_plugin(PhaserPlugin
        VERSION 1.0.0                                # Plugin version
        COMPANY_NAME "YourCompanyName"               # Plugin author/company name
        IS_EFFECT TRUE                               # This is an audio effect (not a synth)
        NEEDS_MIDI_INPUT FALSE                       # No MIDI input needed
        NEEDS_MIDI_OUTPUT FALSE                      # No MIDI output needed
        IS_MIDI_EFFECT FALSE                         # Not a MIDI effect
        FORMATS AU VST3 Standalone                   # Plugin formats to build
        PRODUCT_NAME "PhaserPlugin"                  # Name of the plugin
        )

# Generate the JuceHeader.h for this target
juce_generate_juce_header(PhaserPlugin)

# Add the source files for the Phaser effect
target_sources(PhaserPlugin
        PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp
        Phaser.cpp
        oscillator.cpp
        circBuffer.cpp
        effect.cpp# Keep this for now; consider removing later if not needed
        )

# Compiler definitions (disable web browser and curl support for efficiency)
target_compile_definitions(PhaserPlugin
        PUBLIC
        JUCE_WEB_BROWSER=0  # Disable web browser component
        JUCE_USE_CURL=0     # Disable curl component
        JUCE_VST3_CAN_REPLACE_VST2=0  # VST3 should not replace VST2
        )

# Link necessary JUCE modules and other dependencies
target_link_libraries(PhaserPlugin
        PRIVATE
        juce::juce_audio_utils      # Link JUCE's audio utilities module
        juce::juce_dsp              # Link JUCE's DSP module for audio processing
        PUBLIC
        juce::juce_recommended_config_flags  # Recommended configuration flags
        juce::juce_recommended_lto_flags     # Recommended link-time optimization flags
        juce::juce_recommended_warning_flags # Recommended warning flags
        )