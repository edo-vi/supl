# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.14.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.14.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/edo/cl/suplea

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/edo/cl/suplea/build

# Include any dependencies generated for this target.
include CMakeFiles/exampleKNN.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exampleKNN.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exampleKNN.dir/flags.make

CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.o: CMakeFiles/exampleKNN.dir/flags.make
CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.o: ../examples/exampleKNN.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/edo/cl/suplea/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.o -c /Users/edo/cl/suplea/examples/exampleKNN.cpp

CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/edo/cl/suplea/examples/exampleKNN.cpp > CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.i

CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/edo/cl/suplea/examples/exampleKNN.cpp -o CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.s

# Object files for target exampleKNN
exampleKNN_OBJECTS = \
"CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.o"

# External object files for target exampleKNN
exampleKNN_EXTERNAL_OBJECTS =

exampleKNN: CMakeFiles/exampleKNN.dir/examples/exampleKNN.cpp.o
exampleKNN: CMakeFiles/exampleKNN.dir/build.make
exampleKNN: CMakeFiles/exampleKNN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/edo/cl/suplea/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable exampleKNN"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exampleKNN.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exampleKNN.dir/build: exampleKNN

.PHONY : CMakeFiles/exampleKNN.dir/build

CMakeFiles/exampleKNN.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exampleKNN.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exampleKNN.dir/clean

CMakeFiles/exampleKNN.dir/depend:
	cd /Users/edo/cl/suplea/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/edo/cl/suplea /Users/edo/cl/suplea /Users/edo/cl/suplea/build /Users/edo/cl/suplea/build /Users/edo/cl/suplea/build/CMakeFiles/exampleKNN.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exampleKNN.dir/depend

