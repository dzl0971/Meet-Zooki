# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/scratch/zduan/game design/pong"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/scratch/zduan/game design/pong"

# Include any dependencies generated for this target.
include CMakeFiles/TitleScreen.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TitleScreen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TitleScreen.dir/flags.make

CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o: CMakeFiles/TitleScreen.dir/flags.make
CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o: bin/TitleScreen.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/scratch/zduan/game design/pong/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o -c "/home/scratch/zduan/game design/pong/bin/TitleScreen.cpp"

CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/scratch/zduan/game design/pong/bin/TitleScreen.cpp" > CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.i

CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/scratch/zduan/game design/pong/bin/TitleScreen.cpp" -o CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.s

CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o.requires:
.PHONY : CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o.requires

CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o.provides: CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o.requires
	$(MAKE) -f CMakeFiles/TitleScreen.dir/build.make CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o.provides.build
.PHONY : CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o.provides

CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o.provides.build: CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o

# Object files for target TitleScreen
TitleScreen_OBJECTS = \
"CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o"

# External object files for target TitleScreen
TitleScreen_EXTERNAL_OBJECTS =

TitleScreen: CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o
TitleScreen: CMakeFiles/TitleScreen.dir/build.make
TitleScreen: /home/f85/zduancs/local/lib/libsfml-graphics.so
TitleScreen: /home/f85/zduancs/local/lib/libsfml-window.so
TitleScreen: /home/f85/zduancs/local/lib/libsfml-system.so
TitleScreen: /home/f85/zduancs/local/lib/libsfml-audio.so
TitleScreen: /home/f85/zduancs/local/lib/libsfml-network.so
TitleScreen: CMakeFiles/TitleScreen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable TitleScreen"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TitleScreen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TitleScreen.dir/build: TitleScreen
.PHONY : CMakeFiles/TitleScreen.dir/build

CMakeFiles/TitleScreen.dir/requires: CMakeFiles/TitleScreen.dir/bin/TitleScreen.cpp.o.requires
.PHONY : CMakeFiles/TitleScreen.dir/requires

CMakeFiles/TitleScreen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TitleScreen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TitleScreen.dir/clean

CMakeFiles/TitleScreen.dir/depend:
	cd "/home/scratch/zduan/game design/pong" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/scratch/zduan/game design/pong" "/home/scratch/zduan/game design/pong" "/home/scratch/zduan/game design/pong" "/home/scratch/zduan/game design/pong" "/home/scratch/zduan/game design/pong/CMakeFiles/TitleScreen.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TitleScreen.dir/depend
