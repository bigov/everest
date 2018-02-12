#
# x86_64 GNU/Linux
#

SET( LIBS wx_gtk2u_richtext-3.1 wx_gtk2u_adv-3.1 wx_gtk2u_html-3.1
 wx_gtk2u_core-3.1 wx_baseu_xml-3.1 wx_baseu-3.1 wxtiff-3.1 wxjpeg-3.1
 wxpng-3.1 gtk-x11-2.0 gdk-x11-2.0 pangocairo-1.0 atk-1.0 cairo
 gdk_pixbuf-2.0 gio-2.0 pangoft2-1.0 pango-1.0 gobject-2.0 fontconfig
 freetype gthread-2.0 glib-2.0 X11 Xxf86vm SM notify Xtst wxzlib-3.1
 wxregexu-3.1 wxexpat-3.1 dl secret-1 m )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie -pthread -D__WXGTK__" )

include_directories(
 "${WX_SRC_DIR}/include"
 "${WX_LIB_DIR}/include"
 "${WX_LIB_DIR}/include/wx-3.1"
 "${WX_LIB_DIR}/lib/wx/include/gtk2-unicode-static-3.1"
)
