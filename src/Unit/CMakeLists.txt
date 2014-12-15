cmake_minimum_required(VERSION 2.8)

##############################################################################
# DEFINE 
##############################################################################
set(Unit_SRCS
  Entity.cpp
  Component.cpp
  Orientation.cpp
)

set(Unit_HDRS
  Entity.hpp
  Component.hpp
  Orientation.hpp
)

set(Polycode_LIBS
  libPolycore
)

##############################################################################
# BUILD 
##############################################################################
add_library(
  unit STATIC
  ${Unit_SRCS} ${Unit_HDRS}
)

##############################################################################
# INSTALL 
##############################################################################
install(FILES ${Unit_HDRS} DESTINATION include/Unit)

##############################################################################
# TESTING
##############################################################################
enable_testing()

add_executable(test_unit_entity Tests/test_unit_entity.cpp)
target_link_libraries(test_unit_entity
  unit
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_executable(test_unit_orientation Tests/test_unit_orientation.cpp)
target_link_libraries(test_unit_orientation
  unit
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_executable(test_unit_component Tests/test_unit_component.cpp)
target_link_libraries(test_unit_component
  unit
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_test(test_unit_entity test_unit_entity)
add_test(test_unit_component test_unit_component)
add_test(test_unit_orientation test_unit_orientation)

