# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  [[CMakeFiles\flashcards_autogen.dir\AutogenUsed.txt]]
  [[CMakeFiles\flashcards_autogen.dir\ParseCache.txt]]
  "flashcards_autogen"
  )
endif()
