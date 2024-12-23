cmake_minimum_required(VERSION 3.21)

# Nome do projeto e definição do tipo como DLL
project(SVCheat LANGUAGES CXX)

# Define o alvo da DLL
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_library(svcheat SHARED ${SOURCES})

# Define o diretório de inclusão
target_include_directories(svcheat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)

# Define a versão do libmem antes de baixar
set(LIBMEM_DOWNLOAD_VERSION "5.0.2")

# Download and set up libmem
FetchContent_Declare(libmem-config 
    URL "https://raw.githubusercontent.com/rdbo/libmem/config-v1/libmem-config.cmake" 
    DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_MakeAvailable(libmem-config)

set(CMAKE_PREFIX_PATH "${libmem-config_SOURCE_DIR}" "${CMAKE_PREFIX_PATH}")

# Find libmem package
find_package(libmem CONFIG REQUIRED)

# Adiciona a dependência para a biblioteca libmem
target_link_libraries(svcheat PUBLIC libmem::libmem)

# Especifique que o código está sendo construído no Windows
if(WIN32)
    # Adiciona a dependência para a biblioteca windows.h
    # target_link_libraries(svcheat PUBLIC -luser32 -lkernel32)
    target_link_libraries(svcheat PUBLIC 
        user32.lib
        psapi.lib
        ntdll.lib
        shell32.lib
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