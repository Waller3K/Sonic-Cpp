cmake_minimum_required(VERSION 3.28)

add_executable(${PROJECT_NAME}
    main.cpp
    MenuScene.cpp
    MenuScene.hpp
    GameScene.cpp
    GameScene.hpp
    IDs.hpp
)




target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE engine)