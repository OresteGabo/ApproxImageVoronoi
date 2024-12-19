# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "ApproxImageVoronoi_autogen"
  "CMakeFiles/ApproxImageVoronoi_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ApproxImageVoronoi_autogen.dir/ParseCache.txt"
  )
endif()
