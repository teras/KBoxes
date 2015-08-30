####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = kboxes
kboxes_SOURCES = kboxes.cpp main.cpp 
kboxes_LDADD   =  -lqt -lXext -lX11 $(LIBSOCKET)

SUBDIRS = docs 

EXTRA_DIST = main.cpp kboxes.cpp kboxes.h resource.h kboxes.xpm mini-kboxes.xpm 

####### kdevelop will overwrite this part!!! (end)############


# set the include path for X, qt and KDE
INCLUDES= $(all_includes)
# claim, which subdirectories you want to install
# you can add here more. This one gets installed 
bin_PROGRAMS = kboxes 

kboxes_METASOURCES = USE_AUTOMOC

# the library search path. 
kboxes_LDFLAGS = $(all_libraries) 

# them while "make clean", use CLEANFILES
DISTCLEANFILES = $(kboxes_METASOURCES)




