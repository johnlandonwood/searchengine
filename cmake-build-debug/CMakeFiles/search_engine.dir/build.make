# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /cygdrive/c/Users/Owner/AppData/Local/JetBrains/CLion2020.2/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Owner/AppData/Local/JetBrains/CLion2020.2/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Owner/CS2341/search-engine-harrison-wood

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/search_engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/search_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/search_engine.dir/flags.make

CMakeFiles/search_engine.dir/main.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/search_engine.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/main.cpp.o -c /home/Owner/CS2341/search-engine-harrison-wood/main.cpp

CMakeFiles/search_engine.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Owner/CS2341/search-engine-harrison-wood/main.cpp > CMakeFiles/search_engine.dir/main.cpp.i

CMakeFiles/search_engine.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Owner/CS2341/search-engine-harrison-wood/main.cpp -o CMakeFiles/search_engine.dir/main.cpp.s

CMakeFiles/search_engine.dir/UserInterface.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/UserInterface.cpp.o: ../UserInterface.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/search_engine.dir/UserInterface.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/UserInterface.cpp.o -c /home/Owner/CS2341/search-engine-harrison-wood/UserInterface.cpp

CMakeFiles/search_engine.dir/UserInterface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/UserInterface.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Owner/CS2341/search-engine-harrison-wood/UserInterface.cpp > CMakeFiles/search_engine.dir/UserInterface.cpp.i

CMakeFiles/search_engine.dir/UserInterface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/UserInterface.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Owner/CS2341/search-engine-harrison-wood/UserInterface.cpp -o CMakeFiles/search_engine.dir/UserInterface.cpp.s

CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.o: ../InvertedIndexEntry.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.o -c /home/Owner/CS2341/search-engine-harrison-wood/InvertedIndexEntry.cpp

CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Owner/CS2341/search-engine-harrison-wood/InvertedIndexEntry.cpp > CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.i

CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Owner/CS2341/search-engine-harrison-wood/InvertedIndexEntry.cpp -o CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.s

CMakeFiles/search_engine.dir/InvertedIndex.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/InvertedIndex.cpp.o: ../InvertedIndex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/search_engine.dir/InvertedIndex.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/InvertedIndex.cpp.o -c /home/Owner/CS2341/search-engine-harrison-wood/InvertedIndex.cpp

CMakeFiles/search_engine.dir/InvertedIndex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/InvertedIndex.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Owner/CS2341/search-engine-harrison-wood/InvertedIndex.cpp > CMakeFiles/search_engine.dir/InvertedIndex.cpp.i

CMakeFiles/search_engine.dir/InvertedIndex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/InvertedIndex.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Owner/CS2341/search-engine-harrison-wood/InvertedIndex.cpp -o CMakeFiles/search_engine.dir/InvertedIndex.cpp.s

CMakeFiles/search_engine.dir/DocumentProcessor.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/DocumentProcessor.cpp.o: ../DocumentProcessor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/search_engine.dir/DocumentProcessor.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/DocumentProcessor.cpp.o -c /home/Owner/CS2341/search-engine-harrison-wood/DocumentProcessor.cpp

CMakeFiles/search_engine.dir/DocumentProcessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/DocumentProcessor.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Owner/CS2341/search-engine-harrison-wood/DocumentProcessor.cpp > CMakeFiles/search_engine.dir/DocumentProcessor.cpp.i

CMakeFiles/search_engine.dir/DocumentProcessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/DocumentProcessor.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Owner/CS2341/search-engine-harrison-wood/DocumentProcessor.cpp -o CMakeFiles/search_engine.dir/DocumentProcessor.cpp.s

CMakeFiles/search_engine.dir/QueryProcessor.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/QueryProcessor.cpp.o: ../QueryProcessor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/search_engine.dir/QueryProcessor.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/QueryProcessor.cpp.o -c /home/Owner/CS2341/search-engine-harrison-wood/QueryProcessor.cpp

CMakeFiles/search_engine.dir/QueryProcessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/QueryProcessor.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Owner/CS2341/search-engine-harrison-wood/QueryProcessor.cpp > CMakeFiles/search_engine.dir/QueryProcessor.cpp.i

CMakeFiles/search_engine.dir/QueryProcessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/QueryProcessor.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Owner/CS2341/search-engine-harrison-wood/QueryProcessor.cpp -o CMakeFiles/search_engine.dir/QueryProcessor.cpp.s

CMakeFiles/search_engine.dir/IndexHandler.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/IndexHandler.cpp.o: ../IndexHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/search_engine.dir/IndexHandler.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/IndexHandler.cpp.o -c /home/Owner/CS2341/search-engine-harrison-wood/IndexHandler.cpp

CMakeFiles/search_engine.dir/IndexHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/IndexHandler.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Owner/CS2341/search-engine-harrison-wood/IndexHandler.cpp > CMakeFiles/search_engine.dir/IndexHandler.cpp.i

CMakeFiles/search_engine.dir/IndexHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/IndexHandler.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Owner/CS2341/search-engine-harrison-wood/IndexHandler.cpp -o CMakeFiles/search_engine.dir/IndexHandler.cpp.s

# Object files for target search_engine
search_engine_OBJECTS = \
"CMakeFiles/search_engine.dir/main.cpp.o" \
"CMakeFiles/search_engine.dir/UserInterface.cpp.o" \
"CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.o" \
"CMakeFiles/search_engine.dir/InvertedIndex.cpp.o" \
"CMakeFiles/search_engine.dir/DocumentProcessor.cpp.o" \
"CMakeFiles/search_engine.dir/QueryProcessor.cpp.o" \
"CMakeFiles/search_engine.dir/IndexHandler.cpp.o"

# External object files for target search_engine
search_engine_EXTERNAL_OBJECTS =

search_engine.exe: CMakeFiles/search_engine.dir/main.cpp.o
search_engine.exe: CMakeFiles/search_engine.dir/UserInterface.cpp.o
search_engine.exe: CMakeFiles/search_engine.dir/InvertedIndexEntry.cpp.o
search_engine.exe: CMakeFiles/search_engine.dir/InvertedIndex.cpp.o
search_engine.exe: CMakeFiles/search_engine.dir/DocumentProcessor.cpp.o
search_engine.exe: CMakeFiles/search_engine.dir/QueryProcessor.cpp.o
search_engine.exe: CMakeFiles/search_engine.dir/IndexHandler.cpp.o
search_engine.exe: CMakeFiles/search_engine.dir/build.make
search_engine.exe: CMakeFiles/search_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable search_engine.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/search_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/search_engine.dir/build: search_engine.exe

.PHONY : CMakeFiles/search_engine.dir/build

CMakeFiles/search_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/search_engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/search_engine.dir/clean

CMakeFiles/search_engine.dir/depend:
	cd /home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Owner/CS2341/search-engine-harrison-wood /home/Owner/CS2341/search-engine-harrison-wood /home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug /home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug /home/Owner/CS2341/search-engine-harrison-wood/cmake-build-debug/CMakeFiles/search_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/search_engine.dir/depend

