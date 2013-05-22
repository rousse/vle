include_directories(${VLE_BINARY_DIR}/src ${VLE_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIRS} ${VLEDEPS_INCLUDE_DIRS})

link_directories(${VLEDEPS_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(Dynamics.i PROPERTIES CPLUSPLUS ON)
#SET_SOURCE_FILES_PROPERTIES(Dynamics.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_MODULE(testDynamics python Dynamics.i testDynamics.cpp testDynamics.hpp)
SWIG_LINK_LIBRARIES(testDynamics ${PYTHON_LIBRARIES} vlelib)

INSTALL(TARGETS _testDynamics DESTINATION lib/python/lib-dynload)
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/pydynamics/testDynamics.py DESTINATION lib/python)

###
###ancien pydynamics
###INSTALL(TARGETS _pyDynamics DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python/lib-dynload")
###INSTALL(FILES ${CMAKE_BINARY_DIR}/src/pyDynamics.py DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python")
###
###pyvle
###INSTALL(TARGETS pyvle DESTINATION lib/python${PYTHON_VERSION}/lib-dynload)
###INSTALL(FILES pyvle.py DESTINATION lib/python${PYTHON_VERSION})
###

