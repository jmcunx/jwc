/*
 * Copyright (c) 2003 ... 2021 2022
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

#ifndef _MSDOS
#include <sys/param.h>
#endif
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#ifdef OpenBSD
#include <err.h>
#endif
#ifdef __FreeBSD_version
#include <err.h>
#endif
#ifdef __NetBSD_Version__
#include <err.h>
#endif

#include <j_lib2.h>
#include <j_lib2m.h>

#include "jwc.h"

/*
 * show_counts()
 */
void show_counts(work_area *w, struct s_line_count *c, char *file_name)
{
  char *fmt_fname;

  if ( w->show_lines )
    fprintf(w->out.fp, WC_DTL_2, c->lines);

  if ( w->show_words )
    fprintf(w->out.fp, WC_DTL_2, c->words);

  if ( w->show_bytes )
    fprintf(w->out.fp, WC_DTL_2, c->bytes);

  if ( w->show_min_line )
    fprintf(w->out.fp, WC_DTL_2, c->min_line_size);

  if ( w->show_min_num )
    {
      if ( (c->min_line_num > (COUNT_NUM) 0) )
	fprintf(w->out.fp, WC_DTL_2, c->min_line_num);
      else
	fprintf(w->out.fp, WC_HDR_1, " ");
    }

  if ( w->show_max_line )
    fprintf(w->out.fp, WC_DTL_2, c->max_line_size);

  if ( w->show_max_num )
    {
      if ( (c->max_line_num > (COUNT_NUM) 0) )
	fprintf(w->out.fp, WC_DTL_2, c->max_line_num);
      else
	fprintf(w->out.fp, WC_HDR_1, " ");
    }

  if (file_name == (char *) NULL)
    fmt_fname = LIT_STDIN;
  else
    {
      if (strcmp(file_name, FILE_NAME_STDIN) == 0)
	fmt_fname = LIT_STDIN;
      else
	fmt_fname = file_name;
    }
  fprintf(w->out.fp, WC_DTL_3, fmt_fname);

} /* show_counts() */

/*
 * show_heading()
 */
void show_heading(work_area *w, char *lines, char *words, char *bytes, char *min, char *minnum, char *max, char *maxnum, char *file)

{
  if ( w->show_lines )
    fprintf(w->out.fp, WC_HDR_1, lines);

  if ( w->show_words )
    fprintf(w->out.fp, WC_HDR_1, words);

  if ( w->show_bytes )
    fprintf(w->out.fp, WC_HDR_1, bytes);

  if ( w->show_min_line )
    fprintf(w->out.fp, WC_HDR_1, min);

  if ( w->show_min_num )
    fprintf(w->out.fp, WC_HDR_1, minnum);

  if ( w->show_max_line )
    fprintf(w->out.fp, WC_HDR_1, max);

  if ( w->show_max_num )
    fprintf(w->out.fp, WC_HDR_1, maxnum);

  fprintf(w->out.fp, "%s", file);
  fprintf(w->out.fp, "\n");

} /* show_heading() */

/*
 * file_type_ok() -- determine file type
 */
int file_type_ok(char *file_name, int quiet, FILE *fp)

{

  int ftype;

  ftype = j2_file_typ(file_name);

  switch (ftype)
    {
      case J2_DIRECTORY:
	if ( ! quiet )
	  fprintf(fp, MSG_WARN_W008, file_name);
	return((int) FALSE);
      case J2_BLOCK_SPECIAL:
	if ( ! quiet )
	  fprintf(fp, MSG_WARN_W011, file_name);
	return((int) FALSE);
	break;
      case J2_CANT_GET:
	if ( ! quiet )
	  fprintf(fp, MSG_WARN_W012, file_name);
	return((int) FALSE);
	break;
      case J2_CHAR_SPECIAL:
	if ( ! quiet )
	  fprintf(fp, MSG_WARN_W010, file_name);
	return((int) FALSE);
	break;
      case J2_FIFO:
	/* do not care */
	break;
      case J2_PIPE:
	/* do not care */
	break;
      case J2_REGULAR:
	/* do not care */
	break;
      case J2_SOCKET:
	/* do not care */
	break;
      case J2_SYMB_LINK:
	/* do not care */
	break;
      case J2_UNKNOWN:
	if ( ! quiet )
	  fprintf(fp, MSG_WARN_W013, file_name);
	return((int) FALSE);
	break;
      default:
	if ( ! quiet )
	  fprintf(fp, MSG_WARN_W009, file_name);
	return((int) FALSE);
	break;
    }

  return((int) TRUE);

} /* file_type_ok() */

/*
 * file_size() -- determine file size
 */
COUNT_NUM file_siz(char *file_name)

{
  struct stat s;

  if (stat(file_name, &s) == 0)
    return((COUNT_NUM) s.st_size);
  
  return((COUNT_NUM) 0);

} /* file_siz() */

/*
 * count_lines() -- Count lines and saves longest line
 */
