set(CMAKE_BUILD_TYPE Debug CACHE STRING "Debug Release ReleaseWithDebug MinRelSize")
set(CMAKE_INSTALL_PREFIX Install CACHE PATH "default install dir")
option(BUILD_SHARED_LIBS "If present and true, this will cause all libraries to be built shared unless the library was explicitly added as a static library." OFF)

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(USE_WIN_MULTI_THREAD_DLL "Enable STATIC CRT in Windows system"  OFF)
set(USE_SANITIZER "" CACHE STRING "Compile with a sanitizer. Options are: Address, Memory, MemoryWithOrigins, Undefined, Thread, Leak, 'Address;Undefined'")

option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
option(ENABLE_INCLUDE_WHAT_YOU_USE "Enable static analysis with include-what-you-use" OFF)
option(ENABLE_TEST "" OFF)
option(CODE_COVERAGE  "" OFF)
option(ENABLE_EXAMPLE "" OFF)
option(ENABLE_DOXYGEN "" OFF)
option(ENABLE_CLANG_FORMAT "" OFF)
