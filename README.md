## litehtmltopng (litehtml engine)

**litehtmltopng** is simple html render to png image designed to helper the [litehtml HTML rendering engine](https://github.com/tordex/litehtml).

Also demonstrated:
  * cairo work with freetype
  * cairo scaling pictures

### Building

You can build litehtmltopng with Vinsual Studio 2008 and newer. **Note**: this project contais some git submodules:

  * [freetype](https://github.com/aseprite/freetype2) - used to draw fonts
  * [cairo](https://github.com/tordex/cairo) - 2D graphics library
  * [litehtmlcpp98](https://github.com/hovlad/litehtmlcpp98) - fork [litehtml HTML rendering engine](https://github.com/tordex/litehtml)

Please be sure the submodules are fetched, or download them from github and copy into libs subfolder.

* [litehtmlcpp98](https://github.com/hovlad/litehtmlcpp98) and [litehtmltopng](https://github.com/hovlad/litehtmltopng) should be compiled with define LITEHTML_UTF8 for all platforms

### Why fork litehtml?

Used [litehtmlcpp98](https://github.com/hovlad/litehtmlcpp98) because while in fork implemented [cairo_f container](https://github.com/hovlad/litehtmlcpp98/tree/master/containers/cairo_ft) allows minimal commons dependencies for Windows, Linux Embedded, Android and other platforms.

### Download binaries

You can download the binary files from 
[freetype](https://github.com/ubawurinna/freetype-windows-binaries) 
[cairo](https://github.com/preshing/cairo-windows/releases)

### Using litehtmltopng

Before running litehtmltopng copy the files freetype.dll (from libs\freetype) cairo.dll (from libs\cairo) and litehtml.dll (libs\litehtml) into the same folder where litehtmltopng.exe .

### Additionally

  * basis of the project https://github.com/litehtml/litebrowser
  
### Reference links

  * [litehtml wiki](https://github.com/litehtml/litehtml/wiki/How-to-use-litehtml)
  * [An example of Cairo and FreeType in C](https://www.lemoda.net/c/free-type/index.html)
  * [cairo doc](https://www.cairographics.org/documentation)
  * [cairo samples](https://www.cairographics.org/samples)
  * [graficheskaya-biblioteka-cairo](https://progtips.ru/texnologii-programmirovaniya/graficheskaya-biblioteka-cairo.html)
  * [cairo tutorial](http://www.opennet.ru/docs/RUS/tutorial_cairo)
