# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\jaung\source\repos\Raylib Project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\jaung\source\repos\Raylib Project\bin"

# Include any dependencies generated for this target.
include src/CMakeFiles/RaylibProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/RaylibProject.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/RaylibProject.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/RaylibProject.dir/flags.make

src/CMakeFiles/RaylibProject.dir/codegen:
.PHONY : src/CMakeFiles/RaylibProject.dir/codegen

src/CMakeFiles/RaylibProject.dir/main.c.obj: src/CMakeFiles/RaylibProject.dir/flags.make
src/CMakeFiles/RaylibProject.dir/main.c.obj: src/CMakeFiles/RaylibProject.dir/includes_C.rsp
src/CMakeFiles/RaylibProject.dir/main.c.obj: C:/Users/jaung/source/repos/Raylib\ Project/src/main.c
src/CMakeFiles/RaylibProject.dir/main.c.obj: src/CMakeFiles/RaylibProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/RaylibProject.dir/main.c.obj"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/RaylibProject.dir/main.c.obj -MF CMakeFiles\RaylibProject.dir\main.c.obj.d -o CMakeFiles\RaylibProject.dir\main.c.obj -c "C:\Users\jaung\source\repos\Raylib Project\src\main.c"

src/CMakeFiles/RaylibProject.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RaylibProject.dir/main.c.i"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\jaung\source\repos\Raylib Project\src\main.c" > CMakeFiles\RaylibProject.dir\main.c.i

src/CMakeFiles/RaylibProject.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RaylibProject.dir/main.c.s"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\jaung\source\repos\Raylib Project\src\main.c" -o CMakeFiles\RaylibProject.dir\main.c.s

src/CMakeFiles/RaylibProject.dir/d_dict.c.obj: src/CMakeFiles/RaylibProject.dir/flags.make
src/CMakeFiles/RaylibProject.dir/d_dict.c.obj: src/CMakeFiles/RaylibProject.dir/includes_C.rsp
src/CMakeFiles/RaylibProject.dir/d_dict.c.obj: C:/Users/jaung/source/repos/Raylib\ Project/src/d_dict.c
src/CMakeFiles/RaylibProject.dir/d_dict.c.obj: src/CMakeFiles/RaylibProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/RaylibProject.dir/d_dict.c.obj"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/RaylibProject.dir/d_dict.c.obj -MF CMakeFiles\RaylibProject.dir\d_dict.c.obj.d -o CMakeFiles\RaylibProject.dir\d_dict.c.obj -c "C:\Users\jaung\source\repos\Raylib Project\src\d_dict.c"

src/CMakeFiles/RaylibProject.dir/d_dict.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RaylibProject.dir/d_dict.c.i"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\jaung\source\repos\Raylib Project\src\d_dict.c" > CMakeFiles\RaylibProject.dir\d_dict.c.i

src/CMakeFiles/RaylibProject.dir/d_dict.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RaylibProject.dir/d_dict.c.s"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\jaung\source\repos\Raylib Project\src\d_dict.c" -o CMakeFiles\RaylibProject.dir\d_dict.c.s

src/CMakeFiles/RaylibProject.dir/d_queue.c.obj: src/CMakeFiles/RaylibProject.dir/flags.make
src/CMakeFiles/RaylibProject.dir/d_queue.c.obj: src/CMakeFiles/RaylibProject.dir/includes_C.rsp
src/CMakeFiles/RaylibProject.dir/d_queue.c.obj: C:/Users/jaung/source/repos/Raylib\ Project/src/d_queue.c
src/CMakeFiles/RaylibProject.dir/d_queue.c.obj: src/CMakeFiles/RaylibProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/RaylibProject.dir/d_queue.c.obj"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/RaylibProject.dir/d_queue.c.obj -MF CMakeFiles\RaylibProject.dir\d_queue.c.obj.d -o CMakeFiles\RaylibProject.dir\d_queue.c.obj -c "C:\Users\jaung\source\repos\Raylib Project\src\d_queue.c"

src/CMakeFiles/RaylibProject.dir/d_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RaylibProject.dir/d_queue.c.i"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\jaung\source\repos\Raylib Project\src\d_queue.c" > CMakeFiles\RaylibProject.dir\d_queue.c.i

src/CMakeFiles/RaylibProject.dir/d_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RaylibProject.dir/d_queue.c.s"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\jaung\source\repos\Raylib Project\src\d_queue.c" -o CMakeFiles\RaylibProject.dir\d_queue.c.s

src/CMakeFiles/RaylibProject.dir/g_events.c.obj: src/CMakeFiles/RaylibProject.dir/flags.make
src/CMakeFiles/RaylibProject.dir/g_events.c.obj: src/CMakeFiles/RaylibProject.dir/includes_C.rsp
src/CMakeFiles/RaylibProject.dir/g_events.c.obj: C:/Users/jaung/source/repos/Raylib\ Project/src/g_events.c
src/CMakeFiles/RaylibProject.dir/g_events.c.obj: src/CMakeFiles/RaylibProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/RaylibProject.dir/g_events.c.obj"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/RaylibProject.dir/g_events.c.obj -MF CMakeFiles\RaylibProject.dir\g_events.c.obj.d -o CMakeFiles\RaylibProject.dir\g_events.c.obj -c "C:\Users\jaung\source\repos\Raylib Project\src\g_events.c"

