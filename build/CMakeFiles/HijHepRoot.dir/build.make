# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /gpfs/gibbs/project/caines/shared/software/cmake-3.26.3/bin/cmake

# The command to remove a file.
RM = /gpfs/gibbs/project/caines/shared/software/cmake-3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/egp28/hijing_wrapper

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/egp28/hijing_wrapper/build

# Include any dependencies generated for this target.
include CMakeFiles/HijHepRoot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HijHepRoot.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HijHepRoot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HijHepRoot.dir/flags.make

CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.o: CMakeFiles/HijHepRoot.dir/flags.make
CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.o: /home/egp28/hijing_wrapper/hijingHepROOT.cxx
CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.o: CMakeFiles/HijHepRoot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egp28/hijing_wrapper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.o"
	/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.o -MF CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.o.d -o CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.o -c /home/egp28/hijing_wrapper/hijingHepROOT.cxx

CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.i"
	/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/egp28/hijing_wrapper/hijingHepROOT.cxx > CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.i

CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.s"
	/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/egp28/hijing_wrapper/hijingHepROOT.cxx -o CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.s

CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.o: CMakeFiles/HijHepRoot.dir/flags.make
CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.o: /home/egp28/hijing_wrapper/hipyset1.37zv.f
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egp28/hijing_wrapper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building Fortran object CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.o"
	/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /home/egp28/hijing_wrapper/hipyset1.37zv.f -o CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.o

CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing Fortran source to CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.i"
	/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /home/egp28/hijing_wrapper/hipyset1.37zv.f > CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.i

CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling Fortran source to assembly CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.s"
	/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /home/egp28/hijing_wrapper/hipyset1.37zv.f -o CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.s

CMakeFiles/HijHepRoot.dir/hijing1.420.f.o: CMakeFiles/HijHepRoot.dir/flags.make
CMakeFiles/HijHepRoot.dir/hijing1.420.f.o: /home/egp28/hijing_wrapper/hijing1.420.f
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egp28/hijing_wrapper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building Fortran object CMakeFiles/HijHepRoot.dir/hijing1.420.f.o"
	/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /home/egp28/hijing_wrapper/hijing1.420.f -o CMakeFiles/HijHepRoot.dir/hijing1.420.f.o

CMakeFiles/HijHepRoot.dir/hijing1.420.f.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing Fortran source to CMakeFiles/HijHepRoot.dir/hijing1.420.f.i"
	/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /home/egp28/hijing_wrapper/hijing1.420.f > CMakeFiles/HijHepRoot.dir/hijing1.420.f.i

CMakeFiles/HijHepRoot.dir/hijing1.420.f.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling Fortran source to assembly CMakeFiles/HijHepRoot.dir/hijing1.420.f.s"
	/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/gfortran $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /home/egp28/hijing_wrapper/hijing1.420.f -o CMakeFiles/HijHepRoot.dir/hijing1.420.f.s

# Object files for target HijHepRoot
HijHepRoot_OBJECTS = \
"CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.o" \
"CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.o" \
"CMakeFiles/HijHepRoot.dir/hijing1.420.f.o"

# External object files for target HijHepRoot
HijHepRoot_EXTERNAL_OBJECTS =

HijHepRoot: CMakeFiles/HijHepRoot.dir/hijingHepROOT.cxx.o
HijHepRoot: CMakeFiles/HijHepRoot.dir/hipyset1.37zv.f.o
HijHepRoot: CMakeFiles/HijHepRoot.dir/hijing1.420.f.o
HijHepRoot: CMakeFiles/HijHepRoot.dir/build.make
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libCore.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libImt.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libRIO.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libNet.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libHist.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libGraf.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libGraf3d.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libGpad.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libROOTDataFrame.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libTree.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libTreePlayer.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libRint.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libPostscript.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libMatrix.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libPhysics.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libMathCore.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libThread.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libMultiProc.so
HijHepRoot: /vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib/libROOTVecOps.so
HijHepRoot: /gpfs/gibbs/project/caines/shared/software/HepMC3-install/lib64/libHepMC3.so
HijHepRoot: CMakeFiles/HijHepRoot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/egp28/hijing_wrapper/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking Fortran executable HijHepRoot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HijHepRoot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HijHepRoot.dir/build: HijHepRoot
.PHONY : CMakeFiles/HijHepRoot.dir/build

CMakeFiles/HijHepRoot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HijHepRoot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HijHepRoot.dir/clean

CMakeFiles/HijHepRoot.dir/depend:
	cd /home/egp28/hijing_wrapper/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/egp28/hijing_wrapper /home/egp28/hijing_wrapper /home/egp28/hijing_wrapper/build /home/egp28/hijing_wrapper/build /home/egp28/hijing_wrapper/build/CMakeFiles/HijHepRoot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HijHepRoot.dir/depend

