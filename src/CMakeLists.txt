cmake_minimum_required(VERSION 3.10)

add_executable(RaylibProject main.c d_dict.c d_queue.c g_events.c hash.c m_cylinder.c m_raytriangleintersection.c m_vector.c f_objparser.c)

set_property(TARGET RaylibProject PROPERTY C_STANDARD 99)
set_property(TARGET RaylibProject PROPERTY C_STANDARD_REQUIRED ON)

target_compile_options(RaylibProject PRIVATE
  -g3 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef -fdiagnostics-show-option
)

target_include_directories(RaylibProject PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(RaylibProject ${CMAKE_SOURCE_DIR}/lib/liblua.a)
target_link_libraries(RaylibProject ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
target_link_libraries(RaylibProject libopengl32.a)
target_link_libraries(RaylibProject libgdi32.a)
target_link_libraries(RaylibProject libwinmm.a)