src/CMakeFiles/RaylibProject.dir/g_events.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RaylibProject.dir/g_events.c.i"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\jaung\source\repos\Raylib Project\src\g_events.c" > CMakeFiles\RaylibProject.dir\g_events.c.i

src/CMakeFiles/RaylibProject.dir/g_events.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RaylibProject.dir/g_events.c.s"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\jaung\source\repos\Raylib Project\src\g_events.c" -o CMakeFiles\RaylibProject.dir\g_events.c.s

src/CMakeFiles/RaylibProject.dir/hash.c.obj: src/CMakeFiles/RaylibProject.dir/flags.make
src/CMakeFiles/RaylibProject.dir/hash.c.obj: src/CMakeFiles/RaylibProject.dir/includes_C.rsp
src/CMakeFiles/RaylibProject.dir/hash.c.obj: C:/Users/jaung/source/repos/Raylib\ Project/src/hash.c
src/CMakeFiles/RaylibProject.dir/hash.c.obj: src/CMakeFiles/RaylibProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/RaylibProject.dir/hash.c.obj"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/RaylibProject.dir/hash.c.obj -MF CMakeFiles\RaylibProject.dir\hash.c.obj.d -o CMakeFiles\RaylibProject.dir\hash.c.obj -c "C:\Users\jaung\source\repos\Raylib Project\src\hash.c"

src/CMakeFiles/RaylibProject.dir/hash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RaylibProject.dir/hash.c.i"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\jaung\source\repos\Raylib Project\src\hash.c" > CMakeFiles\RaylibProject.dir\hash.c.i

src/CMakeFiles/RaylibProject.dir/hash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RaylibProject.dir/hash.c.s"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\jaung\source\repos\Raylib Project\src\hash.c" -o CMakeFiles\RaylibProject.dir\hash.c.s

src/CMakeFiles/RaylibProject.dir/m_cylinder.c.obj: src/CMakeFiles/RaylibProject.dir/flags.make
src/CMakeFiles/RaylibProject.dir/m_cylinder.c.obj: src/CMakeFiles/RaylibProject.dir/includes_C.rsp
src/CMakeFiles/RaylibProject.dir/m_cylinder.c.obj: C:/Users/jaung/source/repos/Raylib\ Project/src/m_cylinder.c
src/CMakeFiles/RaylibProject.dir/m_cylinder.c.obj: src/CMakeFiles/RaylibProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/CMakeFiles/RaylibProject.dir/m_cylinder.c.obj"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/RaylibProject.dir/m_cylinder.c.obj -MF CMakeFiles\RaylibProject.dir\m_cylinder.c.obj.d -o CMakeFiles\RaylibProject.dir\m_cylinder.c.obj -c "C:\Users\jaung\source\repos\Raylib Project\src\m_cylinder.c"

src/CMakeFiles/RaylibProject.dir/m_cylinder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RaylibProject.dir/m_cylinder.c.i"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\jaung\source\repos\Raylib Project\src\m_cylinder.c" > CMakeFiles\RaylibProject.dir\m_cylinder.c.i

src/CMakeFiles/RaylibProject.dir/m_cylinder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RaylibProject.dir/m_cylinder.c.s"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\jaung\source\repos\Raylib Project\src\m_cylinder.c" -o CMakeFiles\RaylibProject.dir\m_cylinder.c.s

src/CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.obj: src/CMakeFiles/RaylibProject.dir/flags.make
src/CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.obj: src/CMakeFiles/RaylibProject.dir/includes_C.rsp
src/CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.obj: C:/Users/jaung/source/repos/Raylib\ Project/src/m_raytriangleintersection.c
src/CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.obj: src/CMakeFiles/RaylibProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.obj"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.obj -MF CMakeFiles\RaylibProject.dir\m_raytriangleintersection.c.obj.d -o CMakeFiles\RaylibProject.dir\m_raytriangleintersection.c.obj -c "C:\Users\jaung\source\repos\Raylib Project\src\m_raytriangleintersection.c"

src/CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.i"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\jaung\source\repos\Raylib Project\src\m_raytriangleintersection.c" > CMakeFiles\RaylibProject.dir\m_raytriangleintersection.c.i

src/CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.s"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\jaung\source\repos\Raylib Project\src\m_raytriangleintersection.c" -o CMakeFiles\RaylibProject.dir\m_raytriangleintersection.c.s

