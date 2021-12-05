## jwc -- Word Count and Line Length

jwc is a clone of wc(1) but it includes an option for
minimum/maximum Line Length.

This was created for Systems that does not have wc(1)
plus I needed line lengths.

If wc(1) is present, you should use that since it
is much faster.

To build, execute build.sh to generate a Makefile from
Makefile.template on most BSD/Linux systems and IBM AIX.
For MS-DOS, it should be rather easy to create a Makefile.

This requires [j_lib2](https://github.com/jmcunx/j_lib2) to build.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, so I came up with my own method which
is a real hack.  But works for me.
