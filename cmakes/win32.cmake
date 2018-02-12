#
# x86_64 - Msys2 - Mingw64
#

SET( LIBS wx_mswu_richtext-3.1 wx_mswu_adv-3.1 wx_mswu_html-3.1
 wx_mswu_core-3.1 wx_baseu_xml-3.1 wx_baseu-3.1 wxtiff-3.1 wxjpeg-3.1 wxpng-3.1
 wxzlib-3.1 wxregexu-3.1 wxexpat-3.1 rpcrt4 oleaut32 ole32 uuid uxtheme
 winspool winmm shell32 shlwapi comctl32 comdlg32 advapi32 version wsock32
 gdi32 oleacc )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -D__WXMSW__" )

include_directories(
 "${WX_LIB_DIR}/include/wx-3.1"
 "${WX_LIB_DIR}/lib/wx/include/msw-unicode-static-3.1"
)
