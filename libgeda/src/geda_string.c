/* gEDA - GPL Electronic Design Automation
 * libgeda - gEDA's library
 * Copyright (C) 1998, 1999, 2000 Kazu Hirata / Ales Hvezda
 * Copyright (C) 1998-2010 Ales Hvezda
 * Copyright (C) 1998-2010 gEDA Contributors (see ChangeLog for details)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include <config.h>

#include <stdio.h>
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include "libgeda_priv.h"

/*! \brief count the lines of a text string
 *  \par Function Description
 *  This function just counts the number of lines that are
 *  in the \a string.

 *  \param [in] string  text string to count the lines
 *  \return the number of lines
 */
int
o_text_num_lines(const char *string)
{
  int line_count = 0;
  const gchar *aux;
  gunichar current_char;

  g_return_val_if_fail (string != NULL, 0);

  /* if it's not null, then we have at least one line */
  line_count++;
  /* Count how many \n are in the string */
  aux = string;
  while (aux && ((gunichar) (*aux) != 0) ) {
    current_char = g_utf8_get_char_validated(aux, -1);
    if (current_char == '\n')
      line_count++;
    aux = g_utf8_find_next_char(aux, NULL);
  }

  return (line_count);
}

/*! \brief Remove the ending newline
 *
 *  This function removes the ending newline from the string. If no newline
 *  exists at the end of the string, this function returns the passed in
 *  string.
 *
 *  This function modifies the string in place, so statically allocated strings
 *  cannot be passed to this function.
 *
 *  \param [in,out] string the input UTF-8 string
 *  \return the string with no ending newline
 */
gchar*
geda_string_remove_ending_newline (gchar *string)
{
  glong length;

  g_return_val_if_fail (string != NULL, NULL);

  length = g_utf8_strlen (string, -1);

  if (length > 0) {
    gchar *last_char = g_utf8_offset_to_pointer (string, length - 1);

    if ((*last_char == '\n') || (*last_char == '\r')) {
      *last_char = '\0';
    }
  }

  return string;
}

/*! \brief Gets the first line of the string
 *
 *  This function modifies the string in place, so statically allocated strings
 *  cannot be passed to this function.
 *
 *  \param [in,out] string the input UTF-8 string, NUL terminated
 *  \return the first line of the string with no ending newline
 */
gchar*
geda_string_get_first_line (gchar *string)
{
  gchar *iter = string;

  g_return_val_if_fail (string != NULL, NULL);

  while ((iter != NULL) && (*iter != '\0')) {
    if ((*iter == '\n') || (*iter == '\r')) {
      *iter = '\0';
      break;
    }

    iter = g_utf8_find_next_char (iter, NULL);
  }

  return string;
}

/*! \todo Finish function documentation!!!
 *  \brief
 *  \par Function Description
 *
 */
/* the delimiter is what is passed in or spaces */
/* count starts at zero */
char *u_basic_breakup_string(char *string, char delimiter, int count)
{
  int i=0, j=0;
  int internal_counter=0;
  int done=FALSE;
  char *return_value;

  g_return_val_if_fail (string != NULL, NULL);

  /* skip over any leading white space */
  while(string[i] == ' ' && !string[i]) {
    i++;
  }

  /* Allocate space for temp string storage (+1 for null character) */
  return_value = g_malloc(sizeof(char)*(strlen(string) + 1));

  while(!done) {

    /* oops, ran out of string before we found what we were */
    /* looking for */
    if (i > strlen(string)) {
      g_free(return_value);
      return(NULL);
    }

    /* skip over any leading white space */
    while(string[i] == ' ' && string[i] != '\0') {
      i++;
    }

    j = 0;

    /* Old forgiving parsing */
    /*		while(string[i] != ',' && string[i] != ';' && */
    /*		      string[i] != ' ' && string[i] != '\0') {*/

    while(string[i] != delimiter && string[i] != '\0') {
      return_value[j] = string[i];
      i++; j++;
    }

    if (internal_counter == count)  {
      done = TRUE;
    } else {
      internal_counter++;
      i++; /* skip the offending character */
    }
  }

  return_value[j] = '\0';
  return(return_value);
}
