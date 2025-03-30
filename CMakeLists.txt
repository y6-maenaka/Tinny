
cmake_minimum_required(VERSION 3.20)
project(TINNY CXX)

# C++20 を利用する設定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenSSL の検出
find_package(OpenSSL REQUIRED)
# Boost の必要なコンポーネントを追加 (例: chrono と system)
find_package(Boost REQUIRED COMPONENTS chrono system REQUIRED)

if(OpenSSL_FOUND)
  message(STATUS "Using OpenSSL ${OPENSSL_VERSION}")
endif()

if(Boost_FOUND)
  message(STATUS "Using Boost ${Boost_VERSION}")
endif()

# src 以下の全てのソースファイルを再帰的に検索
file(GLOB_RECURSE basic_source_files "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
if(NOT basic_source_files)
  message(WARNING "ソースファイルが見つかりませんでした: ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
endif()

# ライブラリ TINNY の作成
add_library(TINNY STATIC ${basic_source_files})
target_include_directories(TINNY PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${OPENSSL_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)

# run/tinny.cpp を実行ファイルとしてビルド (実行ファイルのターゲット名を TINNY_APP に変更)
add_executable(TINNY_APP "${CMAKE_CURRENT_SOURCE_DIR}/run/tinny.cpp")
target_include_directories(TINNY_APP PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(TINNY_APP PRIVATE 
  TINNY
  OpenSSL::SSL 
  OpenSSL::Crypto 
  Boost::chrono 
  Boost::system
)

set_target_properties(TINNY_APP PROPERTIES OUTPUT_NAME "Tinny")
