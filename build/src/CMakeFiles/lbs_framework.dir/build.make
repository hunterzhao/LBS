# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /mnt/hgfs/workstation/LBS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/workstation/LBS/build

# Include any dependencies generated for this target.
include src/CMakeFiles/lbs_framework.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/lbs_framework.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/lbs_framework.dir/flags.make

src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o: src/CMakeFiles/lbs_framework.dir/flags.make
src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o: ../src/lbsserver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/workstation/LBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lbs_framework.dir/lbsserver.cpp.o -c /mnt/hgfs/workstation/LBS/src/lbsserver.cpp

src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lbs_framework.dir/lbsserver.cpp.i"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/workstation/LBS/src/lbsserver.cpp > CMakeFiles/lbs_framework.dir/lbsserver.cpp.i

src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lbs_framework.dir/lbsserver.cpp.s"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/workstation/LBS/src/lbsserver.cpp -o CMakeFiles/lbs_framework.dir/lbsserver.cpp.s

src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o.requires:

.PHONY : src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o.requires

src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o.provides: src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/lbs_framework.dir/build.make src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o.provides.build
.PHONY : src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o.provides

src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o.provides.build: src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o


src/CMakeFiles/lbs_framework.dir/task.cpp.o: src/CMakeFiles/lbs_framework.dir/flags.make
src/CMakeFiles/lbs_framework.dir/task.cpp.o: ../src/task.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/workstation/LBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/lbs_framework.dir/task.cpp.o"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lbs_framework.dir/task.cpp.o -c /mnt/hgfs/workstation/LBS/src/task.cpp

src/CMakeFiles/lbs_framework.dir/task.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lbs_framework.dir/task.cpp.i"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/workstation/LBS/src/task.cpp > CMakeFiles/lbs_framework.dir/task.cpp.i

src/CMakeFiles/lbs_framework.dir/task.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lbs_framework.dir/task.cpp.s"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/workstation/LBS/src/task.cpp -o CMakeFiles/lbs_framework.dir/task.cpp.s

src/CMakeFiles/lbs_framework.dir/task.cpp.o.requires:

.PHONY : src/CMakeFiles/lbs_framework.dir/task.cpp.o.requires

src/CMakeFiles/lbs_framework.dir/task.cpp.o.provides: src/CMakeFiles/lbs_framework.dir/task.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/lbs_framework.dir/build.make src/CMakeFiles/lbs_framework.dir/task.cpp.o.provides.build
.PHONY : src/CMakeFiles/lbs_framework.dir/task.cpp.o.provides

src/CMakeFiles/lbs_framework.dir/task.cpp.o.provides.build: src/CMakeFiles/lbs_framework.dir/task.cpp.o


src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o: src/CMakeFiles/lbs_framework.dir/flags.make
src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o: ../src/clientinfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/workstation/LBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lbs_framework.dir/clientinfo.cpp.o -c /mnt/hgfs/workstation/LBS/src/clientinfo.cpp

src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lbs_framework.dir/clientinfo.cpp.i"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/workstation/LBS/src/clientinfo.cpp > CMakeFiles/lbs_framework.dir/clientinfo.cpp.i

src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lbs_framework.dir/clientinfo.cpp.s"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/workstation/LBS/src/clientinfo.cpp -o CMakeFiles/lbs_framework.dir/clientinfo.cpp.s

src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o.requires:

.PHONY : src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o.requires

src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o.provides: src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/lbs_framework.dir/build.make src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o.provides.build
.PHONY : src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o.provides

src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o.provides.build: src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o


src/CMakeFiles/lbs_framework.dir/until.cpp.o: src/CMakeFiles/lbs_framework.dir/flags.make
src/CMakeFiles/lbs_framework.dir/until.cpp.o: ../src/until.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/workstation/LBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/lbs_framework.dir/until.cpp.o"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lbs_framework.dir/until.cpp.o -c /mnt/hgfs/workstation/LBS/src/until.cpp

src/CMakeFiles/lbs_framework.dir/until.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lbs_framework.dir/until.cpp.i"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/workstation/LBS/src/until.cpp > CMakeFiles/lbs_framework.dir/until.cpp.i

src/CMakeFiles/lbs_framework.dir/until.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lbs_framework.dir/until.cpp.s"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/workstation/LBS/src/until.cpp -o CMakeFiles/lbs_framework.dir/until.cpp.s

src/CMakeFiles/lbs_framework.dir/until.cpp.o.requires:

.PHONY : src/CMakeFiles/lbs_framework.dir/until.cpp.o.requires

src/CMakeFiles/lbs_framework.dir/until.cpp.o.provides: src/CMakeFiles/lbs_framework.dir/until.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/lbs_framework.dir/build.make src/CMakeFiles/lbs_framework.dir/until.cpp.o.provides.build
.PHONY : src/CMakeFiles/lbs_framework.dir/until.cpp.o.provides

