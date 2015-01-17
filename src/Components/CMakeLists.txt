cmake_minimum_required(VERSION 2.8)

##############################################################################
# DEFINE 
##############################################################################
set(Components_SRCS
  Factory.cpp
)

set(Components_HDRS
  Factory.hpp
)

##############################################################################
# BUILD 
##############################################################################
add_library(
  components STATIC
  ${Components_SRCS} ${Components_HDRS}
)

add_library(
  PassiveHub SHARED
  Passive/Hub.cpp
)

add_library(
  ActiveServo SHARED
  Active/Servo.cpp
)

add_library(
  ActiveLinear SHARED
  Active/Linear.cpp
)

add_library(
  ActiveLight SHARED
  Active/Light.cpp
)

##############################################################################
# INSTALL 
##############################################################################
install(TARGETS PassiveHub
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

install(TARGETS ActiveServo
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

install(TARGETS ActiveLinear
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

install(TARGETS ActiveLight
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

##############################################################################
# TESTING
##############################################################################
enable_testing()

add_executable(test_factory Tests/test_factory.cpp)
target_link_libraries(test_factory
  components
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_test(test_factory test_factory)

add_executable(test_load_components Tests/test_load_components.cpp)
target_link_libraries(test_load_components
  components
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_test(test_load_components test_load_components)

