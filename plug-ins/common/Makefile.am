

## ---------------------------------------------------------
## This file is autogenerated by mkgen.pl and plugin-defs.pl
## ---------------------------------------------------------

## Modify those two files instead of this one; for most
## plug-ins you should only need to modify plugin-defs.pl.


libgimp = $(top_builddir)/libgimp/libgimp-$(GIMP_API_VERSION).la
libgimpbase = $(top_builddir)/libgimpbase/libgimpbase-$(GIMP_API_VERSION).la
libgimpcolor = $(top_builddir)/libgimpcolor/libgimpcolor-$(GIMP_API_VERSION).la
libgimpconfig = $(top_builddir)/libgimpconfig/libgimpconfig-$(GIMP_API_VERSION).la
libgimpmath = $(top_builddir)/libgimpmath/libgimpmath-$(GIMP_API_VERSION).la
libgimpmodule = $(top_builddir)/libgimpmodule/libgimpmodule-$(GIMP_API_VERSION).la
libgimpui = $(top_builddir)/libgimp/libgimpui-$(GIMP_API_VERSION).la
libgimpwidgets = $(top_builddir)/libgimpwidgets/libgimpwidgets-$(GIMP_API_VERSION).la


if OS_WIN32
mwindows = -mwindows
endif

AM_LDFLAGS = $(mwindows)

libexecdir = $(gimpplugindir)/plug-ins

EXTRA_DIST = \
	mkgen.pl	\
	plugin-defs.pl

INCLUDES = \
	-I$(top_srcdir)	\
	$(GTK_CFLAGS)	\
	-I$(includedir)

libexec_PROGRAMS = \
	AlienMap2 \
	CEL \
	CML_explorer \
	$(AA) \
	align_layers \
	animationplay \
	animoptimize \
	antialias \
	apply_lens \
	autocrop \
	autostretch_hsv \
	blinds \
	blur \
	borderaverage \
	bumpmap \
	c_astretch \
	cartoon \
	ccanalyze \
	channel_mixer \
	checkerboard \
	color_enhance \
	colorify \
	colormap-remap \
	colortoalpha \
	compose \
	compressor \
	convmatrix \
	csource \
	cubism \
	curve_bend \
	decompose \
	deinterlace \
	depthmerge \
	desktop-link \
	despeckle \
	destripe \
	dicom \
	diffraction \
	displace \
	dog \
	edge \
	emboss \
	engrave \
	exchange \
	film \
	flarefx \
	fp \
	fractaltrace \
	gauss \
	gbr \
	gee \
	gee_zoom \
	gif-load \
	gif-save \
	gih \
	glasstile \
	glob \
	gqbist \
	gradmap \
	grid \
	gtm \
	guillotine \
	header \
	hot \
	illusion \
	iwarp \
	jigsaw \
	laplace \
	$(LCMS) \
	lens \
	lic \
	$(MAIL) \
	mapcolor \
	max_rgb \
	mblur \
	$(MNG) \
	mosaic \
	neon \
	newsprint \
	nlfilt \
	noisify \
	normalize \
	nova \
	oilify \
	papertile \
	pat \
	pcx \
	photocopy \
	pix \
	pixelize \
	plasma \
	plugin-browser \
	$(PNG) \
	pnm \
	polar \
	$(POPPLER) \
	postscript \
	procedure-browser \
	psd-load \
	psd-save \
	$(PSP) \
	randomize \
	raw \
	redeye \
	retinex \
	ripple \
	rotate \
	sample_colorize \
	scatter_hsv \
	$(SCREENSHOT) \
	sel_gauss \
	semiflatten \
	sharpen \
	shift \
	sinus \
	smooth_palette \
	snoise \
	sobel \
	softglow \
	sparkle \
	spheredesigner \
	spread \
	struc \
	sunras \
	$(SVG) \
	tga \
	threshold_alpha \
	$(TIFF_LOAD) \
	$(TIFF_SAVE) \
	tile \
	tileit \
	tiler \
	uniteditor \
	unsharp \
	video \
	vinvert \
	vpropagate \
	warp \
	waves \
	webbrowser \
	whirlpinch \
	wind \
	$(WMF) \
	xbm \
	$(XPM) \
	xwd \
	zealouscrop

