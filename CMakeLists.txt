cmake_minimum_required(VERSION 3.28)
project(Sonic-CPP LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

if(APPLE)
	enable_language(OBJCXX)
endif()

FetchContent_Declare(Nlohmann_Json
					GIT_REPOSITORY https://github.com/nlohmann/json.git
					GIT_TAG v3.12.0
					GIT_SHALLOW ON
					EXCLUDE_FROM_ALL
					SYSTEM)
FetchContent_MakeAvailable(Nlohmann_Json)

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
	PUBLIC
	SFML::Graphics
	SFML::Audio
	ImGui-SFML::ImGui-SFML
	juce::juce_core
	juce::juce_audio_basics
	nlohmann_json::nlohmann_json
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} 
	PRIVATE
	engine
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_custom_target(CopyAssets ALL
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/src/game/Assets
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/Assets
		COMMENT "Copying Assets into DEBUG bianary directory! :3"
	)
	add_custom_target(CopyAssetsJson ALL
		COMMAND ${CMAKE_COMMAND} -E copy
		${PROJECT_SOURCE_DIR}/src/game/Assets.json
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/
		COMMENT "Copying Assets.json into DEBUG bianary directory! >:D"
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_custom_target(CopyAssets ALL
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/src/game/Assets
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/Assets
		COMMENT "Copying Assets into RELEASE bianary directory! :3"
	)
	add_custom_target(CopyAssetsJson ALL
		COMMAND ${CMAKE_COMMAND} -E copy
		${PROJECT_SOURCE_DIR}/src/game/Assets.json
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/
		COMMENT "Copying Assets.json into RELEASE bianary directory! >:D"
	)
endif()

add_dependencies(${PROJECT_NAME} CopyAssets CopyAssetsJson)