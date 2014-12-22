cmake_minimum_required(VERSION 2.8)

##############################################################################
# DEFINE 
##############################################################################
set(Compounds_SRCS
  Factory.cpp
)

set(Compounds_HDRS
  Factory.hpp
)

##############################################################################
# BUILD 
##############################################################################
add_library(
  compounds STATIC
  ${Compounds_SRCS} ${Compounds_HDRS}
)

add_library(
  PassiveHub SHARED
  Passive/Hub.cpp
)

##############################################################################
# INSTALL 
##############################################################################
install(TARGETS PassiveHub
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)

##############################################################################
# TESTING
##############################################################################
enable_testing()

add_executable(test_load_compounds Tests/test_load_compounds.cpp)
target_link_libraries(test_load_compounds
  compounds
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)

add_test(test_load_compounds test_load_compounds)

