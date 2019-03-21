// litehtmltopng.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <memory>
// Cairo is a 2D graphics library with support for multiple output devices
#include <cairo.h>
// Cairo document_container by https://github.com/litehtml/litehtml/wiki/document_container
#include "container_cairo_ft.h"

#include <string>
#include <fstream>
#include <streambuf>

//general device container
class device_container : public container_cairo_ft
{
public:
	virtual ~device_container() {};
protected:
	virtual int device_width_px() const = 0;
	virtual int device_resolution_dpi() const = 0;
	virtual std::string path_root_resources() const = 0;
private:
	// cairo_container members
	virtual	void get_client_rect(litehtml::position& client)  const
	{
		client = litehtml::position(0, 0, device_width_px(), 0);
	}

	virtual	void make_url(const litehtml::tchar_t* url, const litehtml::tchar_t* basepath, litehtml::tstring& out)
	{
		out = path_root_resources() + url;
	}

	virtual	void get_media_features(litehtml::media_features& media) const
	{
		litehtml::position client;
		get_client_rect(client);
		media.type = litehtml::media_type_screen;
		media.width = client.width;
		media.height = client.height;
		media.device_width = device_width_px();
		media.device_height = 1000;//drawing buffer
		media.color = 8;
		media.monochrome = 0;
		media.color_index = 256;
		media.resolution = device_resolution_dpi();
	}

	// litehtml::document_container and container_cairo_ft members

	//caption is text from <head><title>text</title></head>
	virtual	void set_caption(const litehtml::tchar_t* caption)
	{
		fprintf(stderr, "set_caption is not implemented\n");
	}

	virtual	void set_base_url(const litehtml::tchar_t* base_url)
	{
		fprintf(stderr, "set_base_url is not implemented\n");
	}

	void import_css(litehtml::tstring& text, const litehtml::tstring& url, litehtml::tstring& baseurl)
	{
		const std::string path = path_root_resources() + url;
		std::ifstream t1(path);
		if (t1.is_open()) {
			text = std::string((std::istreambuf_iterator<char>(t1)), std::istreambuf_iterator<char>());
		}
		else {
			fprintf(stderr, "Error css reading file path=%s\n", path.c_str());
		}
	}

	virtual	void on_anchor_click(const litehtml::tchar_t* url, const litehtml::element::ptr& el)
	{
		fprintf(stderr, "on_anchor_click is not implemented\n");
	}

	virtual	void set_cursor(const litehtml::tchar_t* cursor)
	{
		fprintf(stderr, "set_cursor is not implemented\n");
	}
};

//specific device container
class spec_device_container : public device_container
{
public:
	virtual ~spec_device_container() {};
private:
	virtual int device_width_px() const {
		return 384;
	}

	virtual int device_resolution_dpi() const {
		return 20;
	}

