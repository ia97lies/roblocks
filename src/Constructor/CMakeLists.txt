cmake_minimum_required(VERSION 2.8)

##############################################################################
# DEFINE 
##############################################################################
set(Constructor_SRCS
  FileManager.cpp
  SelectorDisplay.cpp
  Display.cpp
  Robot.cpp
)

set(Constructor_HDRS
  FileManager.hpp
  SelectorDisplay.hpp
  Display.hpp
  Robot.hpp
)

##############################################################################
# BUILD 
##############################################################################
add_library(
  constructor STATIC
  ${Constructor_SRCS} ${Constructor_HDRS}
)

add_library(
  RobotLua SHARED
  RobotLua.cpp
)

##############################################################################
# INSTALL 
##############################################################################
install(TARGETS RobotLua
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

##############################################################################
# TESTING
##############################################################################
enable_testing()

add_executable(test_robot Tests/test_robot.cpp)
target_link_libraries(test_robot
  synthetics
  constructor
  components
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_test(test_robot test_robot)
