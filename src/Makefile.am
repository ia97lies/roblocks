# $Id: Makefile.am,v 1.19 2009/07/19 18:31:10 ia97lies Exp $

AM_CFLAGS=-I$(top_srcdir)/include $(INCLUDES)

bin_PROGRAMS = roblocks

roblocks_SOURCES = \
	BulletOpenGLApplication.cpp main.cpp	

roblocks_LDADD = $(HTTEST_MODULES)

noinst_HEADERS = \
	BulletOpenGLApplication.cpp FreeGLUTCallbacks.hpp

