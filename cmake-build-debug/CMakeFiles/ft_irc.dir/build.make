# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = "/Users/francois/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/213.6777.58/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/francois/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/213.6777.58/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/francois/Desktop/ft_irc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/francois/Desktop/ft_irc/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ft_irc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ft_irc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ft_irc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ft_irc.dir/flags.make

CMakeFiles/ft_irc.dir/srcs/Server.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/Server.cpp.o: ../srcs/Server.cpp
CMakeFiles/ft_irc.dir/srcs/Server.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ft_irc.dir/srcs/Server.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/Server.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/Server.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/Server.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/Server.cpp

CMakeFiles/ft_irc.dir/srcs/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/Server.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/Server.cpp > CMakeFiles/ft_irc.dir/srcs/Server.cpp.i

CMakeFiles/ft_irc.dir/srcs/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/Server.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/Server.cpp -o CMakeFiles/ft_irc.dir/srcs/Server.cpp.s

CMakeFiles/ft_irc.dir/srcs/channel.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/channel.cpp.o: ../srcs/channel.cpp
CMakeFiles/ft_irc.dir/srcs/channel.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ft_irc.dir/srcs/channel.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/channel.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/channel.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/channel.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/channel.cpp

CMakeFiles/ft_irc.dir/srcs/channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/channel.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/channel.cpp > CMakeFiles/ft_irc.dir/srcs/channel.cpp.i

CMakeFiles/ft_irc.dir/srcs/channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/channel.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/channel.cpp -o CMakeFiles/ft_irc.dir/srcs/channel.cpp.s

CMakeFiles/ft_irc.dir/srcs/client.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/client.cpp.o: ../srcs/client.cpp
CMakeFiles/ft_irc.dir/srcs/client.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ft_irc.dir/srcs/client.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/client.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/client.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/client.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/client.cpp

CMakeFiles/ft_irc.dir/srcs/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/client.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/client.cpp > CMakeFiles/ft_irc.dir/srcs/client.cpp.i

CMakeFiles/ft_irc.dir/srcs/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/client.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/client.cpp -o CMakeFiles/ft_irc.dir/srcs/client.cpp.s

CMakeFiles/ft_irc.dir/srcs/command.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/command.cpp.o: ../srcs/command.cpp
CMakeFiles/ft_irc.dir/srcs/command.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ft_irc.dir/srcs/command.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/command.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/command.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/command.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/command.cpp

CMakeFiles/ft_irc.dir/srcs/command.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/command.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/command.cpp > CMakeFiles/ft_irc.dir/srcs/command.cpp.i

CMakeFiles/ft_irc.dir/srcs/command.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/command.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/command.cpp -o CMakeFiles/ft_irc.dir/srcs/command.cpp.s

CMakeFiles/ft_irc.dir/srcs/lexer.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/lexer.cpp.o: ../srcs/lexer.cpp
CMakeFiles/ft_irc.dir/srcs/lexer.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ft_irc.dir/srcs/lexer.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/lexer.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/lexer.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/lexer.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/lexer.cpp

CMakeFiles/ft_irc.dir/srcs/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/lexer.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/lexer.cpp > CMakeFiles/ft_irc.dir/srcs/lexer.cpp.i

CMakeFiles/ft_irc.dir/srcs/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/lexer.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/lexer.cpp -o CMakeFiles/ft_irc.dir/srcs/lexer.cpp.s

CMakeFiles/ft_irc.dir/srcs/main.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/main.cpp.o: ../srcs/main.cpp
CMakeFiles/ft_irc.dir/srcs/main.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ft_irc.dir/srcs/main.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/main.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/main.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/main.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/main.cpp

CMakeFiles/ft_irc.dir/srcs/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/main.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/main.cpp > CMakeFiles/ft_irc.dir/srcs/main.cpp.i

CMakeFiles/ft_irc.dir/srcs/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/main.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/main.cpp -o CMakeFiles/ft_irc.dir/srcs/main.cpp.s

CMakeFiles/ft_irc.dir/srcs/numerics.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/numerics.cpp.o: ../srcs/numerics.cpp
CMakeFiles/ft_irc.dir/srcs/numerics.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/ft_irc.dir/srcs/numerics.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/numerics.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/numerics.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/numerics.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/numerics.cpp

