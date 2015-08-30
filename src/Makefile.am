# set the include path for X, qt and KDE
INCLUDES = $(all_includes)

# these are the headers for your project
noinst_HEADERS = kboxes.h

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kboxes.pot

KDE_ICON = kboxes

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = kboxes

# the application source, library search path, and link libraries
kboxes_SOURCES = main.cpp kboxes.cpp
kboxes_LDFLAGS = $(KDE_RPATH) $(all_libraries)
kboxes_LDADD = $(LIB_KDEUI)

# this is where the desktop file will go 
shelldesktopdir   = $(kde_appsdir)/Utilities
shelldesktop_DATA = kboxes.desktop

# this is where the shell's XML-GUI resource file goes
shellrcdir   = $(kde_datadir)/kboxes
shellrc_DATA = kboxesui.rc

