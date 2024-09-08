cmake_minimum_required(VERSION 3.16)

project(AppAccountTools VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets  LinguistTools)
find_package(Qt6 ${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql Xml)

set(TranslationDir "${CMAKE_SOURCE_DIR}/src/langs")
file(MAKE_DIRECTORY ${TranslationDir})
set(TS_FILES "${TranslationDir}/en_GB.ts")

#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/Forms")

set(SOURCES_FORMS_DIR
    "${FORMS_DIR}/MngFormConfig.ui"
    "${FORMS_DIR}/mainwindow.ui"
    "${FORMS_DIR}/images.qrc"
)

#--From Root
set(MNG_FORMS_DIR "${CMAKE_SOURCE_DIR}/MngForms")

set(SOURCES_MNGFORMS_DIR
    "${MNG_FORMS_DIR}/MngFormConfig.cpp"
    "${MNG_FORMS_DIR}/MngFormConfig.h"
)

#--From Root
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

set(SOURCES_SRC_DIR
    main.cpp
    "${SRC_DIR}/mainwindow.h"
    "${SRC_DIR}/mainwindow.cpp"
)

#-- From SRC/Util
set(SRC_UTIL_DIR "${CMAKE_SOURCE_DIR}/src/Util")

set(SOURCES_SRC_UTIL_DIR
    "${SRC_UTIL_DIR}/ConfigXml.h"
    "${SRC_UTIL_DIR}/ConfigXml.cpp"
    "${SRC_UTIL_DIR}/DBConn.h"
    "${SRC_UTIL_DIR}/DBConn.cpp"
    "${SRC_UTIL_DIR}/DBUtil.h"
    "${SRC_UTIL_DIR}/DBUtil.cpp"
    "${SRC_UTIL_DIR}/MngLogFile.h"
    "${SRC_UTIL_DIR}/MngLogFile.cpp"
    "${SRC_UTIL_DIR}/ShowMsg.h"
    "${SRC_UTIL_DIR}/ShowMsg.cpp"
)

# Get rcc command path and put it in RCC
get_target_property(RCC
    Qt6::rcc
    IMPORTED_LOCATION
)

# qt_standard_project_setup()

include_directories(${SRC_DIR})
include_directories(${SRC_UTIL_DIR})
include_directories(${FORMS_DIR})
include_directories(${MNG_FORMS_DIR})

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})
qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})


# Add the executable
if (WIN32) 
    add_executable(AppAccountTools WIN32
        ${SOURCES_SRC_DIR}
        ${SOURCES_SRC_UTIL_DIR}
        ${SOURCES_FORMS_DIR}
        ${SOURCES_MNGFORMS_DIR}
    )
elseif(UNIX)
    add_executable(AppAccountTools
        ${SOURCES_SRC_DIR}
        ${SOURCES_SRC_UTIL_DIR}
        ${SOURCES_FORMS_DIR}
        ${SOURCES_MNGFORMS_DIR}
    )
endif()

# Add the target includes for MY_PROJECT 
target_include_directories(AppAccountTools PRIVATE ${SRC_DIR})
target_include_directories(AppAccountTools PRIVATE ${SRC_UTIL_DIR})
target_include_directories(AppAccountTools PRIVATE ${FORMS_DIR})
target_include_directories(AppAccountTools PRIVATE ${MNG_FORMS_DIR})

target_link_libraries(AppAccountTools
    Qt6::Widgets
    Qt6::Sql
    Qt6::Xml
)


# include(GNUInstallDirs)
# install(TARGETS AppAccountTools
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(AppAccountTools)
# endif()

