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

# Include any dependencies generated for this target.
include src/cpp/CMakeFiles/flann_s.dir/depend.make

# Include the progress variables for this target.
include src/cpp/CMakeFiles/flann_s.dir/progress.make

# Include the compile flags for this target's objects.
include src/cpp/CMakeFiles/flann_s.dir/flags.make

src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o: src/cpp/CMakeFiles/flann_s.dir/flags.make
src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o: ../src/cpp/flann/flann.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/flann_s.dir/flann/flann.cpp.o -c /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann/flann.cpp

src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flann_s.dir/flann/flann.cpp.i"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann/flann.cpp > CMakeFiles/flann_s.dir/flann/flann.cpp.i

src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flann_s.dir/flann/flann.cpp.s"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann/flann.cpp -o CMakeFiles/flann_s.dir/flann/flann.cpp.s

src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o.requires:

.PHONY : src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o.requires

src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o.provides: src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o.requires
	$(MAKE) -f src/cpp/CMakeFiles/flann_s.dir/build.make src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o.provides.build
.PHONY : src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o.provides

src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o.provides.build: src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o


src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o: src/cpp/CMakeFiles/flann_s.dir/flags.make
src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o: ../src/cpp/flann/ext/lz4.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/flann_s.dir/flann/ext/lz4.c.o   -c /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann/ext/lz4.c

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/flann_s.dir/flann/ext/lz4.c.i"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann/ext/lz4.c > CMakeFiles/flann_s.dir/flann/ext/lz4.c.i

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/flann_s.dir/flann/ext/lz4.c.s"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann/ext/lz4.c -o CMakeFiles/flann_s.dir/flann/ext/lz4.c.s

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o.requires:

.PHONY : src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o.requires

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o.provides: src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o.requires
	$(MAKE) -f src/cpp/CMakeFiles/flann_s.dir/build.make src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o.provides.build
.PHONY : src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o.provides

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o.provides.build: src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o


src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o: src/cpp/CMakeFiles/flann_s.dir/flags.make
src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o: ../src/cpp/flann/ext/lz4hc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o   -c /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann/ext/lz4hc.c

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.i"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann/ext/lz4hc.c > CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.i

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.s"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann/ext/lz4hc.c -o CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.s

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o.requires:

.PHONY : src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o.requires

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o.provides: src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o.requires
	$(MAKE) -f src/cpp/CMakeFiles/flann_s.dir/build.make src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o.provides.build
.PHONY : src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o.provides

src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o.provides.build: src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o


# Object files for target flann_s
flann_s_OBJECTS = \
"CMakeFiles/flann_s.dir/flann/flann.cpp.o" \
"CMakeFiles/flann_s.dir/flann/ext/lz4.c.o" \
"CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o"

# External object files for target flann_s
flann_s_EXTERNAL_OBJECTS =

lib/libflann_s.a: src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o
lib/libflann_s.a: src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o
lib/libflann_s.a: src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o
lib/libflann_s.a: src/cpp/CMakeFiles/flann_s.dir/build.make
lib/libflann_s.a: src/cpp/CMakeFiles/flann_s.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ../../lib/libflann_s.a"
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && $(CMAKE_COMMAND) -P CMakeFiles/flann_s.dir/cmake_clean_target.cmake
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flann_s.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/cpp/CMakeFiles/flann_s.dir/build: lib/libflann_s.a

.PHONY : src/cpp/CMakeFiles/flann_s.dir/build

src/cpp/CMakeFiles/flann_s.dir/requires: src/cpp/CMakeFiles/flann_s.dir/flann/flann.cpp.o.requires
src/cpp/CMakeFiles/flann_s.dir/requires: src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4.c.o.requires
src/cpp/CMakeFiles/flann_s.dir/requires: src/cpp/CMakeFiles/flann_s.dir/flann/ext/lz4hc.c.o.requires

.PHONY : src/cpp/CMakeFiles/flann_s.dir/requires

src/cpp/CMakeFiles/flann_s.dir/clean:
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp && $(CMAKE_COMMAND) -P CMakeFiles/flann_s.dir/cmake_clean.cmake
.PHONY : src/cpp/CMakeFiles/flann_s.dir/clean

src/cpp/CMakeFiles/flann_s.dir/depend:
	cd /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1 /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/src/cpp/CMakeFiles/flann_s.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/cpp/CMakeFiles/flann_s.dir/depend

