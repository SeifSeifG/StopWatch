/**
 * @file DEFS.h
 * @author Abdelrahman Samir
 * @date 2025-06-16
 * @brief GPIO (General Purpose Input/Output) driver interface for AVR microcontrollers. *
 * This file provides custom typedefs for fixed-width types,
 * logical constants (e.g., HIGH/LOW), and register-level bit manipulation macros.
 * It is designed to support low-level embedded software on AVR microcontrollers.
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef DEFS_H
#define DEFS_H

/** @name Fixed-width Integer Types
 *  Useful for portability and clarity when working with register-level code.
 *  @{
 */
typedef unsigned char      uint8;    /**< 8-bit unsigned integer */
typedef signed char        int8;     /**< 8-bit signed integer */
typedef unsigned short     uint16;   /**< 16-bit unsigned integer */
typedef signed short       int16;    /**< 16-bit signed integer */
typedef unsigned long      uint32;   /**< 32-bit unsigned integer */
typedef signed long        int32;    /**< 32-bit signed integer */
typedef unsigned long long uint64;   /**< 64-bit unsigned integer */
typedef signed long long   int64;    /**< 64-bit signed integer */
/** @} */

/** @name Floating Point Types
 *  Floating-point typedefs for mathematical operations.
 *  @{
 */
typedef float       float32;   /**< 32-bit floating-point number */
typedef double      float64;   /**< 64-bit floating-point number */
typedef long double float128;  /**< Extended precision floating-point number */
/** @} */

/** @brief Null pointer constant. */
#define NULL ((void*)0)

/** @brief Logical TRUE value (used as boolean). */
#define TRUE 1

/** @brief Logical FALSE value (used as boolean). */
#define FALSE 0

/** @brief Logical HIGH (typically 1 for digital pins). */
#define HIGH 1

/** @brief Logical LOW (typically 0 for digital pins). */
#define LOW 0

/** @brief Number of bits in a register (8-bit AVR). */
#define REGISTER_SIZE 8

/** @name Bit Manipulation Macros
 *  Convenience macros for setting, clearing, toggling, and testing bits in registers.
 *  @{
 */

/**
 * @brief Set a specific bit in a register.
 * @param REG The register to modify.
 * @param BIT The bit number to set.
 */
#define SET(REG,BIT)               (   REG |=  (1 << BIT) )

/**
 * @brief Clear a specific bit in a register.
 * @param REG The register to modify.
 * @param BIT The bit number to clear.
 */
#define CLEAR(REG,BIT)             (   REG &= ~(1 << BIT) )

/**
 * @brief Toggle a specific bit in a register.
 * @param REG The register to modify.
 * @param BIT The bit number to toggle.
 */
#define TOGGLE(REG,BIT)            (   REG ^=  (1 << BIT) )

/**
 * @brief Check if a specific bit is set in a register.
 * @param REG The register to check.
 * @param BIT The bit number to check.
 * @return Non-zero if the bit is set, zero otherwise.
 */
#define IS_SET(REG, BIT)           ( REG & (1 << BIT) )

/**
 * @brief Check if a specific bit is clear.
 * @param REG The register to check.
 * @param BIT The bit number to check.
 * @return Non-zero if the bit is clear, zero otherwise.
 */
#define IS_CLEAR(REG, BIT)         (~( REG & (1 << BIT) ))

/**
 * @brief Apply a bitmask to a register with new data.
 * @param REG The register to modify.
 * @param MUSK The bitmask to preserve bits.
 * @param DATA The new data to apply to bits not masked.
 */
#define MUSK_REG(REG, MUSK, DATA)  ( REG |= ( REG & MUSK ) | ( DATA & ~(MUSK)) )

/**
 * @brief Set specific bits in a register.
 * @param REG The register to modify.
 * @param BITS The bits to set.
 */
#define SET_REG(REG, BITS)         ( REG |= BITS )

/**
 * @brief Clear specific bits in a register.
 * @param REG The register to modify.
 * @param BITS The bits to clear.
 */
#define CLEAR_REG(REG, BITS)       ( REG &= ~(BITS) )


/** @} */ // end of Bit Manipulation Macros

#endif // DEFS_H
