/*
  @file array_helpers.h
  @brief defines array helpers methods. These methods operates over
  multidimensional array of prices
*/
#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H
#include "character.h"
#include <stdbool.h>

#define CHARACTER_TYPES 4
#define CHARACTER_ALIGNMENTS 2
#define CHARACTER_COUNT 10

typedef Character CharacterList[CHARACTER_TYPES][CHARACTER_ALIGNMENTS];

/**
 * @brief Read an array of game characters from a file
 * @details
 *
 *  Each element is read from the file located at 'filepath'.
 *  The file must exist in disk and must have its contents in a sequence of
 *  lines, each with the following format:
 *
 *   [<char> <char>] <char[5]> life: <uint>, strength: <uint>, agility: <uint>
 *
 *  Those elements are copied into an array 'array'.
 *
 * @param array array which will contain the read data
 * @param filepath file with game characters data
 * @returns the number of registers readed
 */
unsigned int array_from_file(CharacterList array, const char *filepath);

/**
 * @brief Calculate the mean life of all alive characters
 * @param[in] array array with data
 */
float array_alive_mean_life(CharacterList array);

/**
 * @brief Write the content of the array into stdout.
 * @param[in] array array to dump in stdout
 */
void array_dump(CharacterList array);

#endif
