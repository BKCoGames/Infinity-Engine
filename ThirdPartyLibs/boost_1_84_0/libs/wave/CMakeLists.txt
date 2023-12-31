# Generated by `boostdep --cmake wave`
# Copyright 2020, 2021 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.8...3.20)

project(boost_wave VERSION "${BOOST_SUPERPROJECT_VERSION}" LANGUAGES CXX)

add_library(boost_wave
  src/instantiate_re2c_lexer.cpp
  src/token_ids.cpp
  src/instantiate_defined_grammar.cpp
  src/instantiate_cpp_literalgrs.cpp
  src/instantiate_cpp_exprgrammar.cpp
  src/instantiate_has_include_grammar.cpp
  src/instantiate_predef_macros.cpp
  src/instantiate_re2c_lexer_str.cpp
  src/instantiate_cpp_grammar.cpp
  src/wave_config_constant.cpp

  src/cpplexer/re2clex/aq.cpp
  src/cpplexer/re2clex/cpp_re.cpp
)

add_library(Boost::wave ALIAS boost_wave)

target_include_directories(boost_wave PUBLIC include)

target_link_libraries(boost_wave
  PUBLIC
    Boost::assert
    Boost::concept_check
    Boost::config
    Boost::core
    Boost::filesystem
    Boost::format
    Boost::iterator
    Boost::lexical_cast
    Boost::mpl
    Boost::multi_index
    Boost::optional
    Boost::pool
    Boost::preprocessor
    Boost::serialization
    Boost::smart_ptr
    Boost::spirit
    Boost::static_assert
    Boost::throw_exception
    Boost::type_traits
)

target_compile_features(boost_wave PUBLIC cxx_std_11)

target_compile_definitions(boost_wave
  PUBLIC BOOST_WAVE_NO_LIB
  PRIVATE BOOST_WAVE_SOURCE
)

if(BUILD_SHARED_LIBS)
  target_compile_definitions(boost_wave PUBLIC BOOST_WAVE_DYN_LINK)
else()
  target_compile_definitions(boost_wave PUBLIC BOOST_WAVE_STATIC_LINK)
endif()

if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt")

  add_subdirectory(test)

endif()

