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
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <j_lib2.h>
#include <j_lib2m.h>

#include "jwc.h"

#define WCI_AMODE_NORMAL 0
#define WCI_AMODE_TAB    1
#define WCI_MAX_ENV_ARG  100
#define SCKARG           80

char *jwc_i_rev="$Id: jwc_i.c,v 3.6 2021/02/21 21:01:17 jmccue Exp $";

/*
 * open_out() -- save the file anem and check status
 */
int open_out(FILE *wfp, struct s_file_info *f, char *fname, int force)

{

  int errsave;

  if (fname == (char *) NULL)
    return((int) TRUE);

  if (force == (int) FALSE)
    {
      if ( j2_f_exist(fname) )
	{
	  fprintf(wfp, MSG_ERR_E025, fname);
	  return((int) FALSE);
	}
    }


  f->fp = fopen(fname, "w");
  errsave = errno;

  if (f->fp == (FILE *) NULL)
    {
      f->fp = stderr;  /* needs to be something */
      fprintf(wfp, MSG_ERR_E002, fname);
      fprintf(wfp, "\t%s\n", strerror(errsave));
      return((int) FALSE);
    }

  /*** success, save file name ***/
  f->fname = strdup(fname);
  return((int) TRUE);

} /* open_out() */

/*
 * close_out() -- close output
 */
void close_out(struct s_file_info *f)
{

  if (f->fname != (char *) NULL)
    {
      fclose(f->fp);
      free(f->fname);
      f->fname = (char *) NULL;
    }

} /* close_out() */

/*
 * parse_arg() -- Set an argument value
 */
void parse_arg(work_area *w, int *defaults_overriden, int argc, char **argv)
{

  char ckarg[SCKARG];
  int ok, opt;
  char *fout = (char *) NULL; 
  char *ferr = (char *) NULL; 
  int display_help = (int) FALSE;
  int display_rev  = (int) FALSE;

  snprintf(ckarg, SCKARG, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c:%c:",
          ARG_ALL, ARG_BYTE, ARG_EXPAND, ARG_FORCE, ARG_HELP, 
          ARG_INCLUDE_NL, ARG_LONG_LEN, ARG_SHORT_LINES, ARG_QUIET, 
          ARG_SHORT_LEN, ARG_VERBOSE, ARG_VERSION, ARG_WORD_COUNT, 
          ARG_LONG_LINES, ARG_ERR, ARG_OUT);


  while ((opt = getopt(argc, argv, ckarg)) != -1)
    {
      switch (opt)
	{
	  case ARG_ERR:
	    ferr = optarg;
	    break;
	  case ARG_FORCE:
	    w->force = (int) TRUE;
	    break;
	  case ARG_HELP:
	    display_help = (int) TRUE;
	    break;
	  case ARG_OUT:
	    fout = optarg;
	    break;
	  case ARG_QUIET:
	    w->verbose  = (int) FALSE;
	    break;
	  case ARG_VERBOSE:
	    w->verbose    = (int) TRUE;
	    break;
	  case ARG_VERSION:
	    display_rev = (int) TRUE;
	    break;
	  case ARG_ALL:
	    w->verbose       = (int) TRUE;
	    w->show_bytes    = (int) TRUE;
	    w->show_lines    = (int) TRUE;
	    w->show_words    = (int) TRUE;
	    w->show_min_line = (int) TRUE;
	    w->show_min_num  = (int) TRUE;
	    w->show_max_line = (int) TRUE;
	    w->show_max_num  = (int) TRUE;
	    break;
	  case ARG_BYTE:
	    (*defaults_overriden) = (int) TRUE;
	    w->show_bytes = (int) TRUE;
	    break;
	  case ARG_EXPAND:
	    w->expand_tabs = (int) TRUE;
	    break;
	  case ARG_LONG_LEN:
	    w->show_max_line = (int) TRUE;
	    break;
	  case ARG_INCLUDE_NL:
	    (*defaults_overriden) = (int) TRUE;
	    w->show_lines = (int) TRUE;
	    break;
	  case ARG_SHORT_LINES:
	    w->show_min_num = (int) TRUE;
	    break;
	  case ARG_SHORT_LEN:
	    w->show_min_line = (int) TRUE;
	    break;
	  case ARG_WORD_COUNT:
	    (*defaults_overriden) = (int) TRUE;
	    w->show_words = (int) TRUE;
	    break;
	  case ARG_LONG_LINES:
	    w->show_max_num = (int) TRUE;
	    break;
	  default:
	    fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
	    exit(EXIT_FAILURE);
	    break;
	}
    }

  /*** if necessary - save stdout/err files and open ***/
  ok = open_out(stderr, &(w->err), ferr, w->force);
  if ( ok )
    ok = open_out(w->err.fp, &(w->out), fout, w->force);
  if ( ! ok )
    {
      fprintf(w->err.fp, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
      exit(EXIT_FAILURE);
    }

  /*** see if rev/help display needed ***/
  ok = EXIT_SUCCESS;
  if (display_help)
    ok = show_brief_help(w);
  if (display_rev)
    ok = show_rev(w);
  if (ok != EXIT_SUCCESS)
    {
      close_out(&(w->out));
      close_out(&(w->err));
      exit(ok);
    }

} /* parse_arg() */

/*
 * init_finfo() -- initialize out file structure
 */
void init_finfo(struct s_file_info *f)

{

  f->fp         = (FILE *) NULL;
  f->fname      = (char *) NULL;

} /* init_finfo() */

/*
 * init_work() -- clear work area
 */
void init_work(work_area *w, char *pname)
{

  w->arg_switch        = SWITCH_CHAR;
  w->expand_tabs       = (int) FALSE;
  w->force             = (int) FALSE;
  w->quiet             = (int) FALSE;
  w->verbose           = (int) FALSE;
  w->show_lines        = (int) FALSE;
  w->show_words        = (int) FALSE;
  w->show_bytes        = (int) FALSE;
  w->show_min_line     = (int) FALSE;
  w->show_min_num      = (int) FALSE;
  w->show_max_line     = (int) FALSE;
  w->show_max_num      = (int) FALSE;
  w->show_arg_found    = (int) FALSE;

  w->size_expanded     = 0;
  w->expanded          = (char *) NULL;
  w->bad_arg           = (char *) NULL;

  init_finfo(&(w->err));
  init_finfo(&(w->out));
  init_line_count(&(w->totals));

  w->out.fp = stdout;
  w->err.fp = stderr;

} /* init_work() */

/*****************************************************************************
* init() -- init
*****************************************************************************/
void init(work_area *w, int argc, char **argv)
{
  int defaults_overriden = (int) FALSE;

  init_work(w, argv[0]);

  parse_arg(w, &defaults_overriden, argc, argv);

  if (! defaults_overriden)
    {
      w->show_lines   = (int) TRUE;
      w->show_words   = (int) TRUE;
      w->show_bytes   = (int) TRUE;
    }

} /* END: init() */

/******************************************************************************
* init_line_count()
******************************************************************************/
void init_line_count(l)

	struct s_line_count *l;
{

  l->file_count    = (COUNT_NUM) 0;
  l->lines         = (COUNT_NUM) 0;
  l->words         = (COUNT_NUM) 0;
  l->bytes         = (COUNT_NUM) 0;
  l->min_line_size = (COUNT_NUM) 0;
  l->min_line_num  = (COUNT_NUM) 0;
  l->max_line_size = (COUNT_NUM) 0;
  l->max_line_num  = (COUNT_NUM) 0;

} /* END: init_line_cpunt() */

/******************************* END: jwc_i.c *********************************/
