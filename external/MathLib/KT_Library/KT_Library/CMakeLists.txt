project(KT_Library)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


set(HEADERS
 ${HEADER_DIR}/KT_Array.h
 ${HEADER_DIR}/KT_Vector.h
 ${HEADER_DIR}/KT_List.h
 ${HEADER_DIR}/KT_Algorithm.h
 ${HEADER_DIR}/KT_Container.h
 ${HEADER_DIR}/KT_IntrusiveList.h
 ${HEADER_DIR}/KT_InsertionSort.h
 ${HEADER_DIR}/KT_BubbleSort.h
 ${HEADER_DIR}/KT_FusionSort.h
 ${HEADER_DIR}/KT_VectorND.h
 ${HEADER_DIR}/KT_Math_Algorithm.h
 ${HEADER_DIR}/KT_Matrix.h
 ${HEADER_DIR}/KT_Math.h
)
set(SOURCES
${SOURCE_DIR}/KT_Algorithm.cpp
)

add_library(${PROJECT_NAME}

${SOURCES}
${HEADERS}
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")