	virtual std::string path_root_resources() const {
		return "html/";
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	//demo Cairo and FreeType from https://www.lemoda.net/c/free-type/index.html "An example of Cairo and FreeType in C"
	{
		const int size = 200;
		cairo_surface_t* cairo_out_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size, size);
		cairo_t* c = cairo_create(cairo_out_surface);
		const char * filename = "html/arial.ttf";
		FT_Library ft_library;
		{
			const FT_Error ft_status = FT_Init_FreeType(&ft_library);
			if (ft_status != 0) {
				fprintf(stderr, "Error %d opening FreeType library\n", ft_status);
				exit(EXIT_FAILURE);
			}
		}
		FT_Face ft_face;
		{
			const FT_Error ft_status = FT_New_Face(ft_library, filename, 0, &ft_face);
			if (ft_status != 0) {
				fprintf(stderr, "Error %d opening %s.\n", ft_status, filename);
				exit(EXIT_FAILURE);
			}
		}
		cairo_font_face_t* fnt = cairo_ft_font_face_create_for_ft_face(ft_face, 0);
		cairo_set_font_face(c, fnt);
		cairo_set_font_size(c, size / 3);
		cairo_set_source_rgb(c, 0, 0, 0);
		cairo_move_to(c, size / 6, size / 3);
		cairo_show_text(c, "\xd0\xae\xd0\xb3");
		cairo_set_source_rgb(c, 0.5, 0.5, 0);
		cairo_move_to(c, size / 6, 5 * size / 6);
		cairo_show_text(c, "\xd0\x81\xd0\xb6");
		FT_Done_FreeType(ft_library);
		cairo_surface_write_to_png(cairo_out_surface, "free-type.png");
	}
	//demo cairo image resize
	// See: 
	// https://progtips.ru/texnologii-programmirovaniya/graficheskaya-biblioteka-cairo.html
	// http://www.opennet.ru/docs/RUS/tutorial_cairo/
	{
	const int w_new_size_px = 50;
	const int h_new_size_px = 150;
	cairo_surface_t* cairo_out_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w_new_size_px, h_new_size_px);
	cairo_status_t status = cairo_surface_status(cairo_out_surface);
	cairo_t* cr = cairo_create(cairo_out_surface);//context
	cairo_surface_t *image = cairo_image_surface_create_from_png("html/image.png");
	status = cairo_surface_status(image);
	//cairo_save Makes a copy of the current state of cr and saves it on an internal stack of saved states for cr . When cairo_restore() is called, cr will be restored to the saved state. 
	cairo_save(cr);
	//cairo_translate Modifies the current transformation matrix (CTM) by translating the user-space origin by (tx , ty ). 
	cairo_translate(cr, 0, 0);//offset px
	//cairo_scale Modifies the current transformation matrix (CTM) by scaling the X and Y user-space axes by sx and sy respectively. 
	int w_image_px = cairo_image_surface_get_width(image);
	int h_image_px = cairo_image_surface_get_height(image);
	cairo_scale(cr, double(w_new_size_px) / w_image_px, double(h_new_size_px) / h_image_px);
	// note: it's important to set the source after setting up the
	// user space transformation.
	cairo_set_source_surface(cr, image, 0, 0);
	cairo_paint(cr);
	cairo_restore(cr);
	cairo_surface_write_to_png(cairo_out_surface, "out-resize.png");
	cairo_surface_destroy(image);
}

	//Demo rendering html
	// manuals: https://github.com/litehtml/litehtml/wiki/How-to-use-litehtml
	// litebrowser example: void CHTMLViewWnd::OnPaint( simpledib::dib* dib, LPRECT rcDraw )
	//const std::string html_text = "<h1>Something work 2!!!</h1>";
	std::ifstream t1("html/some.html");
	const std::string html_text((std::istreambuf_iterator<char>(t1)), std::istreambuf_iterator<char>());
	typedef std::shared_ptr<litehtml::document_container>	document_container_ptr;
	document_container_ptr container;//need removed after doc
	container.reset(new spec_device_container());
	litehtml::context ctx;
	std::ifstream t2("html/master.css");
	if (!t2.is_open()) {
		fprintf(stderr, "Error opening html/master.css\n");
		exit(EXIT_FAILURE);
	}
	const std::string css((std::istreambuf_iterator<char>(t2)), std::istreambuf_iterator<char>());
	ctx.load_master_stylesheet(css.data());
	//EnterCriticalSection(&m_sync);
	litehtml::document::ptr	doc = litehtml::document::createFromUTF8(html_text.c_str(), container.get(), &ctx);
	//render HTML elements
	const int max_width = 384;
	doc->render(max_width);
	//find the width and height of the rendered document
	const int doc_width = doc->width();
	const int doc_height = doc->height();
	{
		//by project litebrowser example: void CHTMLViewWnd::OnPaint( simpledib::dib* dib, LPRECT rcDraw )
		const int left = 0;
		const int top = 0;
		const int width = doc_width;
		const int height = doc_height;
		cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
		cairo_t* cr = cairo_create(surface);
		cairo_rectangle(cr, left, top, width, height);
		cairo_clip(cr);
		cairo_set_source_rgb(cr, 1, 1, 1);
		cairo_paint(cr);
		litehtml::uint_ptr hdc = (litehtml::uint_ptr)cr;
		//drawing
		{
			const litehtml::position clip(left, top, width, height);
			doc->draw(hdc, left, top, &clip);
		}

		//save to file
		const cairo_status_t save_result = cairo_surface_write_to_png(surface, "out.png");
		//destory
		cairo_destroy(cr);
		cairo_surface_destroy(surface);
	}
	return 0;
}


