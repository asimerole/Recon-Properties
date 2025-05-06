# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\Properties-Recon_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Properties-Recon_autogen.dir\\ParseCache.txt"
  "Properties-Recon_autogen"
  )
endif()
