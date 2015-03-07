/*
 *  Prints a histogram of characters frequencies.
 *
 *  Copyright (C) 2007 Efstathios Chatzikyriakidis (contact@efxa.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* standard headers. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* basic defines. */
#define MAX_SYMS  50     /* the maximum `SYM_HIST' to print. */
#define NEW_LINE  '\n'   /* the newline character. */
#define SYM_HIST  '*'    /* the histogram symbol. */
#define ASCII_STR 'a'    /* ascii start character. */
#define ASCII_END 'z'    /* ascii end character. */

/* calculate the size of the array. */
#define MAX_SIZE ((ASCII_END - ASCII_STR) + 1)

/* type definitions. */

/* a boolean enumeration. */
typedef enum { false, true } bool;

/* a const pointer which points to const char. */
typedef const char *const unique;

/* global messages. */
static unique isnt_between_str = "No character found between: ";

/* function prototypes. */
void zero_array (int array[], int length);
int find_max (int array[], int length);
void init_array (int array[], int length, int number);
void print_frq (int array[], int length, int max_frq);

void read_chars (int array[]);
bool is_between (int symbol);
void print_sym (int times);

/* main function. */
int
main (void)
{
  /* array for the frequency of chars. */
  int chars_frequency[MAX_SIZE];

  /* maximum fequency; */
  int max_frq;

  /* zero the array (fill it with 0). */
  zero_array (chars_frequency, MAX_SIZE);

  /* read characters from stdin
     and store the frequencies. */
  read_chars (chars_frequency);

  /* find maximum frequency. */
  max_frq = find_max (chars_frequency, MAX_SIZE);

  /* if none chars read between `ASCII_STR' - `ASCII_END'. */
  if (!max_frq)
    {
      printf ("%s", isnt_between_str);
      printf ("%c-%c.", ASCII_STR, ASCII_END);
      printf ("%c", NEW_LINE);
      return 1;
    }

  /* print histogram info. */
  print_frq (chars_frequency, MAX_SIZE, max_frq);

  return EXIT_SUCCESS;
}

/* zero the array (fill with 0). */
void
zero_array (int array[], int length)
{
  init_array (array, length, 0);
}

/* init the array (fill with `number'). */
void
init_array (int array[], int length, int number)
{
  /* index for the loop. */
  int i;

  for (i = 0; i < length; i++)
    array[i] = number;
}

/* checks to see if the symbols are
   between `ASCII_STR' - `ASCII-END'. */
bool
is_between (int symbol)
{
  if (symbol >= ASCII_STR && symbol <= ASCII_END)
    return true;

  /* non `ASCII_STR' - `ASCII-END' char. */
  return false;
}

/* read all `ASCII_STR' - `ASCII-END' chars
   from stdin and increase their frequency. */
void
read_chars (int array[])
{
  /* current character. */
  int symbol;

  /* read only chars between `ASCII_STR' - `ASCII-END'. */
  while ((symbol = getchar ()) != EOF)
    if (is_between (symbol))
      ++array[symbol - ASCII_STR];

  /* EOF character found. */
}

/* print the frequencies for each
   `ASCII_STR' - `ASCII-END' char. */
void
print_frq (int array[], int length, int max_frq)
{
  int i;        /* index for the loop. */
  int sym_len;  /* the length of `SYM_HIST'. */

  /* print info. */
  for (i = 0; i < length; i++)
    {
      printf ("%c: %4d : ", i + ASCII_STR, array[i]);

      /* `max_frq' must be positive. */
      assert (max_frq != 0);

      /* calculate number of `SYM_HIST' to print. */
      sym_len = array[i] * MAX_SYMS / max_frq;

      /* check some exceptions. */
      if (array[i] > 0)
        {
          if (sym_len <= 0) sym_len = 1;
        }
      else
        sym_len = 0;

      /* print symbol `SYM_HIST' `sym_len' times. */
      print_sym (sym_len);

      printf ("%c", NEW_LINE);
    }
}

/* print `times' times
   the `SYM_HIST' char. */
void
print_sym (int times)
{
  /* index for the loop. */
  int i;

  for (i = 0; i < times; i++)
    printf ("%c", SYM_HIST);
}

/* search the array in order to
   find the maximum frequency. */
int
find_max (int array[], int length)
{
  int i;        /* index for the loop. */
  int max_frq;  /* maximum frequency; */

  /* assume max the first frq. */
  max_frq = array[0];

  /* search and return the maximum. */
  for (i = 1; i < length; i++)
    if (max_frq < array[i])
      max_frq = array[i];

  return max_frq;
}
