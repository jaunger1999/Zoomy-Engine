cmake_minimum_required(VERSION 3.10)

macro(WindowsLibraries name)
	target_link_libraries(${name} libopengl32.a)
	target_link_libraries(${name} libgdi32.a)
	target_link_libraries(${name} libwinmm.a)
endmacro()

macro(CompilerOptions name)
	set_property(TARGET ${name} PROPERTY C_STANDARD 99)
	set_property(TARGET ${name} PROPERTY C_STANDARD_REQUIRED ON)

	target_compile_options(${name} PRIVATE -g3 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef -fdiagnostics-show-option)
endmacro()

add_executable(RaylibProject main.c d_dict.c d_queue.c g_events.c hash.c m_cylinder.c m_raytriangleintersection.c m_vector.c f_objparser.c)

CompilerOptions(RaylibProject)

target_include_directories(RaylibProject PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries     (RaylibProject ${CMAKE_SOURCE_DIR}/lib/liblua.a)
target_link_libraries     (RaylibProject ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
WindowsLibraries(RaylibProject)

# CDF Test
project(t_cdf)

add_executable(t_cdf EXCLUDE_FROM_ALL t_cdfparser.c d_dict_s.c d_string.c f_cdfparser.c g_statemachines.c hash.c)

CompilerOptions(t_cdf)

target_include_directories(t_cdf PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries     (t_cdf ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
WindowsLibraries(t_cdf)

# Char Args Test
project(t_charargs)

add_executable(t_charargs EXCLUDE_FROM_ALL t_charArgs.c)

CompilerOptions(t_charargs)

target_include_directories(t_charargs PUBLIC ${CMAKE_SOURCE_DIR}/include)
WindowsLibraries(t_charargs)

# Dict Test
project(t_dict)

add_executable(t_dict EXCLUDE_FROM_ALL t_dict.c d_dict.c hash.c)

CompilerOptions(t_dict)

target_include_directories(t_dict PUBLIC ${CMAKE_SOURCE_DIR}/include)
WindowsLibraries(t_dict)

# Events Test
project(t_events)

add_executable(t_events EXCLUDE_FROM_ALL t_dict.c d_dict.c hash.c)

CompilerOptions(t_events)

target_include_directories(t_events PUBLIC ${CMAKE_SOURCE_DIR}/include)
WindowsLibraries(t_events)
