# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/edoardo/cl/supl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/edoardo/cl/supl/build

# Include any dependencies generated for this target.
include CMakeFiles/supl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/supl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/supl.dir/flags.make

CMakeFiles/supl.dir/src/supl.cpp.o: CMakeFiles/supl.dir/flags.make
CMakeFiles/supl.dir/src/supl.cpp.o: ../src/supl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/edoardo/cl/supl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/supl.dir/src/supl.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/supl.dir/src/supl.cpp.o -c /home/edoardo/cl/supl/src/supl.cpp

CMakeFiles/supl.dir/src/supl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/supl.dir/src/supl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/edoardo/cl/supl/src/supl.cpp > CMakeFiles/supl.dir/src/supl.cpp.i

CMakeFiles/supl.dir/src/supl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/supl.dir/src/supl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/edoardo/cl/supl/src/supl.cpp -o CMakeFiles/supl.dir/src/supl.cpp.s

CMakeFiles/supl.dir/src/supl.cpp.o.requires:

.PHONY : CMakeFiles/supl.dir/src/supl.cpp.o.requires

CMakeFiles/supl.dir/src/supl.cpp.o.provides: CMakeFiles/supl.dir/src/supl.cpp.o.requires
	$(MAKE) -f CMakeFiles/supl.dir/build.make CMakeFiles/supl.dir/src/supl.cpp.o.provides.build
.PHONY : CMakeFiles/supl.dir/src/supl.cpp.o.provides

CMakeFiles/supl.dir/src/supl.cpp.o.provides.build: CMakeFiles/supl.dir/src/supl.cpp.o


# Object files for target supl
supl_OBJECTS = \
"CMakeFiles/supl.dir/src/supl.cpp.o"

# External object files for target supl
supl_EXTERNAL_OBJECTS =

libsupl.a: CMakeFiles/supl.dir/src/supl.cpp.o
libsupl.a: CMakeFiles/supl.dir/build.make
libsupl.a: CMakeFiles/supl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/edoardo/cl/supl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsupl.a"
	$(CMAKE_COMMAND) -P CMakeFiles/supl.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/supl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/supl.dir/build: libsupl.a

.PHONY : CMakeFiles/supl.dir/build

CMakeFiles/supl.dir/requires: CMakeFiles/supl.dir/src/supl.cpp.o.requires

.PHONY : CMakeFiles/supl.dir/requires

CMakeFiles/supl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/supl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/supl.dir/clean

CMakeFiles/supl.dir/depend:
	cd /home/edoardo/cl/supl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/edoardo/cl/supl /home/edoardo/cl/supl /home/edoardo/cl/supl/build /home/edoardo/cl/supl/build /home/edoardo/cl/supl/build/CMakeFiles/supl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/supl.dir/depend

