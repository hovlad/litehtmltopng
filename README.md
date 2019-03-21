## litehtmltopng (litehtml engine)

**litehtmltopng** is simple html render to png image designed to helper the [litehtml HTML rendering engine](https://github.com/tordex/litehtml)
used fork [litehtml C++98 / freetype fork](https://github.com/hovlad/litehtmlcpp98) because while in fork implemented \litehtml\containers\cairo_ft 
this cairo_ft container allows minimal dependencies for platforms Windows, Linux Embedded, Android and other.

Also demonstrated:
  * cairo work with freetype
  * cairo scaling pictures

### Building

You can build litehtmltopng with Vinsual Studio 2008 and newer. **Note**: this project contais some git submodules:

  * [freetype](https://github.com/aseprite/freetype2) - used to draw fonts
  * [cairo](https://github.com/tordex/cairo) - 2D graphics library
  * [fork litehtml](https://github.com/hovlad/litehtmlcpp98) - html rendering engine

Please be sure the submodules are fetched, or download them from github and copy into libs subfolder.

### Download binaries

You can download the binary files from:
[github.com] (https://github.com/ubawurinna/freetype-windows-binaries) 
[litehtml.com](http://www.litehtml.com)


### Using litehtmltopng

Before running litehtmltopng copy the files freetype.dll (from libs\freetype) cairo.dll (from libs\cairo) and litehtml.dll (libs\litehtml) into the same folder where litehtmltopng.exe is.

### Additionally

  * basis of the project https://github.com/litehtml/litebrowser
  * litehtml should be compiled with define LITEHTML_UTF8
  
### Reference links
	* litehtml wiki: https://github.com/litehtml/litehtml/wiki/How-to-use-litehtml
	* demo cairo and fretype from https://www.lemoda.net/c/free-type/index.html "An example of Cairo and FreeType in C"
	* demo cairo scaling pictures:
https://www.cairographics.org/documentation/
https://www.cairographics.org/samples/
https://progtips.ru/texnologii-programmirovaniya/graficheskaya-biblioteka-cairo.html
http://www.opennet.ru/docs/RUS/tutorial_cairo/
