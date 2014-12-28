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
  ActorServo SHARED
  Actor/Servo.cpp
)

##############################################################################
# INSTALL 
##############################################################################
install(TARGETS PassiveHub
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

install(TARGETS ActorServo
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

##############################################################################
# TESTING
##############################################################################
enable_testing()

add_executable(test_load_components Tests/test_load_components.cpp)
target_link_libraries(test_load_components
  components
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_test(test_load_components test_load_components)

