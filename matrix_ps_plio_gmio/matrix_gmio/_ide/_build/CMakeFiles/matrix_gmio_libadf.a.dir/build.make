# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /tools/Xilinx/Vitis/2023.2/tps/lnx64/cmake-3.24.2/bin/cmake

# The command to remove a file.
RM = /tools/Xilinx/Vitis/2023.2/tps/lnx64/cmake-3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yzwu/Desktop/soc_test/matrix_gmio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yzwu/Desktop/soc_test/matrix_gmio/_ide/_build

# Utility rule file for matrix_gmio_libadf.a.

# Include any custom commands dependencies for this target.
include CMakeFiles/matrix_gmio_libadf.a.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/matrix_gmio_libadf.a.dir/progress.make

CMakeFiles/matrix_gmio_libadf.a: libadf.a
CMakeFiles/matrix_gmio_libadf.a: /home/yzwu/Desktop/soc_test/matrix_gmio/src/project.cpp

libadf.a: /home/yzwu/Desktop/soc_test/matrix_gmio/aiecompiler.cfg
libadf.a: /home/yzwu/Desktop/soc_test/matrix_gmio/aiecompiler.cfg
libadf.a: /home/yzwu/Desktop/soc_test/matrix_gmio/src/project.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/yzwu/Desktop/soc_test/matrix_gmio/_ide/_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating libadf.a"
	unset MAKEFLAGS&&/tools/Xilinx/Vitis/2023.2/bin/v++ -c --mode aie --target x86sim --config /home/yzwu/Desktop/soc_test/matrix_gmio/aiecompiler.cfg --config /home/yzwu/Desktop/soc_test/matrix_gmio/aiecompiler.cfg --platform /tools/Xilinx/Vitis/2023.2/base_platforms/xilinx_vck190_base_202320_1/xilinx_vck190_base_202320_1.xpfm --work_dir /home/yzwu/Desktop/soc_test/matrix_gmio/_ide/_build/./Work /home/yzwu/Desktop/soc_test/matrix_gmio/src/project.cpp

matrix_gmio_libadf.a: CMakeFiles/matrix_gmio_libadf.a
matrix_gmio_libadf.a: libadf.a
matrix_gmio_libadf.a: CMakeFiles/matrix_gmio_libadf.a.dir/build.make
.PHONY : matrix_gmio_libadf.a

# Rule to build all files generated by this target.
CMakeFiles/matrix_gmio_libadf.a.dir/build: matrix_gmio_libadf.a
.PHONY : CMakeFiles/matrix_gmio_libadf.a.dir/build

CMakeFiles/matrix_gmio_libadf.a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matrix_gmio_libadf.a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matrix_gmio_libadf.a.dir/clean

CMakeFiles/matrix_gmio_libadf.a.dir/depend:
	cd /home/yzwu/Desktop/soc_test/matrix_gmio/_ide/_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yzwu/Desktop/soc_test/matrix_gmio /home/yzwu/Desktop/soc_test/matrix_gmio /home/yzwu/Desktop/soc_test/matrix_gmio/_ide/_build /home/yzwu/Desktop/soc_test/matrix_gmio/_ide/_build /home/yzwu/Desktop/soc_test/matrix_gmio/_ide/_build/CMakeFiles/matrix_gmio_libadf.a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matrix_gmio_libadf.a.dir/depend