void count_lines(work_area *w, struct s_line_count *l, char *buf)
{

  COUNT_NUM line_size;

  l->bytes += (COUNT_NUM) strlen(buf); /* for stdin only */

  /*** count lines ***/
  (l->lines)++;

  /*** remove \n and determine line length  ***/
  /*** longest line should not include \n   ***/
  j2_bye_nl(buf);

  if (w->expand_tabs == (int) TRUE)
    {
      if ( j2_expand_tab(EXPAND_TAB_DEFAULT, &(w->size_expanded), &(w->expanded), buf) == (int) TRUE)
	line_size = (COUNT_NUM) strlen(w->expanded);
      else
	line_size = (COUNT_NUM) strlen(buf);
    }
  else
    line_size = (COUNT_NUM) strlen(buf);

  if (l->lines == 1)
    {
      w->totals.min_line_size = line_size;
      l->min_line_num  = l->lines;
      l->min_line_size = line_size;
      l->max_line_num  = l->lines;
      l->max_line_size = line_size;
    }

  if (line_size < l->min_line_size)
    {
      l->min_line_num  = l->lines;
      l->min_line_size = line_size;
    }

  if (line_size > l->max_line_size)
    {
      l->max_line_num  = l->lines;
      l->max_line_size = line_size;
    }

  /*** now ready the line for word count      ***/
  /*** get rid of leading and trailing spaces ***/
  j2_rtw(buf);
  j2_justleft(buf);

} /* count_lines() */

/*
 * count_words() -- Count number of word in a line
 */
void count_words(struct s_line_count *l, char *buf)

{
  char last_char = 'a';

  if ((*buf) == (COUNT_NUM) 0)
    return;

  for ( ;  (*buf) != JLIB2_CHAR_NULL; buf++ )
    {
      if ( ! isspace((int) last_char) )
	{
	  if ( isspace((int) (*buf)) )
	    (l->words)++;
	}
      last_char = (*buf);
    }
  (l->words)++;

} /* count_words() */

/*
 * open_in() -- open in file
 */
int open_in(FILE **in, char *fname, FILE *fp_err, int quiet)

{

  int errsave;

  if (fname == (char *) NULL)
    {
      (*in) = stdin;
      return((int) TRUE);
    }
  if (strcmp(fname, FILE_NAME_STDIN) == 0)
    {
      (*in) = stdin;
      return((int) TRUE);
    }
  
  if ( ! file_type_ok(fname, quiet, fp_err) )
    return((int) FALSE);

  (*in) = fopen(fname, "r");
  errsave = errno;

  if ((*in) == (FILE *) NULL)
    {
      fprintf(fp_err, MSG_WARN_W002, fname, strerror(errsave));
      return((int) FALSE);
    }

  return((int) TRUE);

} /* open_in() */

/*
 * count_file()
 */
void count_file(work_area *w, char *file_name)

{
  FILE *fp;
  size_t buf_size;
  char *buf;
  ssize_t cbytes = (ssize_t) 0;
  struct s_line_count count;

  init_line_count(&count);
  buf = (char *) NULL;

  if ( ! open_in(&(fp), file_name, (w->err.fp), w->quiet) )
    return;

  /* allocate initial read buffer memory (optional) */
  buf_size = (size_t) 200;
  buf = (char *) calloc(buf_size, sizeof(char));
  if (buf == (char *) NULL)
    {
      fprintf(w->err.fp, MSG_ERR_E023, file_name);
      fprintf(w->err.fp, "\t%s\n", strerror(errno));
      return;
    }

  /* Process Data */
  while ((cbytes = j2_getline(&buf, &buf_size, fp)) > (ssize_t) -1)
    {
      count_lines(w, &count, buf);
      count_words(&count, buf);
    }
  free(buf);

  if (file_name != (char *) NULL)
    {
      if (strcmp(file_name, FILE_NAME_STDIN) != 0)
	{
	  if (fp != (FILE *) NULL)
	    fclose(fp);
	}
    }

  /*** get byte count, for MSDOS type sys and binary files ***/
  if (file_name != (char *) NULL)
    {
      if (strcmp(file_name, FILE_NAME_STDIN) != 0)
	(count.bytes) = file_siz(file_name);
    }

  /*** show file results ***/
  show_counts(w, &count, file_name);

  /*** add totals ***/
  (w->totals.file_count)++;
  (w->totals.lines) += (count.lines);
  (w->totals.words) += (count.words);
  (w->totals.bytes) += (count.bytes);
  if (count.min_line_size < w->totals.min_line_size)
    w->totals.min_line_size = count.min_line_size;
  if (count.max_line_size > w->totals.max_line_size)
    w->totals.max_line_size = count.max_line_size;

} /* count_file() */

/*
 * process_wc()
 */
void process_wc(work_area *w, int argc, char **argv)

{
  int i;

  if (w->verbose)
    {
      show_heading(w, LIT_LINES,    LIT_WORDS,    LIT_BYTES,    
                      LIT_MIN,      LIT_MIN_NUM,  LIT_MAX,      
                      LIT_MAX_NUM,  LIT_FILE);
      show_heading(w, LIT_ULINE_08, LIT_ULINE_08, LIT_ULINE_08, 
                      LIT_ULINE_08, LIT_ULINE_08, LIT_ULINE_08, 
                      LIT_ULINE_08, LIT_ULINE_16);
    }

  /*** process all files ***/
  for (i = optind; i < argc; i++)
    count_file(w, argv[i]);
  if (i == optind)
    count_file(w, FILE_NAME_STDIN);

  if (w->totals.file_count > (COUNT_NUM) 1)
    show_counts(w, &(w->totals), LIT_TOTAL);

} /* process_wc() */

/*
 * main()
 */
int main(int argc, char **argv)

{

  work_area w;

#ifdef OpenBSD
  if(pledge("stdio rpath wpath cpath",NULL) == -1)
    err(1,"pledge\n");
#endif

  init(&w, argc, argv);

  process_wc(&w, argc, argv);

  eoj(&w);

  exit(0);

}  /* main() */
