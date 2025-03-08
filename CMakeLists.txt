cmake_minimum_required(VERSION 3.21)

# Nome do projeto e definição do tipo como DLL
project(SVCheat LANGUAGES CXX)

# Define o alvo da DLL
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(svcheat SHARED ${SOURCES})

# Define o diretório de inclusão
target_include_directories(svcheat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)

# Demoncore
FetchContent_Declare(
    demoncore
    GIT_REPOSITORY git@github.com:KingTimer12/demon-core.git
    GIT_BRANCH master
)
FetchContent_MakeAvailable(demoncore)

# Adiciona a dependência para a biblioteca libmem
target_link_libraries(svcheat PUBLIC demoncore d3d9)

set(DIRECTX_SDK_PATH "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)")

if (WIN32)
    include_directories("${DIRECTX_SDK_PATH}/Include")
    link_directories("${DIRECTX_SDK_PATH}/Lib/x64")
endif()

# Especifique que o código está sendo construído no Windows
if(WIN32)
    # Adiciona a dependência para a biblioteca windows.h
    # target_link_libraries(svcheat PUBLIC -luser32 -lkernel32)
    target_link_libraries(svcheat PUBLIC 
        user32.lib
        psapi.lib
        ntdll.lib
        shell32.lib
        d3d9.lib
    )
endif()

# Especifica o padrão da linguagem C++
set_target_properties(svcheat PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Define o diretório de destino dos arquivos binários
set_target_properties(svcheat PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)