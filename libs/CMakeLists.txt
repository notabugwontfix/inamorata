set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)

# doctest
set(DOCTEST_NO_INSTALL ON CACHE INTERNAL "" FORCE)
add_subdirectory(doctest)

# yaml-cpp
set(YAML_BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)
set(YAML_CPP_BUILD_CONTRIB OFF CACHE INTERNAL "" FORCE)
set(YAML_CPP_BUILD_TOOLS OFF CACHE INTERNAL "" FORCE)
set(YAML_CPP_FORMAT_SOURCE OFF CACHE INTERNAL "" FORCE)
add_subdirectory(yaml-cpp)