EXTRA_PROGRAMS = \
	aa \
	lcms \
	mail \
	mng \
	png \
	poppler \
	psp \
	screenshot \
	svg \
	tiff-load \
	tiff-save \
	wmf \
	xpm

install-%: %
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libexecdir)
	@p=$<; p1=`echo $$p|sed 's/$(EXEEXT)$$//'`; \
	if test -f $$p \
	   || test -f $$p1 \
	; then \
	  f=`echo "$$p1" | sed 's,^.*/,,;$(transform);s/$$/$(EXEEXT)/'`; \
	  echo " $(INSTALL_PROGRAM_ENV) $(LIBTOOL) --mode=install $(libexecPROGRAMS_INSTALL) $$p $(DESTDIR)$(libexecdir)/$$f"; \
	  $(INSTALL_PROGRAM_ENV) $(LIBTOOL) --mode=install $(libexecPROGRAMS_INSTALL) $$p $(DESTDIR)$(libexecdir)/$$f || exit 1; \
	else :; fi

AlienMap2_SOURCES = \
	AlienMap2.c

AlienMap2_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

CEL_SOURCES = \
	CEL.c

CEL_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

CML_explorer_SOURCES = \
	CML_explorer.c

CML_explorer_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

aa_SOURCES = \
	aa.c

aa_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBAA)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

align_layers_SOURCES = \
	align_layers.c

align_layers_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

animationplay_SOURCES = \
	animationplay.c

animationplay_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

animoptimize_SOURCES = \
	animoptimize.c

animoptimize_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

antialias_SOURCES = \
	antialias.c

antialias_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

apply_lens_SOURCES = \
	apply_lens.c

apply_lens_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

autocrop_SOURCES = \
	autocrop.c

autocrop_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

autostretch_hsv_SOURCES = \
	autostretch_hsv.c

autostretch_hsv_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

blinds_SOURCES = \
	blinds.c

blinds_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

blur_SOURCES = \
	blur.c

blur_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

borderaverage_SOURCES = \
	borderaverage.c

borderaverage_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

bumpmap_SOURCES = \
	bumpmap.c

bumpmap_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

c_astretch_SOURCES = \
	c_astretch.c

c_astretch_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

cartoon_SOURCES = \
	cartoon.c

cartoon_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

ccanalyze_SOURCES = \
	ccanalyze.c

ccanalyze_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

channel_mixer_SOURCES = \
	channel_mixer.c

channel_mixer_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

checkerboard_SOURCES = \
	checkerboard.c

checkerboard_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

color_enhance_SOURCES = \
	color_enhance.c

color_enhance_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

colorify_SOURCES = \
	colorify.c

colorify_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

colormap_remap_SOURCES = \
	colormap-remap.c

colormap_remap_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

colortoalpha_SOURCES = \
	colortoalpha.c

colortoalpha_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

compose_SOURCES = \
	compose.c

compose_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

compressor_SOURCES = \
	compressor.c

compressor_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

convmatrix_SOURCES = \
	convmatrix.c

convmatrix_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

csource_SOURCES = \
	csource.c

csource_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

cubism_SOURCES = \
	cubism.c

cubism_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

curve_bend_SOURCES = \
	curve_bend.c

curve_bend_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

decompose_SOURCES = \
	decompose.c

decompose_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

deinterlace_SOURCES = \
	deinterlace.c

deinterlace_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

depthmerge_SOURCES = \
	depthmerge.c

depthmerge_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

desktop_link_SOURCES = \
	desktop-link.c

desktop_link_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

despeckle_SOURCES = \
	despeckle.c

despeckle_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

destripe_SOURCES = \
	destripe.c

destripe_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

dicom_SOURCES = \
	dicom.c

dicom_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

diffraction_SOURCES = \
	diffraction.c

diffraction_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

displace_SOURCES = \
	displace.c

