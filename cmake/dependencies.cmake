include(FetchContent)

find_package(OpenCV REQUIRED core imgcodecs imgproc)

set(PUGIXML_HEADER_ONLY ON CACHE BOOL "")
set(TLCT_HEADER_ONLY ON CACHE BOOL "")
set(TLCT_PUGIXML_PATH "${PROJECT_SOURCE_DIR}/thirdparty/pugixml-1.14")
add_subdirectory(thirdparty/TLCT-0.10.2)
add_subdirectory(thirdparty/argparse-3.0)

if (MCA_BUILD_TESTS)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.14.0
    )

    set(BUILD_GMOCK OFF CACHE INTERNAL "" FORCE)
    set(GTEST_LINKED_AS_SHARED_LIBRARY 1 CACHE INTERNAL "" FORCE)
    set(gtest_force_shared_crt ON CACHE INTERNAL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    include(GoogleTest)
endif ()
