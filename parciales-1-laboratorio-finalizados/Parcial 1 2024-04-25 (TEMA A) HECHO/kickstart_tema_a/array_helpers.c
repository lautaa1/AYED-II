/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "character.h"

void array_dump(CharacterList array) {
  for (alignment_t alignment=good; alignment<CHARACTER_ALIGNMENTS; ++alignment) {
    for (charttype_t charttype=physical; charttype < CHARACTER_TYPES; ++charttype) {
      Character character = array[charttype][alignment];

      char *str_alignment = (character.alignment == good) ? "Good" : "Evil";
      char *str_alive = (character.alive) ? "Yes" : "Nope";

      fprintf(stdout,
              "Character '%s': Life=%u/100, Strength=%u/10, Agility=%u/10, "
              "alignment='%s', Alive='%s'\n",
              NAMES[character.name], character.life, character.strength,
              character.agility, str_alignment, str_alive);
    }
  }
}

float array_alive_mean_life(CharacterList array){
  float prom = 0.0;
  unsigned int count = 0u;
  for (unsigned int i = physical; i <= magic; i++){
    for (unsigned int j = good; j <= evil; j++){
      if (array[i][j].alive == true){
        count = count + 1;
        prom += array[i][j].life;
      }
    }
  }
  prom = prom / count;
  return prom;
}


unsigned int array_from_file(CharacterList array, const char *filepath) {
  FILE *file = NULL;

  // check if file exists
  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  // read the file
  unsigned int readed = 0;
  while (!feof(file) && readed < 8) {
    charttype_t charttype;
    alignment_t alignment;

    char s_charttype, s_alignment;
    int res=fscanf(file, "[%c %c]\n" , &s_charttype, &s_alignment);
    if (res != 2) {
        fprintf(stderr, "Error reading type and alignment.\n");
        exit(EXIT_FAILURE);
    }
    /* convertir la letra de `s_charttype` en un valor `charttype_t` y asignarlo
     * a la variable  `charttype`:
     *
     * 'a' --> agile
     * 'p' --> physical
     * 't' --> tank
     * 'm' --> mage
     *
     */
    if (s_charttype == 'a'){
      charttype = agile;
    }else if (s_charttype == 'p'){
      charttype = physical;
    }else if (s_charttype == 't'){
      charttype = tank;
    }else if (s_charttype == 'm'){
      charttype = magic;
    } else {
      fprintf(stderr, "Error Unknown type.\n");
      exit(EXIT_FAILURE);
    }
    /* convertir la letra de `s_alignment` en un valor `aligment_t` y asignarlo
     * a la variable  `alignment`:
     *
     * 'g' --> good
     * 'e' --> evil
     *
     */
    if (s_alignment == 'g'){
      alignment = good;
    }else if (s_alignment == 'e'){
      alignment = evil;
    } else{
      fprintf(stderr, "Error Unknown alignment.\n");
      exit(EXIT_FAILURE);
    }

    // Reads the name and obtains an name_t value
    name_t name = read_character_name(file);

    Character character = character_from_file_line(file, name, alignment);

    /* COMPLETAR: Almacenar en la tabla*/
    array[charttype][character.alignment] = character;
    ++readed;
  }
  /* COMPLETAR SI ES NECESARIO CON ALGUNA VERIFICACIÓN FINAL */

  // close the file
  fclose(file);

  return readed;
}

/*
gcc -Wall -Werror -Wextra -pedantic -std=c99 -g -c array_helpers.c character.c main.c
gcc -Wall -Werror -Wextra -pedantic -std=c99 array_helpers.o character.o main.o -g -o load_characters

./load_characters input/valid.in
*/
