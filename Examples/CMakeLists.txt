CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(ssm_vtk)


SET(CMAKE_VERBOSE_MAKEFILE ON)

FIND_PACKAGE(VTK REQUIRED)
include (${VTK_USE_FILE})


FILE(GLOB INCLUDE_FILES *.h)
FILE(GLOB SOURCE_FILES  *.txx *.cpp)


include_directories(${STATISMO_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/Representers/ 
					${VTK_INCLUDE_DIR}  
					${HDF5_INCLUDE_DIR} ${HDF5_INCLUDE_DIR_CPP})					

link_directories(${STATISMO_LIBRARY_DIR} ${VTK_LIBRARY_DIR} ${HDF5_LIBRARY_DIR})

IF(WIN32)
# Fix for VS2012 that has _VARIADIC_MAX set to 5. For some of the examples, this does not seem to be sufficient. 
#Don't set too high because it increases compiler memory usage / compile-time.
add_definitions( -D_VARIADIC_MAX=9 )
ENDIF()

 
add_executable (vtkBuildShapeModelExample BuildShapeModelExample.cxx) 
ADD_DEPENDENCIES(vtkBuildShapeModelExample HDF5)
target_link_libraries (vtkBuildShapeModelExample ${STATISMO_LIBRARIES} ${VTK_LIBRARIES} ${HDF5_LIBRARIES}  ${STATISMO_LIBRARIES})


add_executable (vtkBasicSamplingExample BasicSamplingExample.cxx) 
ADD_DEPENDENCIES(vtkBasicSamplingExample HDF5)
target_link_libraries (vtkBasicSamplingExample ${VTK_LIBRARIES} ${HDF5_LIBRARIES}  ${STATISMO_LIBRARIES})

 

add_executable (vtkCrossValidationExample CrossValidationExample.cxx) 
ADD_DEPENDENCIES(vtkCrossValidationExample HDF5)
target_link_libraries (vtkCrossValidationExample ${VTK_LIBRARIES} ${HDF5_LIBRARIES}  ${STATISMO_LIBRARIES})

add_executable (vtkBuildIntensityModelExample BuildIntensityModelExample.cxx) 
add_DEPENDENCIES(vtkBuildIntensityModelExample HDF5)
target_link_libraries (vtkBuildIntensityModelExample ${VTK_LIBRARIES} ${HDF5_LIBRARIES}  ${STATISMO_LIBRARIES})


add_executable (vtkReduceModelVarianceExample ReduceModelVarianceExample.cxx) 
add_DEPENDENCIES(vtkReduceModelVarianceExample HDF5)
target_link_libraries (vtkReduceModelVarianceExample ${VTK_LIBRARIES} ${HDF5_LIBRARIES}  ${STATISMO_LIBRARIES})


add_executable (vtkBuildPosteriorModelExample BuildPosteriorModelExample.cxx) 
add_DEPENDENCIES(vtkBuildPosteriorModelExample HDF5)
target_link_libraries (vtkBuildPosteriorModelExample ${VTK_LIBRARIES} ${HDF5_LIBRARIES}  ${STATISMO_LIBRARIES})


add_executable (vtkBuildConditionalModelExample BuildConditionalModelExample.cxx) 
add_DEPENDENCIES(vtkBuildConditionalModelExample HDF5)
target_link_libraries (vtkBuildConditionalModelExample  ${VTK_LIBRARIES} ${HDF5_LIBRARIES}  ${STATISMO_LIBRARIES})

add_executable (vtkBuildGaussianProcessShapeModelExample BuildGaussianProcessShapeModelExample.cxx) 
ADD_DEPENDENCIES(vtkBuildGaussianProcessShapeModelExample HDF5)
target_link_libraries (vtkBuildGaussianProcessShapeModelExample ${STATISMO_LIBRARIES} ${VTK_LIBRARIES} ${HDF5_LIBRARIES}  ${STATISMO_LIBRARIES})



INSTALL(TARGETS vtkBuildShapeModelExample vtkBasicSamplingExample vtkCrossValidationExample vtkBuildIntensityModelExample vtkBuildPosteriorModelExample vtkBuildConditionalModelExample vtkBuildGaussianProcessShapeModelExample RUNTIME DESTINATION bin)

INSTALL(PROGRAMS runVTKExamples.sh DESTINATION  bin)
