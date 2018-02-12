#
# Сборка текстового редактора на основе wxWidgets
#

cmake_minimum_required( VERSION 2.8.12 )
project( EveRest )
SET( EXEC_NAME everest )
SET( SRC_DIR "${CMAKE_SOURCE_DIR}/src" )

SET( evCMAKES "${CMAKE_SOURCE_DIR}/cmakes" )
SET( WX_SRC_DIR "${CMAKE_SOURCE_DIR}/3rdparty/wxWidgets" )
SET( WX_LIB_DIR "${CMAKE_SOURCE_DIR}/3rdparty/staticlib" )
SET( BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE )
link_directories( "${WX_LIB_DIR}/lib" )

# проверочная сборка с параметром -DTRY=1
if( ${TRY} )
  SET( SRC_FILES ${SRC_DIR}/richtext.cpp )
else()
SET( SRC_FILES
  ${SRC_DIR}/app.cpp
  ${SRC_DIR}/text.cpp
  ${SRC_DIR}/frame.cpp
  ${SRC_DIR}/fields.cpp
  ${SRC_DIR}/assets.rc )
endif()

SET( CMAKE_CXX_FLAGS "-D_FILE_OFFSET_BITS=64 -O2 -Wall -Wundef\
 -Wunused-parameter -Wno-ctor-dtor-privacy -Woverloaded-virtual"
)

## Установка параметров для сборки на Linux
if( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
  include( "${evCMAKES}/linux.cmake" )
else( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
  include( "${evCMAKES}/win32.cmake" )
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

add_executable( ${EXEC_NAME} ${SRC_FILES} )
target_link_libraries( ${EXEC_NAME} ${LIBS} )
