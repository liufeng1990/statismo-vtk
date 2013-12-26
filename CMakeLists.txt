cmake_minimum_required (VERSION 2.6)
project (statismo-vtk)

ENABLE_TESTING()

SET(STATISMO_VTK_VERSION 0.9) 
SET(STATISMO_VTK_MINOR_VERSION 0)

FIND_PACKAGE(STATISMO REQUIRED)

# rpath settings
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Setup build locations.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


FIND_PATH(HDF5_INCLUDE_DIR hdf5.h)
FIND_PATH(HDF5_INCLUDE_DIR_CPP H5Cpp.h)
FIND_LIBRARY(HDF5_LIBRARY hdf5)
FIND_LIBRARY(HDF5_CPP_LIBRARY hdf5_cpp)
GET_FILENAME_COMPONENT(HDF5_LIBRARY_DIR ${HDF5_LIBRARY} PATH) 
SET (HDF5_LIBRARIES ${HDF5_LIBRARY} ${HDF5_CPP_LIBRARY})
SET (STATISMO_LIBRARY_DIR ${HDF5_LIBRARY_DIR})	


#
#optional examples and wrapping
OPTION(BUILD_EXAMPLES "Build the vtk examples " OFF)
OPTION(BUILD_PYTHON_WRAPPING "Build python wrapping" OFF)

#
#optional tests
#
OPTION(BUILD_STATISMO_TESTS "Build tests" OFF)
OPTION(BUILD_STATISMO_TESTS_PYTHON "Build Unit tests written in python (requires python wrapping)") 
OPTION(BUILD_REPRESENTER_TESTS "Build representer tests (requires ITK and VTK)" OFF)

# 
# copy the data
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION share)

set(STATISMO_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})


if (BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif()

if (BUILD_STATISMO_TESTS)
  add_subdirectory(Tests)
endif()


if (BUILD_STATISMO_TESTS_PYTHON)
  set(BUILD_PYTHON_WRAPPING ON)
  add_custom_target(unit_test  ${CMAKE_CURRENT_SOURCE_DIR}/Tests/statismoTests/runPythonTests.sh ${CMAKE_CURRENT_BINARY_DIR}/Wrapping/SWIG ${CMAKE_CURRENT_SOURCE_DIR}/Tests/statismoTests/)
endif()

if (BUILD_TESTS)
  add_subdirectory(Tests)	  
endif()


if (BUILD_REPRESENTER_TESTS)
  add_subdirectory(Tests/representerTests)	  
endif()


if (BUILD_PYTHON_WRAPPING)
  add_subdirectory(Wrapping/SWIG)
endif()



