hunter_add_package(bcos-pbft)
find_package(bcos-framework CONFIG REQUIRED)
find_package(bcos-pbft CONFIG REQUIRED)
get_target_property(BCOS_PBFT_INCLUDE bcos-pbft::bcos-pbft INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${BCOS_PBFT_INCLUDE}/bcos-pbft)