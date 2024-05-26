cmake_minimum_required (VERSION 3.28)
project (COS10009_customProgram C)

set (CMAKE_C_STANDARD 11)

include_directories ("includes")

add_executable (COS10009_customProgram
				main.c
				game.c
				gameHUD.c
				screens.c
				loadGame.c)

target_link_libraries (${PROJECT_NAME} raylib)