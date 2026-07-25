cmake_minimum_required(VERSION 3.15)

project(IbanezTubeScreamer VERSION 1.0.0 LANGUAGES C CXX) 

# ==========================================
# CONFIGURAÇÃO ESPECÍFICA PARA LINUX
# ==========================================
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    pkg_check_modules(WEBKIT REQUIRED webkit2gtk-4.1) 
    pkg_check_modules(SOUP REQUIRED libsoup-3.0)

    include_directories(${GTK3_INCLUDE_DIRS} ${WEBKIT_INCLUDE_DIRS} ${SOUP_INCLUDE_DIRS})
    link_libraries(${GTK3_LIBRARIES} ${WEBKIT_LIBRARIES} ${SOUP_LIBRARIES})
endif()

# ==========================================
# DEFINIÇÕES GLOBAIS DO JUCE
# ==========================================
set(JUCE_WEB_BROWSER 0 CACHE INTERNAL "")
set(JUCE_USE_CURL 0 CACHE INTERNAL "")
set(JUCE_VST3_CAN_REPLACE_VST2 0 CACHE INTERNAL "")

# Adiciona o JUCE ao projeto (mantendo o seu caminho relativo)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../JUCE" "${CMAKE_CURRENT_BINARY_DIR}/JUCE")

# Configura o seu componente de áudio
juce_add_plugin(IbanezTubeScreamer
    COMPANY_NAME "Lavbella"
    PLUGIN_MANUFACTURER_CODE MPlg
    PLUGIN_CODE TScr
    FORMATS CLAP VST3                   
    PRODUCT_NAME "Paudiog01"
    IS_SYNTH FALSE                      
)

# Arquivos de código
target_sources(IbanezTubeScreamer PRIVATE
    PluginProcessor.h
    PluginProcessor.cpp
    PluginEditor.cpp   
    PluginEditor.h  
)

# Vincula as bibliotecas do JUCE (Lista Completa e Correta)
target_link_libraries(IbanezTubeScreamer PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_data_structures
    juce::juce_dsp
    juce::juce_gui_basics
)

target_compile_definitions(IbanezTubeScreamer PUBLIC
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

# ==========================================
# CONFIGURAÇÃO DE CÓPIA PARA PASTA PERSONALIZADA
# ==========================================
# if(WIN32)
#     # Copia o ficheiro Paudiog01.vst3 diretamente para a pasta que indicou
#     add_custom_command(TARGET IbanezTubeScreamer POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E make_directory "C:/audioplugins/MeusVST3"
#         COMMAND ${CMAKE_COMMAND} -E copy 
#         "${CMAKE_CURRENT_BINARY_DIR}/IbanezTubeScreamer_artefacts/Release/Paudiog01.vst3"
#         "C:/audioplugins/MeusVST3/Paudiog01.vst3"
#         COMMENT "A copiar o ficheiro .VST3 do VST3 para C:/audioplugins/MeusVST3...")
# endif()