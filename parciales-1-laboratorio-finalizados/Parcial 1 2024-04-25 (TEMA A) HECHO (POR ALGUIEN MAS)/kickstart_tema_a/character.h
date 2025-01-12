/*
  @file character.h
  @brief Defines character information
*/

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <stdbool.h> 
#include <stdio.h>

#define CHARACTER_NAME_LENGTH 5

#define EXPECTED_ATTRIBUTE_FORMAT "[%c %c] "

typedef enum
{
    good,
    evil
} alignment_t;

typedef enum
{
    physical,
    agile,
    tank,
    magic
} charttype_t;

typedef enum
{
    alice, mario, lenny, eliza, eddie, frank, nadia, oscar, bella, yoshi
} name_t;

#define CHARACTER_COUNT 10

extern char* NAMES[];


/** @brief Type used to represent character data.*/
typedef struct _character
{
    name_t name;            // The name of the character
    unsigned int life;      // life must be between [0, 100]
    unsigned int strength;  // strength must be between [1, 10]
    unsigned int agility;   // agility must be between [1, 10]
    alignment_t alignment;  // alignment must be 'good' or 'evil'
    bool alive;             // alive if life > 0

} Character;

/**
 * @brief Creates a Character instance from a file.
 * @details
 *
 *  Reads from a file pointer and creates a Character instance from it.
 *  Each line of the file must have the following format:
 *     life: <uint>, strength: <uint>, agility: <uint>
 *
 * @param file pointer to a file containing Character data
 * @param name the previosly readed name of the character, the value is used to
 *             fill the Character structure
 * @param alignment the previously readed alignment of the character, the value
 *                  is used to fill the Character structure
 * @return a Character instance
 */
Character character_from_file_line(FILE *file, name_t name, alignment_t alignment);

/**
 * @brief Reads a name from an open file and transforms it to a name_t value
 * @details
 *
 *  Reads from a file pointer a string and transforms it to the corresponding
 *  name_t value or aborts with an error.
 *  It spect the following format:
 *     <char[5]>
 *
 * @param file pointer to a file containing a name string
 * @return a name_t value corresponding to the name tha was readed
 */
name_t read_character_name(FILE*file);

#endif  // _CHARACTER_H
