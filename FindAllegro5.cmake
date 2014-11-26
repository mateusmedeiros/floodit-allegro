# - Find allegro 5
# Find the native ALLEGRO 5 includes and library
#
#  ALLEGRO_INCLUDE_DIR - where to find allegro.h, etc.
#  ALLEGRO_LIBRARIES   - List of libraries when using allegro.
#  ALLEGRO_FOUND       - True if allegro found.


IF (ALLEGRO_INCLUDE_DIR)
  # Already in cache, be silent
  SET(ALLEGRO_FIND_QUIETLY TRUE)
ENDIF (ALLEGRO_INCLUDE_DIR)

FIND_PATH(ALLEGRO_INCLUDE_DIR allegro.h
  /usr/local/include/allegro5
  /usr/include/allegro5
  $ENV{MINGDIR}/include/allegro5
  ${CMAKE_SOURCE_DIR}/allegro/include/allegro5
)

set(VERSION_NUMBER "5.1")

if(UNIX AND NOT CYGWIN)
	exec_program(pkg-config ARGS "allegro-${VERSION_NUMBER} allegro_ttf-${VERSION_NUMBER} allegro_font-${VERSION_NUMBER} allegro_dialog-${VERSION_NUMBER} --libs" OUTPUT_VARIABLE ALLEGRO_LIBRARIES)
	IF (NOT ${ALLEGRO_LIBRARIES})
	    # FALL BACK TO 5.0
	    set(VERSION_NUMBER "5.0")
	    exec_program(pkg-config ARGS "allegro-${VERSION_NUMBER} allegro_ttf-${VERSION_NUMBER} allegro_font-${VERSION_NUMBER} allegro_dialog-${VERSION_NUMBER} --libs" OUTPUT_VARIABLE ALLEGRO_LIBRARIES)
	ENDIF (NOT ${ALLEGRO_LIBRARIES})
	# Check if any of these checks have found if so then cause failure)
	STRING(REGEX MATCH "not found" LIB_CHECK ${ALLEGRO_LIBRARIES})
	IF (${LIB_CHECK})
	    set(ALLEGRO_LIBRARIES "")
	ENDIF (${LIB_CHECK})
else(UNIX AND NOT CYGWIN)
	FIND_LIBRARY(ALLEGRO_LIBRARY
	NAMES allegro-5.0.0-monolith-static-mt
	allegro-5.0.1-monolith-static-mt
	allegro-5.0.2-monolith-static-mt
	allegro-5.0.3-monolith-static-mt
	allegro-5.0.4-monolith-static-mt
	allegro-5.0.5-monolith-static-mt
	allegro-5.0.6-monolith-static-mt
	allegro-5.0.7-monolith-static-mt
	allegro-5.0.8-monolith-static-mt
	allegro-5.0.9-monolith-static-mt
	allegro-5.0.10-monolith-static-mt
	allegro-5.0.11-monolith-static-mt
	allegro-5.0.12-monolith-static-mt
	allegro-5.0.13-monolith-static-mt
	allegro-5.0.14-monolith-static-mt
	allegro-5.0.15-monolith-static-mt
	allegro-5.1.0-monolith-static-mt
	PATHS /usr/lib /usr/local/lib $ENV{MINGDIR}/lib ${CMAKE_SOURCE_DIR}/allegro/lib)
	IF (NOT ${ALLEGRO_LIBRARY})
	ENDIF (NOT ${ALLEGRO_LIBRARIES})
endif(UNIX AND NOT CYGWIN)

IF (ALLEGRO_INCLUDE_DIR AND (ALLEGRO_LIBRARIES OR ALLEGRO_LIBRARY))
   SET(ALLEGRO_FOUND TRUE)
   SET( ALLEGRO_LIBRARIES ${ALLEGRO_LIBRARIES} )
   IF (ALLEGRO_LIBRARY)
     add_definitions(-DALLEGRO_STATICLINK)
     set(ALLEGRO_LIBRARIES ${ALLEGRO_LIBRARY})
   ENDIF(ALLEGRO_LIBRARY)
 ELSE (ALLEGRO_INCLUDE_DIR AND (ALLEGRO_LIBRARIES OR ALLEGRO_LIBRARY))
   SET(ALLEGRO_FOUND FALSE)
   SET( ALLEGRO_LIBRARIES )
 ENDIF (ALLEGRO_INCLUDE_DIR AND (ALLEGRO_LIBRARIES OR ALLEGRO_LIBRARY))

IF (ALLEGRO_FOUND)
   IF (NOT ALLEGRO_FIND_QUIETLY)
      MESSAGE(STATUS "Found Allegro 5: ${ALLEGRO_LIBRARIES}")
   ENDIF (NOT ALLEGRO_FIND_QUIETLY)
ELSE (ALLEGRO_FOUND)
   IF (ALLEGRO_FIND_REQUIRED)
      MESSAGE(STATUS "Looked for Allegro 5 libraries named ${ALLEGRO_NAMES}.")
      MESSAGE(FATAL_ERROR "Could NOT find Allegro 5 library")
   ENDIF (ALLEGRO_FIND_REQUIRED)
ENDIF (ALLEGRO_FOUND)

MARK_AS_ADVANCED(
  ALLEGRO_LIBRARIES
  ALLEGRO_INCLUDE_DIR
  )
