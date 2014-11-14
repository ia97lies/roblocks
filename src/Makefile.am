# $Id: Makefile.am,v 1.19 2009/07/19 18:31:10 ia97lies Exp $

AM_CFLAGS=-I$(top_srcdir)/include $(INCLUDES)

bin_PROGRAMS = synthetics

synthetics_SOURCES = \
	Graphic.cpp BulletOpenGLApplication.cpp DebugDrawer.cpp GameObject.cpp \
	Synthetics.cpp Hub.cpp main.cpp	

synthetics_LDADD = $(HTTEST_MODULES)

noinst_HEADERS =  
