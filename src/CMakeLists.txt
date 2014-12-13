cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE, "Release" "Build Type")

set(POLYCODE_HOME $ENV{HOME}/workspace/Polycode)
set(POLYCODE_RELEASE ${POLYCODE_HOME}/Release/Linux/Framework)

##############################################################################
# DEFINE 
##############################################################################
include_directories(
  .
  ${POLYCODE_RELEASE}/Core/Dependencies/include
  ${POLYCODE_RELEASE}/Core/Dependencies/include/AL
  ${POLYCODE_RELEASE}/Core/Dependencies/include/lua5.1
  ${POLYCODE_RELEASE}/Core/include
  ${POLYCODE_RELEASE}/Modules/include
  ${POLYCODE_RELEASE}/Modules/Dependencies/include
  ${POLYCODE_RELEASE}/Modules/Dependencies/include/bullet
)

add_library(libPolycore STATIC IMPORTED)
add_library(libfreetype STATIC IMPORTED)
add_library(liblibvorbisfile STATIC IMPORTED)
add_library(liblibvorbis STATIC IMPORTED)
add_library(liblibogg STATIC IMPORTED)
add_library(libopenal SHARED IMPORTED)
add_library(libphysfs STATIC IMPORTED)
add_library(libpng15 STATIC IMPORTED)
add_library(libz STATIC IMPORTED)
add_library(liblua STATIC IMPORTED)
add_library(libPolycode2DPhysics STATIC IMPORTED)
add_library(libBox2D STATIC IMPORTED)
add_library(libPolycode3DPhysics STATIC IMPORTED)
add_library(libBulletDynamics STATIC IMPORTED)
add_library(libBulletCollision STATIC IMPORTED)
add_library(libLinearMath STATIC IMPORTED)

set_property(TARGET libPolycore PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Core/lib/libPolycore.a)
set_property(TARGET libfreetype PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Core/Dependencies/lib/libfreetype.a)
set_property(TARGET liblibvorbisfile PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Core/Dependencies/lib/liblibvorbisfile.a)
set_property(TARGET liblibvorbis PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Core/Dependencies/lib/liblibvorbis.a)
set_property(TARGET liblibogg PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Core/Dependencies/lib/liblibogg.a)
set_property(TARGET libopenal PROPERTY IMPORTED_LOCATION ${POLYCODE_RELEASE}/Core/Dependencies/lib/libopenal.so)
set_property(TARGET libphysfs PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Core/Dependencies/lib/libphysfs.a)
set_property(TARGET libpng15 PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Core/Dependencies/lib/libpng15.a)
set_property(TARGET libz PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Core/Dependencies/lib/libz.a)
set_property(TARGET liblua PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Core/Dependencies/lib/liblua5.1.a)
set_property(TARGET libPolycode2DPhysics PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Modules/lib/libPolycode2DPhysics.a)
set_property(TARGET libBox2D PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Modules/Dependencies/lib/libBox2D.a)
set_property(TARGET libPolycode3DPhysics PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Modules/lib/libPolycode3DPhysics.a)
set_property(TARGET libBulletDynamics PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Modules/Dependencies/lib/libBulletDynamics.a)
set_property(TARGET libBulletCollision PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Modules/Dependencies/lib/libBulletCollision.a)
set_property(TARGET libLinearMath PROPERTY IMPORTED_LOCATION   ${POLYCODE_RELEASE}/Modules/Dependencies/lib/libLinearMath.a)

set(Synthetics_SRCS
  SyntheticsApp.cpp
  Configurator.cpp
  OrbitCamera.cpp
  Constructor.cpp
  HeadUpDisplay.cpp
  UnitEntity.cpp
  UnitPosition.cpp
  UnitEvent.cpp
  UnitFactory.cpp
  UnitPlugging.cpp
)

set(Synthetics_HDRS
  SyntheticsApp.hpp
  Configurator.hpp
  MovingCamera.hpp
  OrbitCamera.hpp
  Constructor.hpp
  HeadUpDisplay.hpp
  Unit.hpp
  UnitEntity.hpp
  UnitPosition.hpp
  UnitEvent.hpp
  UnitPlugging.hpp
)

set(Polycode_LIBS
  libPolycore
  libfreetype
  liblibvorbisfile
  liblibvorbis
  liblibogg
  libopenal
  libphysfs
  libpng15
  libz
  liblua
  libPolycode2DPhysics
  libBox2D
  libPolycode3DPhysics
  libBulletDynamics
  libBulletCollision
  libLinearMath
  rt dl pthread X11 GL GLU SDL
)

##############################################################################
# BUILD 
##############################################################################
add_executable(
  Synthetics
  main.cpp 
)

add_library(
  PassiveBlock SHARED
  Units/Passive/Block.cpp
)

add_library(
  synthetics STATIC
  ${Synthetics_SRCS} ${Synthetics_HDRS}
)
target_link_libraries(
  Synthetics 
  synthetics
  ${Polycode_LIBS}
)

##############################################################################
# INSTALL 
##############################################################################
install(TARGETS Synthetics PassiveBlock
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

install(FILES ${Synthetics_HDRS} DESTINATION include)

##############################################################################
# TESTING
##############################################################################
set(ENV(CTEST_OUTPUT_ON_FAILURE) YES)
enable_testing()

find_package(Boost
  COMPONENTS
  system
  filesystem
  unit_test_framework
  REQUIRED
)

include_directories(${Boost_INCLUDE_DIR})

add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(test_unit_plugging Tests/test_unit_plugging.cpp)
target_link_libraries(test_unit_plugging
  synthetics
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_executable(test_unit_entity Tests/test_unit_entity.cpp)
target_link_libraries(test_unit_entity
  synthetics
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_executable(test_unit_position Tests/test_unit_position.cpp)
target_link_libraries(test_unit_position
  synthetics
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_test(test_unit_entity test_unit_entity)
add_test(test_unit_position test_unit_position)
add_test(test_unit_plugging test_unit_plugging)
