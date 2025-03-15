
project(Test_Unit)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

message(STATUS ${SOURCE_DIR})

set(HEADERS
 ${HEADER_DIR}/Test.h
)
set(SOURCES
${SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME}
${SOURCES}
${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    KT_Library
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Test")