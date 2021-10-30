set(LIBRARY_TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE SOURCES "*/src/*.cc")
file(GLOB_RECURSE HEADERS "*/include/*.h")
file(GLOB_RECURSE PUBLIC_HDRS "api/include/quicplus/*.h")
configure_file(api/src/version.cc.in api/src/version.cc @ONLY)

add_library(
  ${LIBRARY_TARGET_NAME} "${SOURCES}" "${HEADERS}"
                         "${CMAKE_CURRENT_BINARY_DIR}/api/src/version.cc")
add_library(${PROJECT_NAME}::api ALIAS ${LIBRARY_TARGET_NAME})
# must have "" for PUBLIC_HDRS otherwise installed to /quicplus/api.h and got
# permission error in github action
set_target_properties(
  ${LIBRARY_TARGET_NAME} PROPERTIES VERSION ${PROJECT_VERSION} PUBLIC_HEADER
                                                               "${PUBLIC_HDRS}")

# PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/conn/include>"
# <conn/conn.h> cannot be found in header file but can be found in cc file becasue 
# unit test and example needs those includes so it must be as public
target_include_directories(
  ${LIBRARY_TARGET_NAME}
  PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/api/include>"
         "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/conn/include>"
         "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/common/include>"
         "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

install(
  TARGETS ${LIBRARY_TARGET_NAME}
  EXPORT ${PROJECT_NAME}
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT runtime
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
          COMPONENT runtime
          NAMELINK_COMPONENT dev # Requires CMake 3.12 or later
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT dev
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}"
                COMPONENT dev)

if(ENABLE_TEST)
  add_subdirectory(conn/ut)
  add_subdirectory(api/ut)
endif()

message(
  STATUS "Created target ${LIBRARY_TARGET_NAME} for  export ${PROJECT_NAME}.")
