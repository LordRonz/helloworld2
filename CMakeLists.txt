cmake_minimum_required(VERSION 3.10)

# set the project name
project(HelloWorld2 VERSION 6.9)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_library(LibsModule
    BaseDeck.cpp
    Button.cpp
    Card.cpp
    CompDeck.cpp
    Deck.cpp
    EndGame.cpp
    Game.cpp
    GameState.cpp
    MainMenuState.cpp
    PauseMenu.cpp
    PlayerDeck.cpp
    State.cpp
    TrashDeck.cpp
    VectorMath.cpp
)


add_executable(HelloWorld2 main.cpp)

target_link_libraries(LibsModule -lsfml-graphics)
target_link_libraries(LibsModule -lsfml-window)
target_link_libraries(LibsModule -lsfml-system)
target_link_libraries(LibsModule -lsfml-audio)
target_link_libraries(HelloWorld2 LibsModule)