src/CMakeFiles/lbs_framework.dir/until.cpp.o.provides.build: src/CMakeFiles/lbs_framework.dir/until.cpp.o


src/CMakeFiles/lbs_framework.dir/message.pb.cc.o: src/CMakeFiles/lbs_framework.dir/flags.make
src/CMakeFiles/lbs_framework.dir/message.pb.cc.o: ../src/message.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/workstation/LBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/lbs_framework.dir/message.pb.cc.o"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lbs_framework.dir/message.pb.cc.o -c /mnt/hgfs/workstation/LBS/src/message.pb.cc

src/CMakeFiles/lbs_framework.dir/message.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lbs_framework.dir/message.pb.cc.i"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/workstation/LBS/src/message.pb.cc > CMakeFiles/lbs_framework.dir/message.pb.cc.i

src/CMakeFiles/lbs_framework.dir/message.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lbs_framework.dir/message.pb.cc.s"
	cd /mnt/hgfs/workstation/LBS/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/workstation/LBS/src/message.pb.cc -o CMakeFiles/lbs_framework.dir/message.pb.cc.s

src/CMakeFiles/lbs_framework.dir/message.pb.cc.o.requires:

.PHONY : src/CMakeFiles/lbs_framework.dir/message.pb.cc.o.requires

src/CMakeFiles/lbs_framework.dir/message.pb.cc.o.provides: src/CMakeFiles/lbs_framework.dir/message.pb.cc.o.requires
	$(MAKE) -f src/CMakeFiles/lbs_framework.dir/build.make src/CMakeFiles/lbs_framework.dir/message.pb.cc.o.provides.build
.PHONY : src/CMakeFiles/lbs_framework.dir/message.pb.cc.o.provides

src/CMakeFiles/lbs_framework.dir/message.pb.cc.o.provides.build: src/CMakeFiles/lbs_framework.dir/message.pb.cc.o


# Object files for target lbs_framework
lbs_framework_OBJECTS = \
"CMakeFiles/lbs_framework.dir/lbsserver.cpp.o" \
"CMakeFiles/lbs_framework.dir/task.cpp.o" \
"CMakeFiles/lbs_framework.dir/clientinfo.cpp.o" \
"CMakeFiles/lbs_framework.dir/until.cpp.o" \
"CMakeFiles/lbs_framework.dir/message.pb.cc.o"

# External object files for target lbs_framework
lbs_framework_EXTERNAL_OBJECTS =

../lib/liblbs_framework.a: src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o
../lib/liblbs_framework.a: src/CMakeFiles/lbs_framework.dir/task.cpp.o
../lib/liblbs_framework.a: src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o
../lib/liblbs_framework.a: src/CMakeFiles/lbs_framework.dir/until.cpp.o
../lib/liblbs_framework.a: src/CMakeFiles/lbs_framework.dir/message.pb.cc.o
../lib/liblbs_framework.a: src/CMakeFiles/lbs_framework.dir/build.make
../lib/liblbs_framework.a: src/CMakeFiles/lbs_framework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/workstation/LBS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library ../../lib/liblbs_framework.a"
	cd /mnt/hgfs/workstation/LBS/build/src && $(CMAKE_COMMAND) -P CMakeFiles/lbs_framework.dir/cmake_clean_target.cmake
	cd /mnt/hgfs/workstation/LBS/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lbs_framework.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/lbs_framework.dir/build: ../lib/liblbs_framework.a

.PHONY : src/CMakeFiles/lbs_framework.dir/build

src/CMakeFiles/lbs_framework.dir/requires: src/CMakeFiles/lbs_framework.dir/lbsserver.cpp.o.requires
src/CMakeFiles/lbs_framework.dir/requires: src/CMakeFiles/lbs_framework.dir/task.cpp.o.requires
src/CMakeFiles/lbs_framework.dir/requires: src/CMakeFiles/lbs_framework.dir/clientinfo.cpp.o.requires
src/CMakeFiles/lbs_framework.dir/requires: src/CMakeFiles/lbs_framework.dir/until.cpp.o.requires
src/CMakeFiles/lbs_framework.dir/requires: src/CMakeFiles/lbs_framework.dir/message.pb.cc.o.requires

.PHONY : src/CMakeFiles/lbs_framework.dir/requires

src/CMakeFiles/lbs_framework.dir/clean:
	cd /mnt/hgfs/workstation/LBS/build/src && $(CMAKE_COMMAND) -P CMakeFiles/lbs_framework.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/lbs_framework.dir/clean

src/CMakeFiles/lbs_framework.dir/depend:
	cd /mnt/hgfs/workstation/LBS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/workstation/LBS /mnt/hgfs/workstation/LBS/src /mnt/hgfs/workstation/LBS/build /mnt/hgfs/workstation/LBS/build/src /mnt/hgfs/workstation/LBS/build/src/CMakeFiles/lbs_framework.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/lbs_framework.dir/depend

