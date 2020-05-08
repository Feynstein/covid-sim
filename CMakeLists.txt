# CMakeLists.txt

# CMake setup
cmake_minimum_required (VERSION 3.8)

project(CovidSim C CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

set(default_build_type "RelWithDebInfo")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


#Enabling automated out of source build
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT DEFINED OVERRIDE_BINARY_FULLDIR)
  if(NOT DEFINED OVERRIDE_BINARY_SUBDIR)
     if( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/covid-sim_build/${GIT_BRANCH})
     elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/covid-sim_build/${GIT_BRANCH}/${CMAKE_BUILD_TYPE})
     endif()
  else()
        set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/${OVERRIDE_BINARY_SUBDIR}/${CMAKE_BUILD_TYPE})
  endif()
else()
     set(PROJECT_BINARY_DIR ${OVERRIDE_BINARY_FULLDIR})
endif()

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Set a default build type if none was specified

# Project initialisation
add_definitions(-DUSE_OPENMP)
# option(USE_OPENMP "Compile with OpenMP parallelism enabled" ON)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL  "3.12.4") 
		cmake_policy(SET CMP0074 NEW) 
endif()
find_package(Boost 1.58 REQUIRED COMPONENTS
		atomic
		chrono
		date_time
		filesystem
		math_c99f
		math_c99l
		math_c99
		math_tr1f
		math_tr1l
		math_tr1
		program_options
		random
		serialization
		signals
		system
		thread
		timer)
include_directories( ${Boost_INCLUDE_DIR} )


if(USE_OPENMP)
  find_package(OpenMP REQUIRED)
  if (OPENMP_FOUND) 
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  endif()
endif()


set(CMAKE_CXX_STANDARD 11)

include_directories("include/")
file(GLOB covid-sim_SOURCES "src/*.cpp")
file(GLOB covid-sim_HEADERS "include/*.h")



# CovidSim target
add_executable(CovidSim ${covid-sim_SOURCES} "CovidSim.cpp")
target_include_directories(CovidSim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(USE_OPENMP)
  target_link_libraries(CovidSim PUBLIC OpenMP::OpenMP_CXX)
endif()
if(WIN32)
  target_link_libraries(CovidSim PUBLIC Gdiplus.lib Vfw32.lib)
  target_compile_definitions(CovidSim PUBLIC  "_CRT_SECURE_NO_WARNINGS")
elseif(UNIX)
  target_compile_definitions(CovidSim PUBLIC UNIX)
else()
  message(FATAL_ERROR "Unknown operating system type: ${CMAKE_SYSTEM_NAME}")
endif()

source_group("headers" FILES ${covid-sim_HEADERS})
source_group("sources" FILES ${covid-sim_SOURCES})
