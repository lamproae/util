# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/pi/c/practise/heap/lib/libutil

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/c/practise/heap/lib/libutil/build

# Include any dependencies generated for this target.
include src/CMakeFiles/util_static.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/util_static.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/util_static.dir/flags.make

src/CMakeFiles/util_static.dir/random.c.o: src/CMakeFiles/util_static.dir/flags.make
src/CMakeFiles/util_static.dir/random.c.o: ../src/random.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/pi/c/practise/heap/lib/libutil/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/CMakeFiles/util_static.dir/random.c.o"
	cd /home/pi/c/practise/heap/lib/libutil/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/util_static.dir/random.c.o   -c /home/pi/c/practise/heap/lib/libutil/src/random.c

src/CMakeFiles/util_static.dir/random.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/util_static.dir/random.c.i"
	cd /home/pi/c/practise/heap/lib/libutil/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/pi/c/practise/heap/lib/libutil/src/random.c > CMakeFiles/util_static.dir/random.c.i

src/CMakeFiles/util_static.dir/random.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/util_static.dir/random.c.s"
	cd /home/pi/c/practise/heap/lib/libutil/build/src && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/pi/c/practise/heap/lib/libutil/src/random.c -o CMakeFiles/util_static.dir/random.c.s

src/CMakeFiles/util_static.dir/random.c.o.requires:
.PHONY : src/CMakeFiles/util_static.dir/random.c.o.requires

src/CMakeFiles/util_static.dir/random.c.o.provides: src/CMakeFiles/util_static.dir/random.c.o.requires
	$(MAKE) -f src/CMakeFiles/util_static.dir/build.make src/CMakeFiles/util_static.dir/random.c.o.provides.build
.PHONY : src/CMakeFiles/util_static.dir/random.c.o.provides

src/CMakeFiles/util_static.dir/random.c.o.provides.build: src/CMakeFiles/util_static.dir/random.c.o

# Object files for target util_static
util_static_OBJECTS = \
"CMakeFiles/util_static.dir/random.c.o"

# External object files for target util_static
util_static_EXTERNAL_OBJECTS =

lib/libutil.a: src/CMakeFiles/util_static.dir/random.c.o
lib/libutil.a: src/CMakeFiles/util_static.dir/build.make
lib/libutil.a: src/CMakeFiles/util_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library ../lib/libutil.a"
	cd /home/pi/c/practise/heap/lib/libutil/build/src && $(CMAKE_COMMAND) -P CMakeFiles/util_static.dir/cmake_clean_target.cmake
	cd /home/pi/c/practise/heap/lib/libutil/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/util_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/util_static.dir/build: lib/libutil.a
.PHONY : src/CMakeFiles/util_static.dir/build

src/CMakeFiles/util_static.dir/requires: src/CMakeFiles/util_static.dir/random.c.o.requires
.PHONY : src/CMakeFiles/util_static.dir/requires

src/CMakeFiles/util_static.dir/clean:
	cd /home/pi/c/practise/heap/lib/libutil/build/src && $(CMAKE_COMMAND) -P CMakeFiles/util_static.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/util_static.dir/clean

src/CMakeFiles/util_static.dir/depend:
	cd /home/pi/c/practise/heap/lib/libutil/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/c/practise/heap/lib/libutil /home/pi/c/practise/heap/lib/libutil/src /home/pi/c/practise/heap/lib/libutil/build /home/pi/c/practise/heap/lib/libutil/build/src /home/pi/c/practise/heap/lib/libutil/build/src/CMakeFiles/util_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/util_static.dir/depend

