include(CMakePrintHelpers)
cmake_minimum_required(VERSION 3.2)
project(hijing_wrapper LANGUAGES CXX Fortran)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug) # allows you to debug with DBG
set(PROJECT_SOURCE_DIR /home/egp28/hijing_wrapper)
set(PROJECT_BINARY_DIR /home/egp28/hijing_wrapper/build)

#enable_language(Fortran)
find_package(ROOT)

add_executable(Hij hijingcpp.cxx hipyset1.37zv.f hijing1.420.f)
add_executable(HijHep hijingHep.cxx hipyset1.37zv.f hijing1.420.f)
add_executable(HijHepRoot hijingHepROOT.cxx hipyset1.37zv.f hijing1.420.f)

set_target_properties(Hij PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(Hij PUBLIC gfortran ${ROOT_LIBRARIES} ${ROOT_LIB_OPT} $ENV{HEPMC3_ROOT_DIR}/lib64/libHepMC3.so ${HEPMC3_LIB_OPT})
target_include_directories(Hij PUBLIC ${PROJECT_BINARY_DIR} ${ROOT_INCLUDE_DIRS} ${ROOT_INCLUDE} $ENV{HEPMC3_INCLUDE})
target_compile_options(Hij PRIVATE -DHEPMC3 -DHEPMC3_ENABLE_ROOTIO=ON)

set_target_properties(HijHep PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(HijHep PUBLIC gfortran ${ROOT_LIBRARIES} ${ROOT_LIB_OPT} $ENV{HEPMC3_ROOT_DIR}/lib64/libHepMC3.so ${HEPMC3_LIB_OPT})
target_include_directories(HijHep PUBLIC ${PROJECT_BINARY_DIR} ${ROOT_INCLUDE_DIRS} ${ROOT_INCLUDE} $ENV{HEPMC3_INCLUDE})
target_compile_options(HijHep PRIVATE -DHEPMC3 -DHEPMC3_ENABLE_ROOTIO=ON)

set_target_properties(HijHepRoot PROPERTIES LINKER_LANGUAGE Fortran)
target_link_libraries(HijHepRoot PUBLIC gfortran ${ROOT_LIBRARIES} ${ROOT_LIB_OPT} $ENV{HEPMC3_ROOT_DIR}/lib64/libHepMC3.so ${HEPMC3_LIB_OPT})
target_include_directories(HijHepRoot PUBLIC ${PROJECT_BINARY_DIR} ${ROOT_INCLUDE_DIRS} ${ROOT_INCLUDE} $ENV{HEPMC3_INCLUDE})
target_compile_options(HijHepRoot PRIVATE -DHEPMC3 -DHEPMC3_ENABLE_ROOTIO=ON)
