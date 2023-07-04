target_sources("${PROJECT_NAME}"
        PRIVATE
        PluginEditor.cpp
        BASPluginProcessor.cpp)

target_include_directories("${PROJECT_NAME}"
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/VolumeComponents
        ${CMAKE_CURRENT_SOURCE_DIR}/LAF
        ${CMAKE_CURRENT_SOURCE_DIR}/MainComponents
        ${CMAKE_CURRENT_SOURCE_DIR}/DSP)

add_subdirectory(VolumeComponents)
add_subdirectory(MainComponents)
add_subdirectory(LAF)
add_subdirectory(DSP)