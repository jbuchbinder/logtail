#
#	$Id: Makefile 763 2008-06-12 18:58:01Z jbuchbinder $
#

all: clean logtail logtail.static

logtail:
	gcc -O2 -Wall -pedantic logtail.c -o logtail
	strip --strip-unneeded logtail

logtail.static:
	gcc -O2 -Wall -pedantic -static logtail.c -o logtail.static
	strip --strip-unneeded logtail.static
	upx logtail.static

clean:
	rm logtail logtail.static -f
