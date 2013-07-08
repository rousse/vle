INCLUDE_DIRECTORIES(
    ${VLE_BINARY_DIR}/src
    ${VLE_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
    ${VLEDEPS_INCLUDE_DIRS})
#+ ${VLE_INCLUDE_DIRS}


MESSAGE( "VLE_BINARY_DIR} : ${VLE_BINARY_DIR} " )
MESSAGE( "{VLE_SOURCE_DIR} : ${VLE_SOURCE_DIR} " )
MESSAGE( "Boost_INCLUDE_DIRS} : ${Boost_INCLUDE_DIRS} " )
MESSAGE( "VLEDEPS_INCLUDE_DIRS} : ${VLEDEPS_INCLUDE_DIRS} " )




link_directories(
    ${VLEDEPS_LIBRARY_DIRS}
    ${Boost_LIBRARY_DIRS})
#+ ${VLE_LIBRARY_DIRS}

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(Dynamics.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(testDynamics python Dynamics.i testDynamics.cpp testDynamics.hpp)
SWIG_LINK_LIBRARIES(testDynamics ${PYTHON_LIBRARIES} vlelib)

INSTALL(TARGETS _testDynamics DESTINATION "lib/python/lib-dynload")
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/pydynamics/testDynamics.py DESTINATION "/lib/python")




# !!! avec Dynamics.i relatif a Dynamics.hpp et non pas testDynamics.hpp
#SWIG_ADD_MODULE(PyDynamics python Dynamics.i ../vle/devs/Dynamics.cpp ../vle/devs/Dynamics.hpp)
#SWIG_LINK_LIBRARIES(PyDynamics ${PYTHON_LIBRARIES} vlelib)
#INSTALL(TARGETS _PyDynamics DESTINATION "lib/python/lib-dynload")
#INSTALL(FILES ${CMAKE_BINARY_DIR}/src/pydynamics/PyDynamics.py DESTINATION "/lib/python")


