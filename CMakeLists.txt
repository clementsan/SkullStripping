PROJECT(SkullStripping) 

cmake_minimum_required(VERSION 2.6)

FIND_PACKAGE(ITK) 
IF(ITK_FOUND)
  INCLUDE(${ITK_USE_FILE}) 
ELSE(ITK_FOUND)
  MESSAGE(FATAL_ERROR "ITK not found. Please set ITK_DIR.") 
ENDIF(ITK_FOUND) 

FIND_PACKAGE(GenerateCLP) 
IF(GenerateCLP_FOUND)
  INCLUDE(${GenerateCLP_USE_FILE}) 
ELSE(GenerateCLP_FOUND)
  MESSAGE(FATAL_ERROR "GenerateCLP not found. Please set GenerateCLP_DIR.") 
ENDIF(GenerateCLP_FOUND) 

set(SkullStripping_SOURCE main.cxx)
GENERATECLP(SkullStripping_SOURCE main.xml)

ADD_EXECUTABLE(SkullStripping ${SkullStripping_SOURCE})
TARGET_LINK_LIBRARIES(SkullStripping ${ITK_LIBRARIES})

