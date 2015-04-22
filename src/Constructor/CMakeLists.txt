cmake_minimum_required(VERSION 2.8)

##############################################################################
# DEFINE 
##############################################################################
set(Constructor_SRCS
  Menu.cpp
  MenuEntry.cpp
  SelectorDisplay.cpp
  Display.cpp
  ContextMenu.cpp
  Robot.cpp
  Model.cpp
  CommandSetRoot.cpp
  CommandActivate.cpp
  CommandPlace.cpp
  CommandRotateInPlace.cpp
  CommandAdd.cpp
  CommandRemove.cpp
  History.cpp
)

set(Constructor_HDRS
  Menu.hpp
  MenuEntry.hpp
  SelectorDisplay.hpp
  Display.hpp
  ContextMenu.hpp
  Robot.hpp
  Model.hpp
  Command.hpp
  CommandNone.hpp
  CommandSetRoot.hpp
  CommandActivate.hpp
  CommandPlace.hpp
  CommandRotateInPlace.hpp
  CommandAdd.hpp
  CommandRemove.hpp
  History.hpp
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
  recorder
  showkeyhits
  components
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)
add_test(test_robot test_robot)

add_executable(test_command Tests/test_command.cpp)
target_link_libraries(test_command
  synthetics
  constructor
  recorder
  showkeyhits
  components
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)
add_test(test_command test_command)

add_executable(test_history Tests/test_history.cpp)
target_link_libraries(test_history
  synthetics
  constructor
  recorder
  showkeyhits
  components
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)
add_test(test_history test_history)

add_executable(test_model Tests/test_model.cpp)
target_link_libraries(test_model
  synthetics
  constructor
  recorder
  showkeyhits
  components
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)
add_test(test_model test_model)

add_executable(test_menu_entry Tests/test_menu_entry.cpp)
target_link_libraries(test_menu_entry
  constructor
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)
add_test(test_menu_entry test_menu_entry)

add_executable(test_menu Tests/test_menu.cpp)
target_link_libraries(test_menu
  constructor
  ${Polycode_LIBS}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
)
add_test(test_menu test_menu)

