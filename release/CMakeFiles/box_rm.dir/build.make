# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/aynur/Installed/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/aynur/Installed/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aynur/Repos/PubSubCPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aynur/Repos/PubSubCPP/release

# Include any dependencies generated for this target.
include CMakeFiles/box_rm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/box_rm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/box_rm.dir/flags.make

CMakeFiles/box_rm.dir/src/box_rm.cpp.o: CMakeFiles/box_rm.dir/flags.make
CMakeFiles/box_rm.dir/src/box_rm.cpp.o: ../src/box_rm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aynur/Repos/PubSubCPP/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/box_rm.dir/src/box_rm.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/box_rm.dir/src/box_rm.cpp.o -c /home/aynur/Repos/PubSubCPP/src/box_rm.cpp

CMakeFiles/box_rm.dir/src/box_rm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/box_rm.dir/src/box_rm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aynur/Repos/PubSubCPP/src/box_rm.cpp > CMakeFiles/box_rm.dir/src/box_rm.cpp.i

CMakeFiles/box_rm.dir/src/box_rm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/box_rm.dir/src/box_rm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aynur/Repos/PubSubCPP/src/box_rm.cpp -o CMakeFiles/box_rm.dir/src/box_rm.cpp.s

# Object files for target box_rm
box_rm_OBJECTS = \
"CMakeFiles/box_rm.dir/src/box_rm.cpp.o"

# External object files for target box_rm
box_rm_EXTERNAL_OBJECTS =

box_rm: CMakeFiles/box_rm.dir/src/box_rm.cpp.o
box_rm: CMakeFiles/box_rm.dir/build.make
box_rm: /usr/lib/x86_64-linux-gnu/librt.so
box_rm: /usr/lib/x86_64-linux-gnu/libpthread.so
box_rm: CMakeFiles/box_rm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aynur/Repos/PubSubCPP/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable box_rm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/box_rm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/box_rm.dir/build: box_rm

.PHONY : CMakeFiles/box_rm.dir/build

CMakeFiles/box_rm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/box_rm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/box_rm.dir/clean

CMakeFiles/box_rm.dir/depend:
	cd /home/aynur/Repos/PubSubCPP/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aynur/Repos/PubSubCPP /home/aynur/Repos/PubSubCPP /home/aynur/Repos/PubSubCPP/release /home/aynur/Repos/PubSubCPP/release /home/aynur/Repos/PubSubCPP/release/CMakeFiles/box_rm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/box_rm.dir/depend

