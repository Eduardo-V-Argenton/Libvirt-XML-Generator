cmake_minimum_required(VERSION 3.10)
project(Libvirt-XML-Generator VERSION 0.0)

# Define C++ standard
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/elements/*.cpp" 
    "src/elements/devices/*.cpp"
)

# Cria o executável a partir dos arquivos fontes
add_executable(libvirt-xml-generator ${SOURCES})

# Find and link cxxopts
find_package(cxxopts REQUIRED)
target_link_libraries(libvirt-xml-generator cxxopts::cxxopts)
