
file(GLOB_RECURSE SRCS "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")

add_library(${BOOSTSSL_TARGET} ${SRCS} ${HEADERS})
target_link_libraries(${BOOSTSSL_TARGET} ${UTILITIES_TARGET} Boost::system Boost::filesystem
Boost::log Boost::chrono Boost::iostreams Boost::thread OpenSSL::SSL OpenSSL::Crypto)