cmake_minimum_required(VERSION 3.5)
project(srv_service)

# Default to C99
if(NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 99)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra)
    add_compile_options("$<$<CONFIG:RELEASE>:-O2>" "$<$<CONFIG:DEBUG>:-g>")
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)

find_package(service_msg REQUIRED)

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
    "include/${PROJECT_NAME}/*.h"
    "include/${PROJECT_NAME}/*.hpp"
)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
)

add_library(${PROJECT_NAME}_lib SHARED ${SOURCES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}_lib PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

ament_target_dependencies(${PROJECT_NAME}_lib
                          rclcpp
                          rclcpp_components
                          service_msg)

install(
    TARGETS ${PROJECT_NAME}_lib EXPORT ${PROJECT_NAME}_lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

ament_export_targets(${PROJECT_NAME}_lib HAS_LIBRARY_TARGET)

rclcpp_components_register_node(${PROJECT_NAME}_lib PLUGIN "srv_service::SrvService" EXECUTABLE ${PROJECT_NAME})

ament_package()