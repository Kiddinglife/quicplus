cmake_minimum_required(VERSION 3.21)
file(READ "version.txt" ProjectVersion)

project(
  quicplus
  VERSION ${ProjectVersion}
  HOMEPAGE_URL https://github.com/Kiddinglife/quicplus
  DESCRIPTION
    "QuicPlus is an open-source implementation of QUIC Protocol polished for Game Development"
)

find_package(spdlog CONFIG REQUIRED)
find_package(Threads REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(GNUInstallDirs)
include(Settings)
include(PreventInSourceBuilds)
include(CompilerWarnings)
set_project_warnings(*)
include(Sanitizers)
if(NOT BUILD_SHARED_LIBS AND USE_SANITIZER STREQUAL "")
  include(link-time-optimization)
  link_time_optimization()
endif()
if(CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang" OR CMAKE_CXX_COMPILER_ID
                                                     MATCHES "(Apple)?[Cc]lang")
  # clang supports sanitizer only with Release build type
  set(USE_SANITIZER "$<$<CONFIG:Debug>:>")
  file(
    GENERATE
    OUTPUT USE_SANITIZER.genexpr
    CONTENT $<$<CONFIG:Debug>:>)
endif()
if(MSVC)
  # only gcc/clang compiler supports code cov.
  set(CODE_COVERAGE OFF)
endif()
include(code-coverage)
add_code_coverage_all_targets()

# Generate compile_commands.json to make it easier to work with clang based
# tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD
    17
    CACHE STRING "The C++ standard to use")
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_RELEASE_POSTFIX "_r")

# Setup CMAKE_MSVC_RUNTIME_LIBRARY no matter it is msbuild or win-version
# clang/gcc
set(CMAKE_MSVC_RUNTIME_LIBRARY
    "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<BOOL:${USE_WIN_MULTI_THREAD_DLL}>:DLL>"
)

if(ENABLE_CLANG_FORMAT)
  include(ClangFormat)
  file(GLOB_RECURSE examplecpp ${CMAKE_SOURCE_DIR}/example/*.cc)
  file(GLOB_RECURSE examplehpp ${CMAKE_SOURCE_DIR}/example/*.h)
  file(GLOB_RECURSE testcpp ${CMAKE_SOURCE_DIR}/test/*.cc)
  file(GLOB_RECURSE testhpp ${CMAKE_SOURCE_DIR}/test/*.h)
  file(GLOB_RECURSE srccpp ${CMAKE_SOURCE_DIR}/src/*.cc)
  file(GLOB_RECURSE srchpp ${CMAKE_SOURCE_DIR}/src/*.h)
  clang_format(
    clang-format
    ${examplecpp}
    ${examplehpp}
    ${testcpp}
    ${testhpp}
    ${srccpp}
    ${srchpp})
endif()

if(ENABLE_CLANG_TIDY AND NOT MSVC)
  # add_custom_target(clang-tidy COMMAND clang-tidy WORKING_DIRECTORY
  # ${CMAKE_CURRENT_SOURCE_DIR})
  set(CMAKE_CXX_CLANG_TIDY clang-tidy)
  set(CMAKE_C_CLANG_TIDY clang-tidy)
  # set(CMAKE_CXX_CLANG_TIDY clang-tidy;-fix) set(CMAKE_C_CLANG_TIDY
  # clang-tidy;-fix)
  message("CMAKE_C_CLANG_TIDY ${CMAKE_C_CLANG_TIDY}")
  message("CMAKE_CXX_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY}")
elseif()
  # msvc does not work with clang-tidy. reported a lots of errors plz use the
  # virtual sdutio's built-in code analysis feature
  unset(CMAKE_CXX_CLANG_TIDY)
  unset(CMAKE_C_CLANG_TIDY)
endif()

if(ENABLE_TEST)
  find_package(GTest REQUIRED)
  include(GoogleTest)
  enable_testing()
  # Add integration tests (unit tests for each library should be in each
  # sublibrary directory).
  add_subdirectory(test/fuzz)
  add_subdirectory(test/perf)
  add_subdirectory(test/sys)
  # include(CTest)
endif()

# Enable RPATH support for installed binaries and libraries
include(AddInstallRPATHSupport)
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_FULL_BINDIR}" LIB_DIRS
                          "${CMAKE_INSTALL_FULL_LIBDIR}")

if(ENABLE_EXAMPLE)
  add_subdirectory(example)
endif()
add_subdirectory(src)

# Create and install CMake configuration files for your project that are
# necessary to for other projects to call find_package(LibTemplateCMake).
#
# Note that it is extremely important to use exactly the project name while
# installing configuration files (you can use PROJECT_NAME variable to avoid any
# possible error). This is required to allow find_package() to properly look for
# the installed library in system path, in particular in Windows when the
# installation is performed in the default path.
#
# install_basic_package_files() comes with many input parameters to customize
# the configuration files. The parameters used in the following call provide
# basic versions of CMake configuration files. See install_basic_package_files()
# documentation found in ./cmake folder.
#
# Note that if your library depends from other libraries, you are probably
# required to used the install_basic_package_files() DEPENDENCIES option.
include(InstallBasicPackageFiles)
install_basic_package_files(
  ${PROJECT_NAME}
  VERSION
  ${PROJECT_VERSION}
  COMPATIBILITY
  AnyNewerVersion
  VARS_PREFIX
  ${PROJECT_NAME}
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
include(AddUninstallTarget)

# Add targets related to doxygen documention generation
add_subdirectory(doc)
