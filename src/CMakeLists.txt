cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE, "Release" "Build Type")

set(POLYCODE_HOME $ENV{HOME}/workspace/Polycode)
set(POLYCODE_RELEASE ${POLYCODE_HOME}/Release/Linux/Framework)

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
  main.cpp 
  SyntheticsApp.cpp
  Configurator.cpp
  OrbitCamera.cpp
  Constructor.cpp
  Help.cpp
  UnitEvent.cpp
  UnitFactory.cpp
)

set(Synthetics_HDRS
  SyntheticsApp.hpp
  Configurator.hpp
  MovingCamera.hpp
  OrbitCamera.hpp
  Constructor.hpp
  Help.hpp
  Unit.hpp
  UnitEvent.hpp
  UnitFactory.hpp
)

add_executable(
  Synthetics ${Synthetics_SRCS} ${Synthetics_HDRS}
)

add_library(
  PassiveBlock SHARED
  Units/Passive/Block.cpp
)

target_link_libraries(
  Synthetics 
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

install(TARGETS Synthetics PassiveBlock
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

install(FILES ${Synthetics_HDRS} DESTINATION include)
