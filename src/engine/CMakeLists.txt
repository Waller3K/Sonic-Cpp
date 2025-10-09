cmake_minimum_required(VERSION 3.28)

add_library(engine 
	Action.cpp
	Action.hpp
	Animation.cpp
	Animation.hpp
	Assets.cpp
	Assets.hpp
	Entity.cpp
	Entity.hpp
	Scene.cpp
	Scene.hpp
	EntityManager.cpp
	EntityManager.hpp
	GameEngine.cpp
	GameEngine.hpp
)

target_compile_features(engine PRIVATE cxx_std_17)
target_link_libraries(engine PUBLIC SFML::Graphics ImGui-SFML::ImGui-SFML)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
