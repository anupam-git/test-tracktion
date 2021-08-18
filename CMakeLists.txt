cmake_minimum_required(VERSION 3.15)

project(libzl VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(tracktion_engine/modules/juce)
add_subdirectory(tracktion_engine/modules)

################################
#  JUCE MODULE STATIC LIBRARY  #
################################
add_library(juce_plugin_modules STATIC)

target_link_libraries(juce_plugin_modules
    PRIVATE
        tracktion::tracktion_engine
        tracktion::tracktion_graph
        juce::juce_core
        juce::juce_events
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

target_compile_definitions(juce_plugin_modules
    PUBLIC
        JUCE_PLUGINHOST_AU=0
        JUCE_PLUGINHOST_LADSPA=0
        JUCE_PLUGINHOST_VST3=0
        JUCE_USE_CURL=0
        JUCE_WEB_BROWSER=0
        JUCER_ENABLE_GPL_MODE=1
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_REPORT_APP_USAGE=0
        JUCE_STRICT_REFCOUNTEDPOINTER=1
        JUCE_JACK=1
        JUCE_ALSA=1
        TRACKTION_ENABLE_TIMESTRETCH_SOUNDTOUCH=1
    INTERFACE
        $<TARGET_PROPERTY:juce_plugin_modules,COMPILE_DEFINITIONS>)

target_include_directories(juce_plugin_modules
    INTERFACE
        $<TARGET_PROPERTY:juce_plugin_modules,INCLUDE_DIRECTORIES>)

set_target_properties(juce_plugin_modules PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
    VISIBILITY_INLINES_HIDDEN TRUE
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden)

####################################
#  END JUCE MODULE STATIC LIBRARY  #
####################################


#####################
#  CLI APPLICATION  #
#####################
add_executable(cli)

target_sources(cli
    PRIVATE
        cli.cpp)

target_link_libraries(cli
    PRIVATE
        juce_plugin_modules)

#####################
#  GUI APPLICATION  #
#####################
juce_add_pip(./gui.cpp)
juce_generate_juce_header(gui)

target_sources(gui PRIVATE ${SourceFiles})

target_compile_definitions(gui PRIVATE
        JUCE_PLUGINHOST_AU=0
        JUCE_PLUGINHOST_LADSPA=0
        JUCE_PLUGINHOST_VST3=0
        JUCE_USE_CURL=0
        JUCE_WEB_BROWSER=0
        JUCER_ENABLE_GPL_MODE=1
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_REPORT_APP_USAGE=0
        JUCE_STRICT_REFCOUNTEDPOINTER=1
        JUCE_JACK=1
        JUCE_ALSA=1
        TRACKTION_ENABLE_TIMESTRETCH_SOUNDTOUCH=1)
