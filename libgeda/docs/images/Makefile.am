
svg_images = \
	o_attrib_overview.svg \
	o_object_relations.svg \
	o_text_font_overview.svg \
	o_text_text_overview.svg \
	s_conn_overview.svg \
	s_page_overview.svg

EXTRA_DIST = $(svg_images)

png_images = $(EXTRA_DIST:.svg=.png)
pdf_images = $(EXTRA_DIST:.svg=.pdf) 

all:
	@echo 'Type: make images  to create all the png/pdf images'

images: $(png_images) $(pdf_images)

clean-local:
	rm -rf $(png_images) $(pdf_images)

.svg.png:
	if [ -x "`which inkscape`" ]; then inkscape -e $@ $< ; else  convert $< $@; fi

.svg.pdf:
	if [ -x "`which inkscape`" ]; then inkscape -A $@ $< ; else  convert $< $@; fi

SUFFIXES = .svg .pdf .png

MOSTLYCLEANFILES = *~ $(png_images) $(pdf_images)
CLEANFILES = *~ $(png_images) $(pdf_images)
DISTCLEANFILES = *~ $(png_images) $(pdf_images)
MAINTAINERCLEANFILES = *~ Makefile.in $(png_images) $(pdf_images)
