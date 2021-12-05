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

#ifndef JWC_H_REV

#define PROG_NAME   "jwc"

#define JWC_H_REV "INCLUDED"

#define WC_HDR_1 "%8s "
#define WC_DTL_2 "%8lu "
#define WC_DTL_3 "%s\n"

/*** structures ***/
struct s_file_info
  {
    FILE *fp;
    char *fname;
  } ;

struct s_line_count
{
  COUNT_NUM file_count;
  COUNT_NUM min_line_size;
  COUNT_NUM min_line_num;
  COUNT_NUM max_line_size;
  COUNT_NUM max_line_num;
  COUNT_NUM lines;
  COUNT_NUM words;
  COUNT_NUM bytes;
} ;
typedef struct s_work
{
  char   arg_switch;
  int    force;                  /* TRUE or FALSE, defaults to FALSE       */
  int    expand_tabs;            /* TRUE or FALSE, defaults to FALSE       */
  int    quiet;                  /* TRUE or FALSE, defaults to FALSE       */
  int    verbose;                /* TRUE or FALSE, defaults to FALSE       */
  int    show_lines;             /* TRUE or FALSE, defaults to TRUE        */
  int    show_bytes;             /* TRUE or FALSE, defaults to TRUE        */
  int    show_words;             /* TRUE or FALSE, defaults to TRUE        */
  int    show_min_line;          /* TRUE or FALSE, defaults to FALSE       */
  int    show_min_num;           /* TRUE or FALSE, defaults to FALSE       */
  int    show_max_line;          /* TRUE or FALSE, defaults to FALSE       */
  int    show_max_num;           /* TRUE or FALSE, defaults to FALSE       */
  int    show_arg_found;         /* TRUE or FALSE, defaults to FALSE       */
  size_t size_expanded;          /* mem allocated for expanded             */
  char   *expanded;              /* Expanded buffer for min/max line count */
  char   *bad_arg;
  struct s_file_info out;
  struct s_file_info err;
  struct s_line_count totals;
}  work_area;

/*** prototypes ***/
void init(work_area *, int, char **);
void init_line_count(struct s_line_count *);
void eoj(work_area *);
int  show_rev(work_area *);
int  show_brief_help(work_area *);
void close_out(struct s_file_info *);

#endif   /*  JWC_H_REV  */