displace_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

dog_SOURCES = \
	dog.c

dog_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

edge_SOURCES = \
	edge.c

edge_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

emboss_SOURCES = \
	emboss.c

emboss_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

engrave_SOURCES = \
	engrave.c

engrave_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

exchange_SOURCES = \
	exchange.c

exchange_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

film_SOURCES = \
	film.c

film_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

flarefx_SOURCES = \
	flarefx.c

flarefx_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

fp_SOURCES = \
	fp.c

fp_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

fractaltrace_SOURCES = \
	fractaltrace.c

fractaltrace_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gauss_SOURCES = \
	gauss.c

gauss_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gbr_SOURCES = \
	gbr.c

gbr_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gee_SOURCES = \
	gee.c

gee_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gee_zoom_SOURCES = \
	gee_zoom.c

gee_zoom_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gif_load_SOURCES = \
	gif-load.c

gif_load_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gif_save_SOURCES = \
	gif-save.c

gif_save_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gih_SOURCES = \
	gih.c

gih_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

glasstile_SOURCES = \
	glasstile.c

glasstile_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

glob_SOURCES = \
	glob.c

glob_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gqbist_SOURCES = \
	gqbist.c

gqbist_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gradmap_SOURCES = \
	gradmap.c

gradmap_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

grid_SOURCES = \
	grid.c

grid_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

gtm_SOURCES = \
	gtm.c

gtm_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

guillotine_SOURCES = \
	guillotine.c

guillotine_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

header_SOURCES = \
	header.c

header_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

hot_SOURCES = \
	hot.c

hot_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

illusion_SOURCES = \
	illusion.c

illusion_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

iwarp_SOURCES = \
	iwarp.c

iwarp_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

jigsaw_SOURCES = \
	jigsaw.c

jigsaw_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

laplace_SOURCES = \
	laplace.c

laplace_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

lcms_SOURCES = \
	lcms.c

lcms_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBLCMS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

lens_SOURCES = \
	lens.c

lens_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

lic_SOURCES = \
	lic.c

lic_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

mail_SOURCES = \
	mail.c

mail_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBMAIL)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

mapcolor_SOURCES = \
	mapcolor.c

mapcolor_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

max_rgb_SOURCES = \
	max_rgb.c

max_rgb_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

mblur_SOURCES = \
	mblur.c

mblur_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

mng_SOURCES = \
	mng.c

mng_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBMNG)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

mosaic_SOURCES = \
	mosaic.c

mosaic_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

neon_SOURCES = \
	neon.c

neon_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

newsprint_SOURCES = \
	newsprint.c

newsprint_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

nlfilt_SOURCES = \
	nlfilt.c

nlfilt_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

noisify_SOURCES = \
	noisify.c

noisify_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

normalize_SOURCES = \
	normalize.c

normalize_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

nova_SOURCES = \
	nova.c

nova_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

oilify_SOURCES = \
	oilify.c

oilify_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

papertile_SOURCES = \
	papertile.c

papertile_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

pat_SOURCES = \
	pat.c

pat_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

pcx_SOURCES = \
	pcx.c

pcx_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

photocopy_SOURCES = \
	photocopy.c

photocopy_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

pix_SOURCES = \
	pix.c

pix_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

pixelize_SOURCES = \
	pixelize.c

pixelize_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

plasma_SOURCES = \
	plasma.c

plasma_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

plugin_browser_SOURCES = \
	plugin-browser.c

plugin_browser_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

png_CFLAGS = $(PNG_CFLAGS)

png_SOURCES = \
	png.c

png_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBPNG)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

pnm_SOURCES = \
	pnm.c

pnm_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

polar_SOURCES = \
	polar.c

polar_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

poppler_CFLAGS = $(POPPLER_CFLAGS)

poppler_SOURCES = \
	poppler.c

poppler_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBPOPPLER)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

postscript_SOURCES = \
	postscript.c

postscript_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

procedure_browser_SOURCES = \
	procedure-browser.c

procedure_browser_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

psd_load_SOURCES = \
	psd-load.c

