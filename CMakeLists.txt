cmake_minimum_required(VERSION 3.28)
project(Sonic-CPP LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(SFML
				GIT_REPOSITORY https://github.com/SFML/SFML.git
				GIT_TAG 3.0.1
				GIT_SHALLOW ON
				EXCLUDE_FROM_ALL
				SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
				GIT_REPOSITORY https://github.com/ocornut/imgui
				GIT_TAG v1.91.1
				GIT_SHALLOW ON
				EXCLUDE_FROM_ALL
				SYSTEM)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
				GIT_REPOSITORY https://github.com/SFML/imgui-sfml
				GIT_TAG v3.0
				GIT_SHALLOW ON
				EXCLUDE_FROM_ALL
				SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)

FetchContent_Declare(JUCE
	GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
	GIT_TAG 8.0.10
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	SYSTEM)
FetchContent_MakeAvailable(JUCE)

add_subdirectory(src)

target_compile_features(engine PRIVATE cxx_std_17)
target_link_libraries(engine
	PRIVATE
	SFML::Graphics
	ImGui-SFML::ImGui-SFML
	juce::juce_core
	juce::juce_audio_basics
)