CMakeFiles/ft_irc.dir/srcs/numerics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/numerics.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/numerics.cpp > CMakeFiles/ft_irc.dir/srcs/numerics.cpp.i

CMakeFiles/ft_irc.dir/srcs/numerics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/numerics.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/numerics.cpp -o CMakeFiles/ft_irc.dir/srcs/numerics.cpp.s

CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.o: ../srcs/parse_conf.cpp
CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/parse_conf.cpp

CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/parse_conf.cpp > CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.i

CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/parse_conf.cpp -o CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.s

CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.o: ../srcs/parsing_message.cpp
CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/parsing_message.cpp

CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/parsing_message.cpp > CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.i

CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/parsing_message.cpp -o CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.s

CMakeFiles/ft_irc.dir/srcs/t_token.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/t_token.cpp.o: ../srcs/t_token.cpp
CMakeFiles/ft_irc.dir/srcs/t_token.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/ft_irc.dir/srcs/t_token.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/t_token.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/t_token.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/t_token.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/t_token.cpp

CMakeFiles/ft_irc.dir/srcs/t_token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/t_token.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/t_token.cpp > CMakeFiles/ft_irc.dir/srcs/t_token.cpp.i

CMakeFiles/ft_irc.dir/srcs/t_token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/t_token.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/t_token.cpp -o CMakeFiles/ft_irc.dir/srcs/t_token.cpp.s

CMakeFiles/ft_irc.dir/srcs/utils.cpp.o: CMakeFiles/ft_irc.dir/flags.make
CMakeFiles/ft_irc.dir/srcs/utils.cpp.o: ../srcs/utils.cpp
CMakeFiles/ft_irc.dir/srcs/utils.cpp.o: CMakeFiles/ft_irc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/ft_irc.dir/srcs/utils.cpp.o"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ft_irc.dir/srcs/utils.cpp.o -MF CMakeFiles/ft_irc.dir/srcs/utils.cpp.o.d -o CMakeFiles/ft_irc.dir/srcs/utils.cpp.o -c /Users/francois/Desktop/ft_irc/srcs/utils.cpp

CMakeFiles/ft_irc.dir/srcs/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ft_irc.dir/srcs/utils.cpp.i"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/francois/Desktop/ft_irc/srcs/utils.cpp > CMakeFiles/ft_irc.dir/srcs/utils.cpp.i

CMakeFiles/ft_irc.dir/srcs/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ft_irc.dir/srcs/utils.cpp.s"
	clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/francois/Desktop/ft_irc/srcs/utils.cpp -o CMakeFiles/ft_irc.dir/srcs/utils.cpp.s

# Object files for target ft_irc
ft_irc_OBJECTS = \
"CMakeFiles/ft_irc.dir/srcs/Server.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/channel.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/client.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/command.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/lexer.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/main.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/numerics.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/t_token.cpp.o" \
"CMakeFiles/ft_irc.dir/srcs/utils.cpp.o"

# External object files for target ft_irc
ft_irc_EXTERNAL_OBJECTS =

ft_irc: CMakeFiles/ft_irc.dir/srcs/Server.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/channel.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/client.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/command.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/lexer.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/main.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/numerics.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/parse_conf.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/parsing_message.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/t_token.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/srcs/utils.cpp.o
ft_irc: CMakeFiles/ft_irc.dir/build.make
ft_irc: CMakeFiles/ft_irc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable ft_irc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ft_irc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ft_irc.dir/build: ft_irc
.PHONY : CMakeFiles/ft_irc.dir/build

CMakeFiles/ft_irc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ft_irc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ft_irc.dir/clean

CMakeFiles/ft_irc.dir/depend:
	cd /Users/francois/Desktop/ft_irc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/francois/Desktop/ft_irc /Users/francois/Desktop/ft_irc /Users/francois/Desktop/ft_irc/cmake-build-debug /Users/francois/Desktop/ft_irc/cmake-build-debug /Users/francois/Desktop/ft_irc/cmake-build-debug/CMakeFiles/ft_irc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ft_irc.dir/depend

