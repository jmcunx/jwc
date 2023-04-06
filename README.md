## jwc -- Word Count and Line Length

jwc is a clone of wc(1) but it includes an option for
minimum/maximum Line Length.

This was created for Systems that does not have wc(1)
plus I needed line lengths.

If wc(1) is present, you should use that since it
is much faster.

[j\_lib2](https://github.com/jmcunx/j_lib2) is an **optional** dependency.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, but this seems to be good enough for me.

**To compile:**
* If "DESTDIR" is not set, will install under /usr/local
* Execute ./build.sh to create a Makefile
* Works on Linux, BSD and AIX

_To uninstall_, execute
"make uninstall"
from the source directory
