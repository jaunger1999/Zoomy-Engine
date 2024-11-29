cmake_minimum_required(VERSION 3.10)

macro(CompilerOptions name)
	set_property(TARGET ${name} PROPERTY C_STANDARD 99)
	set_property(TARGET ${name} PROPERTY C_STANDARD_REQUIRED ON)

	target_compile_options(${name} PRIVATE -g3 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef -fdiagnostics-show-option)
endmacro()

add_executable(RaylibProject main.c d_dict.c d_queue.c g_events.c hash.c m_cylinder.c m_raytriangleintersection.c m_vector.c f_objparser.c)

CompilerOptions(RaylibProject)

target_include_directories(RaylibProject PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(RaylibProject ${CMAKE_SOURCE_DIR}/lib/liblua.a)
target_link_libraries(RaylibProject ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
target_link_libraries(RaylibProject libopengl32.a)
target_link_libraries(RaylibProject libgdi32.a)
target_link_libraries(RaylibProject libwinmm.a)

# CDF Test
project(t_cdf)

add_executable(t_cdf EXCLUDE_FROM_ALL t_cdfparser.c d_dict_s.c d_dict.c d_queue.c d_string.c f_cdfparser.c g_events.c g_statemachines.c hash.c)

CompilerOptions(t_cdf)

target_include_directories(t_cdf PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(t_cdf        ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
target_link_libraries(t_cdf libwinmm.a)

# Char Args Test
project(t_charargs)

add_executable(t_charargs EXCLUDE_FROM_ALL t_charArgs.c)

CompilerOptions(t_charargs)

target_include_directories(t_charargs PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Dict Test
project(t_dict)

add_executable(t_dict EXCLUDE_FROM_ALL t_dict.c d_dict.c hash.c)

CompilerOptions(t_dict)

target_include_directories(t_dict PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Events Test
project(t_events)

add_executable(t_events EXCLUDE_FROM_ALL t_dict.c d_dict.c hash.c)

CompilerOptions(t_events)

target_include_directories(t_events PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Hash Generator
project(hashgenerator)

add_executable(hashgenerator EXCLUDE_FROM_ALL hashGenerator.c hash.c)

CompilerOptions(hashgenerator)

target_include_directories(hashgenerator PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Fluidsynth test
project(t_fluidsynth)

add_executable(t_fluidsynth EXCLUDE_FROM_ALL t_fluidsynth.c)

CompilerOptions(t_fluidsynth)

target_include_directories(t_fluidsynth PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(t_fluidsynth ${CMAKE_SOURCE_DIR}/lib/libfluidsynth.dll.a)

# Lua test
project(t_lua)

add_executable(t_lua EXCLUDE_FROM_ALL t_lua.c)

CompilerOptions(t_lua)

target_include_directories(t_lua PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(t_lua        ${CMAKE_SOURCE_DIR}/lib/liblua.a)

# Queue test
project(t_queue)

add_executable(t_queue EXCLUDE_FROM_ALL t_queue.c d_queue.c)

CompilerOptions(t_queue)

target_include_directories(t_queue PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Collision test
project(t_collision)

add_executable(t_collision EXCLUDE_FROM_ALL t_collision.c m_raytriangleintersection.c)

CompilerOptions(t_collision)

target_include_directories(t_collision PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(t_collision        ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
target_link_libraries(t_collision libwinmm.a)