src/CMakeFiles/RaylibProject.dir/m_vector.c.obj: src/CMakeFiles/RaylibProject.dir/flags.make
src/CMakeFiles/RaylibProject.dir/m_vector.c.obj: src/CMakeFiles/RaylibProject.dir/includes_C.rsp
src/CMakeFiles/RaylibProject.dir/m_vector.c.obj: C:/Users/jaung/source/repos/Raylib\ Project/src/m_vector.c
src/CMakeFiles/RaylibProject.dir/m_vector.c.obj: src/CMakeFiles/RaylibProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/CMakeFiles/RaylibProject.dir/m_vector.c.obj"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/RaylibProject.dir/m_vector.c.obj -MF CMakeFiles\RaylibProject.dir\m_vector.c.obj.d -o CMakeFiles\RaylibProject.dir\m_vector.c.obj -c "C:\Users\jaung\source\repos\Raylib Project\src\m_vector.c"

src/CMakeFiles/RaylibProject.dir/m_vector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RaylibProject.dir/m_vector.c.i"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\jaung\source\repos\Raylib Project\src\m_vector.c" > CMakeFiles\RaylibProject.dir\m_vector.c.i

src/CMakeFiles/RaylibProject.dir/m_vector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RaylibProject.dir/m_vector.c.s"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\jaung\source\repos\Raylib Project\src\m_vector.c" -o CMakeFiles\RaylibProject.dir\m_vector.c.s

src/CMakeFiles/RaylibProject.dir/f_objparser.c.obj: src/CMakeFiles/RaylibProject.dir/flags.make
src/CMakeFiles/RaylibProject.dir/f_objparser.c.obj: src/CMakeFiles/RaylibProject.dir/includes_C.rsp
src/CMakeFiles/RaylibProject.dir/f_objparser.c.obj: C:/Users/jaung/source/repos/Raylib\ Project/src/f_objparser.c
src/CMakeFiles/RaylibProject.dir/f_objparser.c.obj: src/CMakeFiles/RaylibProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building C object src/CMakeFiles/RaylibProject.dir/f_objparser.c.obj"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/RaylibProject.dir/f_objparser.c.obj -MF CMakeFiles\RaylibProject.dir\f_objparser.c.obj.d -o CMakeFiles\RaylibProject.dir\f_objparser.c.obj -c "C:\Users\jaung\source\repos\Raylib Project\src\f_objparser.c"

src/CMakeFiles/RaylibProject.dir/f_objparser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/RaylibProject.dir/f_objparser.c.i"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\jaung\source\repos\Raylib Project\src\f_objparser.c" > CMakeFiles\RaylibProject.dir\f_objparser.c.i

src/CMakeFiles/RaylibProject.dir/f_objparser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/RaylibProject.dir/f_objparser.c.s"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\jaung\source\repos\Raylib Project\src\f_objparser.c" -o CMakeFiles\RaylibProject.dir\f_objparser.c.s

# Object files for target RaylibProject
RaylibProject_OBJECTS = \
"CMakeFiles/RaylibProject.dir/main.c.obj" \
"CMakeFiles/RaylibProject.dir/d_dict.c.obj" \
"CMakeFiles/RaylibProject.dir/d_queue.c.obj" \
"CMakeFiles/RaylibProject.dir/g_events.c.obj" \
"CMakeFiles/RaylibProject.dir/hash.c.obj" \
"CMakeFiles/RaylibProject.dir/m_cylinder.c.obj" \
"CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.obj" \
"CMakeFiles/RaylibProject.dir/m_vector.c.obj" \
"CMakeFiles/RaylibProject.dir/f_objparser.c.obj"

# External object files for target RaylibProject
RaylibProject_EXTERNAL_OBJECTS =

RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/main.c.obj
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/d_dict.c.obj
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/d_queue.c.obj
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/g_events.c.obj
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/hash.c.obj
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/m_cylinder.c.obj
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/m_raytriangleintersection.c.obj
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/m_vector.c.obj
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/f_objparser.c.obj
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/build.make
RaylibProject.exe: C:/Users/jaung/source/repos/Raylib\ Project/lib/liblua.a
RaylibProject.exe: C:/Users/jaung/source/repos/Raylib\ Project/lib/libraylib.a
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/linkLibs.rsp
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/objects1.rsp
RaylibProject.exe: src/CMakeFiles/RaylibProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\jaung\source\repos\Raylib Project\bin\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Linking C executable ..\RaylibProject.exe"
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RaylibProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/RaylibProject.dir/build: RaylibProject.exe
.PHONY : src/CMakeFiles/RaylibProject.dir/build

src/CMakeFiles/RaylibProject.dir/clean:
	cd /d C:\Users\jaung\source\repos\RAYLIB~1\bin\src && $(CMAKE_COMMAND) -P CMakeFiles\RaylibProject.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/RaylibProject.dir/clean

src/CMakeFiles/RaylibProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\jaung\source\repos\Raylib Project" "C:\Users\jaung\source\repos\Raylib Project\src" "C:\Users\jaung\source\repos\Raylib Project\bin" "C:\Users\jaung\source\repos\Raylib Project\bin\src" "C:\Users\jaung\source\repos\Raylib Project\bin\src\CMakeFiles\RaylibProject.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : src/CMakeFiles/RaylibProject.dir/depend