psd_load_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

psd_save_SOURCES = \
	psd-save.c

psd_save_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

psp_SOURCES = \
	psp.c

psp_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBZ)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

randomize_SOURCES = \
	randomize.c

randomize_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

raw_SOURCES = \
	raw.c

raw_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

redeye_SOURCES = \
	redeye.c

redeye_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

retinex_SOURCES = \
	retinex.c

retinex_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

ripple_SOURCES = \
	ripple.c

ripple_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

rotate_SOURCES = \
	rotate.c

rotate_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

sample_colorize_SOURCES = \
	sample_colorize.c

sample_colorize_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

scatter_hsv_SOURCES = \
	scatter_hsv.c

scatter_hsv_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

screenshot_SOURCES = \
	screenshot.c

screenshot_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBSCREENSHOT)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

sel_gauss_CFLAGS = $(MMX_EXTRA_CFLAGS)

sel_gauss_SOURCES = \
	sel_gauss.c

sel_gauss_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

semiflatten_SOURCES = \
	semiflatten.c

semiflatten_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

sharpen_SOURCES = \
	sharpen.c

sharpen_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

shift_SOURCES = \
	shift.c

shift_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

sinus_SOURCES = \
	sinus.c

sinus_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

smooth_palette_SOURCES = \
	smooth_palette.c

smooth_palette_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

snoise_SOURCES = \
	snoise.c

snoise_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

sobel_SOURCES = \
	sobel.c

sobel_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

softglow_SOURCES = \
	softglow.c

softglow_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

sparkle_SOURCES = \
	sparkle.c

sparkle_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

spheredesigner_SOURCES = \
	spheredesigner.c

spheredesigner_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

spread_SOURCES = \
	spread.c

spread_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

struc_SOURCES = \
	struc.c

struc_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

sunras_SOURCES = \
	sunras.c

sunras_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

svg_CFLAGS = $(SVG_CFLAGS)

svg_SOURCES = \
	svg.c

svg_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBSVG)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

tga_SOURCES = \
	tga.c

tga_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

threshold_alpha_SOURCES = \
	threshold_alpha.c

threshold_alpha_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

tiff_load_SOURCES = \
	tiff-load.c

tiff_load_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBTIFF)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

tiff_save_SOURCES = \
	tiff-save.c

tiff_save_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBTIFF)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

tile_SOURCES = \
	tile.c

tile_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

tileit_SOURCES = \
	tileit.c

tileit_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

tiler_SOURCES = \
	tiler.c

tiler_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

uniteditor_SOURCES = \
	uniteditor.c

uniteditor_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

unsharp_SOURCES = \
	unsharp.c

unsharp_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

video_SOURCES = \
	video.c

video_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

vinvert_SOURCES = \
	vinvert.c

vinvert_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

vpropagate_SOURCES = \
	vpropagate.c

vpropagate_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

warp_SOURCES = \
	warp.c

warp_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

waves_SOURCES = \
	waves.c

waves_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

webbrowser_SOURCES = \
	webbrowser.c

webbrowser_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

whirlpinch_SOURCES = \
	whirlpinch.c

whirlpinch_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

wind_SOURCES = \
	wind.c

wind_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

wmf_CFLAGS = $(WMF_CFLAGS)

wmf_SOURCES = \
	wmf.c

wmf_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBWMF)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

xbm_SOURCES = \
	xbm.c

xbm_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

xpm_SOURCES = \
	xpm.c

xpm_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(LIBXPM)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

xwd_SOURCES = \
	xwd.c

xwd_LDADD = \
	$(libgimpui)		\
	$(libgimpwidgets)	\
	$(libgimpmodule)	\
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GTK_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)

zealouscrop_SOURCES = \
	zealouscrop.c

zealouscrop_LDADD = \
	$(libgimp)		\
	$(libgimpmath)		\
	$(libgimpconfig)	\
	$(libgimpcolor)		\
	$(libgimpbase)		\
	$(GLIB_LIBS)		\
	$(RT_LIBS)		\
	$(INTLLIBS)
