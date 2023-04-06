/*
 * Copyright (c) 2003 ... 2023 2024
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

#ifndef JLIB2_CHAR_NULL
#define NO_JLIB 1
#define JLIB2_INT_NULL   ((int) '\0')
#define JLIB2_CHAR_NULL  ((char) '\0')
#define JLIB2_UCHAR_NULL ((unsigned char) '\0' )
#endif

#ifndef NULL
#define NULL '\0'
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef TAB_CHAR
#define TAB_CHAR 0x09
#endif
#ifndef COUNT_NUM
#define COUNT_NUM unsigned long
#endif
#ifndef EXPAND_TAB_DEFAULT
#define EXPAND_TAB_DEFAULT 8
#endif

/*** values returned by file_type() ***/
#ifdef NO_JLIB
#define J2_CANT_GET      0
#define J2_UNKNOWN       1
#define J2_DIRECTORY     2  /* S_IFDIR  */
#define J2_REGULAR       3  /* S_IFREG  */
#define J2_CHAR_SPECIAL  4  /* S_IFCHR  */
#define J2_BLOCK_SPECIAL 5  /* S_IFBLK  */
#define J2_PIPE          6  /* S_IFPIP  */
#define J2_SOCKET        7  /* S_IFSOCK */
#define J2_SYMB_LINK     8  /* S_IFLNK  */
#define J2_FIFO          9  /* S_IFIFO  */
#endif /* NO_JLIB */

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

/*** messages ***/
#ifdef NO_JLIB
#define ARG_ALL           'a'  /* Turn on all options                */
#define ARG_BYTE          'b'  /* Show byte counts                   */
#define ARG_ERR           'e'  /* Output Error File                  */
#define ARG_EXPAND        'E'  /* Expand tabs to spaces              */
#define ARG_FORCE         'f'  /* force create files                 */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_INCLUDE_NL    'l'  /* Include new line in counts         */
#define ARG_LONG_LEN      'L'  /* print length of the longest line   */
#define ARG_LONG_LINES    'X'  /* print line # of the longest line   */
#define ARG_OUT           'o'  /* Output File                        */
#define ARG_QUIET         'q'  /* Quiet Mode                         */
#define ARG_SHORT_LEN     's'  /* print length of the longest line   */
#define ARG_SHORT_LINES   'N'  /* print line # of the shortest line  */
#define ARG_VERBOSE       'v'  /* Verbose                            */
#define ARG_VERSION       'V'  /* Show Version Information           */
#define ARG_WORD_COUNT    'w'  /* Show work count                    */
#define FILE_NAME_STDIN   "-"
#define LIT_BYTES         "Bytes"
#define LIT_FILE          "File"
#define LIT_INFO_01       "\tBuild: %s %s\n"
#define LIT_LINES         "Lines"
#define LIT_MAX           "Max Size"
#define LIT_MAX_NUM       "Max Line"
#define LIT_MIN           "Min Size"
#define LIT_MIN_NUM       "Min Line"
#define LIT_REV           "Revision"
#define LIT_STDIN         "(standard input)"
#define LIT_TOTAL         "Total"
#define LIT_ULINE_08      "--------"
#define LIT_ULINE_16      "----------------"
#define LIT_WORDS         "Words"
#define MSG_ERR_E000      "Try '%s %c%c' for more information\n"
#define MSG_ERR_E002      "ERROR E002: Cannot open '%s' for write, processing aborted\n"
#define MSG_ERR_E023      "ERROR E023: Cannot allocate memory when processing file %s, file bypassed\n"
#define MSG_ERR_E025      "ERROR E025: File %s cannot be created, already exists\n"
#define MSG_WARN_W002     "W002: Open Error Bypass File '%s' : %s\n"
#define MSG_WARN_W008     "W008: %s is a directory\n"
#define MSG_WARN_W009     "W009: %s File Type Unknown\n"
#define MSG_WARN_W010     "W010: %s File Type Character Special\n"
#define MSG_WARN_W011     "W011: %s File Type Block Special\n"
#define MSG_WARN_W012     "W012: %s File Type Cannot be determined\n"
#define MSG_WARN_W013     "W013: %s File Type undetermined\n"
#define SWITCH_CHAR       '-'
#define USG_MSG_ARG_ALL          "\t%c%c\t\t: Turn all displays on\n"
#define USG_MSG_ARG_BYTE         "\t%c%c\t\t: print byte counts\n"
#define USG_MSG_ARG_ERR          "\t%c%c file\t\t: Write errors to file 'file', default stderr\n"
#define USG_MSG_ARG_EXPAND       "\t%c%c\t\t: Expand TABs to spaces\n"
#define USG_MSG_ARG_FORCE        "\t%c%c\t\t: force create of files when found\n"
#define USG_MSG_ARG_HELP         "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_INCLUDE_NL   "\t%c%c\t\t: print newline counts (# of records)\n"
#define USG_MSG_ARG_LONG_LEN     "\t%c%c\t\t: print length of the longest line\n"
#define USG_MSG_ARG_LONG_LINES   "\t%c%c\t\t: print line number of the longest line\n"
#define USG_MSG_ARG_OUT          "\t%c%c file\t\t: Write output to file 'file', default stdout\n"
#define USG_MSG_ARG_QUIET_3      "\t%c%c\t\t: do not print file open errors\n"
#define USG_MSG_ARG_SHORT_LEN    "\t%c%c\t\t: print length of the shortest line\n"
#define USG_MSG_ARG_SHORT_LINES  "\t%c%c\t\t: print line number of the shortest line\n"
#define USG_MSG_ARG_VERBOSE_6    "\t%c%c\t\t: Print column headings\n"
#define USG_MSG_ARG_VERSION      "\t%c%c\t\t: Show revision information and exit\n"
#define USG_MSG_ARG_WORD_COUNT   "\t%c%c\t\t: print word counts\n"
#define USG_MSG_OPTIONS          "Options\n"
#define USG_MSG_USAGE            "usage:\t%s [OPTIONS] [FILES ...]\n"
#endif /* NO_JLIB */

/*** prototypes ***/
void init(work_area *, int, char **);
void init_line_count(struct s_line_count *);
void eoj(work_area *);
int  show_rev(work_area *);
int  show_brief_help(work_area *);
void close_out(struct s_file_info *);

#ifdef NO_JLIB
SSIZE_T j2_getline(char **buf, size_t *n, FILE *fp);
int j2_expand_tab(int tab_size, size_t *out_buf_size, char **out_buf, char *in_buf);
int j2_f_exist(char *file_name);
int j2_file_typ(char *file_name);
long int j2_bye_last(char *x, char lastc);
long int j2_chg_char(char old, char new, char *s, SSIZE_T force_size);
long int j2_clr_str(char *s, char c, int size);
long int j2_justleft(char *s);
long int j2_rtw(char *buffer);
#define j2_bye_nl(x)    j2_bye_last((x), '\n')
#define j2_bye_ctlm(x)  j2_bye_last((x), '\r')
#endif /* NO_JLIB */

#endif   /*  JWC_H_REV  */
