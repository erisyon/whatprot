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
CMAKE_SOURCE_DIR = /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build

# Utility rule file for pyunit_test_clustering.py.

# Include the progress variables for this target.
include test/CMakeFiles/pyunit_test_clustering.py.dir/progress.make

test/CMakeFiles/pyunit_test_clustering.py: ../test/test_clustering.py
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running pyunit test(s) test_clustering.py"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/test && /usr/bin/python3.6 /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/bin/run_test.py /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/test/test_clustering.py

pyunit_test_clustering.py: test/CMakeFiles/pyunit_test_clustering.py
pyunit_test_clustering.py: test/CMakeFiles/pyunit_test_clustering.py.dir/build.make

.PHONY : pyunit_test_clustering.py

# Rule to build all files generated by this target.
test/CMakeFiles/pyunit_test_clustering.py.dir/build: pyunit_test_clustering.py

.PHONY : test/CMakeFiles/pyunit_test_clustering.py.dir/build

test/CMakeFiles/pyunit_test_clustering.py.dir/clean:
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/test && $(CMAKE_COMMAND) -P CMakeFiles/pyunit_test_clustering.py.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/pyunit_test_clustering.py.dir/clean

test/CMakeFiles/pyunit_test_clustering.py.dir/depend:
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1 /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/test /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/test /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/test/CMakeFiles/pyunit_test_clustering.py.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/pyunit_test_clustering.py.dir/depend

