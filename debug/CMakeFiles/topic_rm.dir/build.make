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
CMAKE_BINARY_DIR = /home/aynur/Repos/PubSubCPP/debug

# Include any dependencies generated for this target.
include CMakeFiles/topic_rm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/topic_rm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/topic_rm.dir/flags.make

CMakeFiles/topic_rm.dir/src/topic_rm.cpp.o: CMakeFiles/topic_rm.dir/flags.make
CMakeFiles/topic_rm.dir/src/topic_rm.cpp.o: ../src/topic_rm.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aynur/Repos/PubSubCPP/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/topic_rm.dir/src/topic_rm.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/topic_rm.dir/src/topic_rm.cpp.o -c /home/aynur/Repos/PubSubCPP/src/topic_rm.cpp

CMakeFiles/topic_rm.dir/src/topic_rm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/topic_rm.dir/src/topic_rm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aynur/Repos/PubSubCPP/src/topic_rm.cpp > CMakeFiles/topic_rm.dir/src/topic_rm.cpp.i

CMakeFiles/topic_rm.dir/src/topic_rm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/topic_rm.dir/src/topic_rm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aynur/Repos/PubSubCPP/src/topic_rm.cpp -o CMakeFiles/topic_rm.dir/src/topic_rm.cpp.s

# Object files for target topic_rm
topic_rm_OBJECTS = \
"CMakeFiles/topic_rm.dir/src/topic_rm.cpp.o"

# External object files for target topic_rm
topic_rm_EXTERNAL_OBJECTS =

topic_rm: CMakeFiles/topic_rm.dir/src/topic_rm.cpp.o
topic_rm: CMakeFiles/topic_rm.dir/build.make
topic_rm: /usr/lib/x86_64-linux-gnu/librt.so
topic_rm: /usr/lib/x86_64-linux-gnu/libpthread.so
topic_rm: CMakeFiles/topic_rm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aynur/Repos/PubSubCPP/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable topic_rm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/topic_rm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/topic_rm.dir/build: topic_rm

.PHONY : CMakeFiles/topic_rm.dir/build

CMakeFiles/topic_rm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/topic_rm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/topic_rm.dir/clean

CMakeFiles/topic_rm.dir/depend:
	cd /home/aynur/Repos/PubSubCPP/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aynur/Repos/PubSubCPP /home/aynur/Repos/PubSubCPP /home/aynur/Repos/PubSubCPP/debug /home/aynur/Repos/PubSubCPP/debug /home/aynur/Repos/PubSubCPP/debug/CMakeFiles/topic_rm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/topic_rm.dir/depend

