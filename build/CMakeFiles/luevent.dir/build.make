# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/luevent

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/luevent/build

# Include any dependencies generated for this target.
include CMakeFiles/luevent.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/luevent.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/luevent.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/luevent.dir/flags.make

CMakeFiles/luevent.dir/src/lu_event.c.o: CMakeFiles/luevent.dir/flags.make
CMakeFiles/luevent.dir/src/lu_event.c.o: /root/luevent/src/lu_event.c
CMakeFiles/luevent.dir/src/lu_event.c.o: CMakeFiles/luevent.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/luevent/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/luevent.dir/src/lu_event.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/luevent.dir/src/lu_event.c.o -MF CMakeFiles/luevent.dir/src/lu_event.c.o.d -o CMakeFiles/luevent.dir/src/lu_event.c.o -c /root/luevent/src/lu_event.c

CMakeFiles/luevent.dir/src/lu_event.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/luevent.dir/src/lu_event.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/luevent/src/lu_event.c > CMakeFiles/luevent.dir/src/lu_event.c.i

CMakeFiles/luevent.dir/src/lu_event.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/luevent.dir/src/lu_event.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/luevent/src/lu_event.c -o CMakeFiles/luevent.dir/src/lu_event.c.s

CMakeFiles/luevent.dir/src/lu_mm-internal.c.o: CMakeFiles/luevent.dir/flags.make
CMakeFiles/luevent.dir/src/lu_mm-internal.c.o: /root/luevent/src/lu_mm-internal.c
CMakeFiles/luevent.dir/src/lu_mm-internal.c.o: CMakeFiles/luevent.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/luevent/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/luevent.dir/src/lu_mm-internal.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/luevent.dir/src/lu_mm-internal.c.o -MF CMakeFiles/luevent.dir/src/lu_mm-internal.c.o.d -o CMakeFiles/luevent.dir/src/lu_mm-internal.c.o -c /root/luevent/src/lu_mm-internal.c

CMakeFiles/luevent.dir/src/lu_mm-internal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/luevent.dir/src/lu_mm-internal.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/luevent/src/lu_mm-internal.c > CMakeFiles/luevent.dir/src/lu_mm-internal.c.i

CMakeFiles/luevent.dir/src/lu_mm-internal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/luevent.dir/src/lu_mm-internal.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/luevent/src/lu_mm-internal.c -o CMakeFiles/luevent.dir/src/lu_mm-internal.c.s

CMakeFiles/luevent.dir/src/main.c.o: CMakeFiles/luevent.dir/flags.make
CMakeFiles/luevent.dir/src/main.c.o: /root/luevent/src/main.c
CMakeFiles/luevent.dir/src/main.c.o: CMakeFiles/luevent.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/luevent/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/luevent.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/luevent.dir/src/main.c.o -MF CMakeFiles/luevent.dir/src/main.c.o.d -o CMakeFiles/luevent.dir/src/main.c.o -c /root/luevent/src/main.c

CMakeFiles/luevent.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/luevent.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/luevent/src/main.c > CMakeFiles/luevent.dir/src/main.c.i

CMakeFiles/luevent.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/luevent.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/luevent/src/main.c -o CMakeFiles/luevent.dir/src/main.c.s

# Object files for target luevent
luevent_OBJECTS = \
"CMakeFiles/luevent.dir/src/lu_event.c.o" \
"CMakeFiles/luevent.dir/src/lu_mm-internal.c.o" \
"CMakeFiles/luevent.dir/src/main.c.o"

# External object files for target luevent
luevent_EXTERNAL_OBJECTS =

luevent: CMakeFiles/luevent.dir/src/lu_event.c.o
luevent: CMakeFiles/luevent.dir/src/lu_mm-internal.c.o
luevent: CMakeFiles/luevent.dir/src/main.c.o
luevent: CMakeFiles/luevent.dir/build.make
luevent: CMakeFiles/luevent.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/root/luevent/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable luevent"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/luevent.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/luevent.dir/build: luevent
.PHONY : CMakeFiles/luevent.dir/build

CMakeFiles/luevent.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/luevent.dir/cmake_clean.cmake
.PHONY : CMakeFiles/luevent.dir/clean

CMakeFiles/luevent.dir/depend:
	cd /root/luevent/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/luevent /root/luevent /root/luevent/build /root/luevent/build /root/luevent/build/CMakeFiles/luevent.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/luevent.dir/depend

