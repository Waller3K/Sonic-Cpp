cmake_minimum_required(VERSION 3.28)

add_executable(
	engine 
	Action.cpp
	Action.hpp
	Entity.cpp
	Entity.hpp
	Scene.cpp
	Scene.hpp
	main.cpp
	GameEngine.hpp
	GameEngine.cpp
)

target_compile_features(engine PRIVATE cxx_std_17)
target_link_libraries(engine PRIVATE SFML::Graphics ImGui-SFML::ImGui-SFML)
