cmake_minimum_required(VERSION 3.0)

project(message_with_encryption VERSION 0.1.0 LANGUAGES CXX)

option(FLATBUFFERS_AS_SHARED "Link flatbuffers as shared library" ON)
if(FLATBUFFERS_AS_SHARED)
	set(FLATBUFFERS_TARGET flatbuffers::flatbuffers_shared)
else()
	set(FLATBUFFERS_TARGET flatbuffers::flatbuffers)
endif()

find_package(OpenSSL REQUIRED)
find_package(Flatbuffers REQUIRED)
if(NOT TARGET flatbuffers::flatc)
	find_program(FLATC_PROGRAM flatc)
	add_executable(flatc IMPORTED GLOBAL)
	set_property(TARGET flatc PROPERTY IMPORTED_LOCATION ${FLATC_PROGRAM})
	add_executable(flatbuffers::flatc ALIAS flatc)
endif()

add_executable(${PROJECT_NAME} main.cpp message_generated.h)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} ${FLATBUFFERS_TARGET} OpenSSL::Crypto)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

add_custom_command(OUTPUT message_generated.h
	COMMAND flatbuffers::flatc ARGS --cpp --gen-object-api ${CMAKE_CURRENT_SOURCE_DIR}/message.fbs
	DEPENDS message.fbs
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
