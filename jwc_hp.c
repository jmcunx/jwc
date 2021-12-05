/*
 * Copyright (c) 2003 ... 2020 2021
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/param.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <j_lib2.h>
#include <j_lib2m.h>

#include "jwc.h"

char *jwc_hp_rev="$Id: jwc_hp.c,v 3.5 2021/02/21 21:01:17 jmccue Exp $";
extern char *jwc_rev;
extern char *jwc_e_rev;
extern char *jwc_i_rev;

#define MSG_HELP_11 "print the number of bytes, words, and lines in files"

/*
 * show_brief_help() -- Display brief help info
 */
int show_brief_help(work_area *w)
{

  fprintf(w->out.fp, USG_MSG_USAGE, PROG_NAME);
  fprintf(w->out.fp, "\t%s\n", MSG_HELP_11);
  fprintf(w->out.fp, USG_MSG_OPTIONS);
  fprintf(w->out.fp, USG_MSG_ARG_ALL,         SWITCH_CHAR, ARG_ALL);
  fprintf(w->out.fp, USG_MSG_ARG_BYTE,        SWITCH_CHAR, ARG_BYTE);
  fprintf(w->out.fp, USG_MSG_ARG_EXPAND,      SWITCH_CHAR, ARG_EXPAND);
  fprintf(w->out.fp, USG_MSG_ARG_ERR,         SWITCH_CHAR, ARG_ERR);
  fprintf(w->out.fp, USG_MSG_ARG_FORCE,       SWITCH_CHAR, ARG_FORCE);
  fprintf(w->out.fp, USG_MSG_ARG_HELP,        SWITCH_CHAR, ARG_HELP);
  fprintf(w->out.fp, USG_MSG_ARG_LONG_LEN,    SWITCH_CHAR, ARG_LONG_LEN);
  fprintf(w->out.fp, USG_MSG_ARG_INCLUDE_NL,  SWITCH_CHAR, ARG_INCLUDE_NL);
  fprintf(w->out.fp, USG_MSG_ARG_SHORT_LINES, SWITCH_CHAR, ARG_SHORT_LINES);
  fprintf(w->out.fp, USG_MSG_ARG_OUT,         SWITCH_CHAR, ARG_OUT);
  fprintf(w->out.fp, USG_MSG_ARG_QUIET_3,     SWITCH_CHAR, ARG_QUIET);
  fprintf(w->out.fp, USG_MSG_ARG_SHORT_LEN,   SWITCH_CHAR, ARG_SHORT_LEN);
  fprintf(w->out.fp, USG_MSG_ARG_VERSION,     SWITCH_CHAR, ARG_VERSION);
  fprintf(w->out.fp, USG_MSG_ARG_VERBOSE_6,   SWITCH_CHAR, ARG_VERBOSE);
  fprintf(w->out.fp, USG_MSG_ARG_WORD_COUNT,  SWITCH_CHAR, ARG_WORD_COUNT);
  fprintf(w->out.fp, USG_MSG_ARG_LONG_LINES,  SWITCH_CHAR, ARG_LONG_LINES);

  return(EXIT_FAILURE);

} /* show_brief_help() */

/*
 * show_rev() -- Display program Rev and exit
 */
int show_rev(work_area *w)

{

  fprintf(w->out.fp,"%s %s:\n", PROG_NAME, LIT_REV);
  fprintf(w->out.fp,"\t%s\n", JWC_H_REV);
  fprintf(w->out.fp,"\t%s\n", jwc_rev);
  fprintf(w->out.fp,"\t%s\n", jwc_e_rev);
  fprintf(w->out.fp,"\t%s\n", jwc_hp_rev);
  fprintf(w->out.fp,"\t%s\n", jwc_i_rev);

#ifdef J_LIB2M_H
  fprintf(w->out.fp, "\t%s\n", J_LIB2M_H);
#endif
#ifdef J_LIB2_H
  fprintf(w->out.fp, "\t%s\n", J_LIB2_H);
  fprintf(w->out.fp, "\t     %s %s\n", LIT_INFO_02, j2_get_build());
#endif

#ifdef OSTYPE
  fprintf(w->out.fp,"\t%s\n",OSTYPE);
#endif  /* OSTYPE    */
#ifdef PRETTY_NAME
  fprintf(w->out.fp,"\t%s\n",PRETTY_NAME);
#endif  /* PRETTY_NAME  */

  fprintf(w->out.fp,LIT_INFO_01, __DATE__, __TIME__);

  return(EXIT_FAILURE);

} /* show_rev() */

/* END: jwc_hp.c */
