# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/egor/Documents/aqbm1000ll

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/egor/Documents/aqbm1000ll/build

# Utility rule file for CMSIS_LD_L433C8.

# Include any custom commands dependencies for this target.
include CMakeFiles/CMSIS_LD_L433C8.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CMSIS_LD_L433C8.dir/progress.make

CMakeFiles/CMSIS_LD_L433C8: L433C8.ld

L433C8.ld:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/egor/Documents/aqbm1000ll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating L433C8.ld"
	/usr/bin/cmake -DFLASH_ORIGIN="0x8000000" -DRAM_ORIGIN="0x20000000" -DCCRAM_ORIGIN="0x10000000" -DRAM_SHARE_ORIGIN="0x20030000" -DFLASH_SIZE="64K" -DRAM_SIZE="64K" -DCCRAM_SIZE="0K" -DRAM_SHARE_SIZE="NOTFOUND" -DSTACK_SIZE="0x400" -DHEAP_SIZE="0x200" -DLINKER_SCRIPT="/home/egor/Documents/aqbm1000ll/build/L433C8.ld" -P /home/egor/Documents/aqbm1000ll/cmake/stm32/linker_ld.cmake

CMSIS_LD_L433C8: CMakeFiles/CMSIS_LD_L433C8
CMSIS_LD_L433C8: L433C8.ld
CMSIS_LD_L433C8: CMakeFiles/CMSIS_LD_L433C8.dir/build.make
.PHONY : CMSIS_LD_L433C8

# Rule to build all files generated by this target.
CMakeFiles/CMSIS_LD_L433C8.dir/build: CMSIS_LD_L433C8
.PHONY : CMakeFiles/CMSIS_LD_L433C8.dir/build

CMakeFiles/CMSIS_LD_L433C8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CMSIS_LD_L433C8.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CMSIS_LD_L433C8.dir/clean

CMakeFiles/CMSIS_LD_L433C8.dir/depend:
	cd /home/egor/Documents/aqbm1000ll/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/egor/Documents/aqbm1000ll /home/egor/Documents/aqbm1000ll /home/egor/Documents/aqbm1000ll/build /home/egor/Documents/aqbm1000ll/build /home/egor/Documents/aqbm1000ll/build/CMakeFiles/CMSIS_LD_L433C8.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CMSIS_LD_L433C8.dir/depend

