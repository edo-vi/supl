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

# Object files for target supl
supl_OBJECTS =

# External object files for target supl
supl_EXTERNAL_OBJECTS =

libsupl.a: CMakeFiles/supl.dir/build.make
libsupl.a: CMakeFiles/supl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/edoardo/cl/supl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library libsupl.a"
	$(CMAKE_COMMAND) -P CMakeFiles/supl.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/supl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/supl.dir/build: libsupl.a

.PHONY : CMakeFiles/supl.dir/build

CMakeFiles/supl.dir/requires:

.PHONY : CMakeFiles/supl.dir/requires

CMakeFiles/supl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/supl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/supl.dir/clean

CMakeFiles/supl.dir/depend:
	cd /home/edoardo/cl/supl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/edoardo/cl/supl /home/edoardo/cl/supl /home/edoardo/cl/supl/build /home/edoardo/cl/supl/build /home/edoardo/cl/supl/build/CMakeFiles/supl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/supl.dir/depend

