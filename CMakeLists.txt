cmake_minimum_required(VERSION 2.8)
Set(NEST_SOLUTION_FOLDERS True)
project("JSON_SPIRIT")

FIND_PACKAGE(Boost 1.51)

IF (NOT Boost_FOUND)
	MESSAGE(WARNING "DIDN'T FIND BOOST, TRYING TO USE %ENV_BOOST_PATH% ENVIRONMENT VARIABLE")

	# in case BOOST_ROOT is invalid, use the environment variable ENV_BOOST_PATH
	SET(BOOST_ROOT $ENV{ENV_BOOST_PATH})
ENDIF()

# OS specific rules...
IF(CMAKE_SYSTEM_NAME MATCHES Windows)

    FIND_PACKAGE(Boost REQUIRED)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${JSON_SPIRIT_SOURCE_DIR}/exec)
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${JSON_SPIRIT_SOURCE_DIR}/exec)

    # definitions used by visual studio to export or import as a dynamic library.
    ADD_DEFINITIONS(-DXXON_EXPORTS)

    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} ${Boost_INCLUDE_DIR}/stage/lib_$(PlatformShortName))
    ADD_DEFINITIONS("/wd4251 /wd4275 /MP") # disable some warnings and enable multiprocessing.

ELSEIF(CMAKE_SYSTEM_NAME MATCHES Linux)

    FIND_PACKAGE(Boost COMPONENTS filesystem REQUIRED)
    ADD_DEFINITIONS("-std=c++0x")

ENDIF()

SET(Boost_DETAILED_FAILURE_MSG TRUE)
SET (LIB_TYPE SHARED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# project source files.
FILE(GLOB SOURCES_CPP "src/*.cpp")
FILE(GLOB SOURCES_H "src/*.hpp")
LIST(APPEND SOURCES_SRC ${SOURCES_CPP} ${SOURCES_H})  

ADD_LIBRARY(json_spirit ${LIB_TYPE} ${SOURCES_SRC})
SET_TARGET_PROPERTIES(json_spirit PROPERTIES LINKER_LANGUAGE CXX)

# unit test source files.
FILE(GLOB TESTS_CPP "test-suite/*.cpp")
FILE(GLOB TESTS_H "test-suite/*.hpp")
LIST(APPEND TESTS_SRC ${TESTS_CPP} ${TESTS_H}) 

INCLUDE_DIRECTORIES(${JSON_SPIRIT_SOURCE_DIR})
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH} ${Boost_LIBRARY_DIRS} ${BOOST_ROOT}/stage/lib_$(PlatformShortName))
    
# json_spirit unit tests.
ADD_EXECUTABLE(json_spirit_tests ${TESTS_SRC})

SET_TARGET_PROPERTIES(json_spirit_tests PROPERTIES LINKER_LANGUAGE CXX)

# adiciona dependências
TARGET_LINK_LIBRARIES(json_spirit_tests json_spirit)
TARGET_LINK_LIBRARIES(json_spirit_tests ${Boost_LIBRARIES})
