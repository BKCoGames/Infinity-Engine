//
// Created by KiiroiSenko on 12/23/2023.
//

#pragma once

#include <boost/assert.hpp>


#ifndef INF_ENGINE_DEBUG_BUILD
// Macro that evaluates to 1 for Debug build and to 0 otherwise
#define INF_ENGINE_DEBUG_BUILD 0
#endif

#ifndef INF_ENGINE_RELEASE_BUILD
// Macro that evaluates to 1 for Release build and to 0 otherwise
#define INF_ENGINE_RELEASE_BUILD 0
#endif

#ifndef INF_ENGINE_DEVELOPMENT_BUILD
// Macro that evaluates to 1 for Development build and to 0 otherwise
#define INF_ENGINE_DEVELOPMENT_BUILD 0
#endif


/**
 * @brief Evaluate the expression only in Debug/development build. If it evaluates to false throw an error and abort the program with the given message
 */
#define IE_ASSERT_MSG(condition, message) BOOST_ASSERT_MSG(condition, message)

/**
 * @brief Evaluate the expression only in Debug/development build. If it evaluates to false throw an error and abort the program without a message
 */
#define IE_ASSERT(condition) BOOST_ASSERT(condition)

/**
 * @brief Force inline the function. equivalent to __forceinline
 */
#define IE_FORCEINLINE __forceinline

/**
 * @brief Make the function no discard. equivalent to [[nodiscard]]
 */
#define IE_NODISCARD [[nodiscard]]

/**
 * @brief Line break macro. equivalent to \n atm
 */
#define IE_LB "\n"