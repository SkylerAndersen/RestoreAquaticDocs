#include <FL/FL.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Help_view.H>
#include <FL/Fl_Box.H>
#include <iostream>
#include <font_importer.h>

int main (void) {
	if (!font_importer::import("inter.ttf")) {
		std::cerr << "Failed to import" << std::endl;
		return 1;
	}
	Fl::set_font(FL_FREE_FONT, "Inter");

	Fl_Double_Window* win = new Fl_Double_Window(680, 400, "readmd");
	Fl_Help_View* view = new Fl_Help_View(10, 10, 660, 380);

	view->textsize(24);
	view->textfont(FL_FREE_FONT);
	view->value("<p>test</p>");
	view->box(FL_FLAT_BOX);
	Fl::background2(36, 49, 79);

	win->color(fl_rgb_color(36, 49, 79));
	win->end();
	win->resizable(view);
	win->show();

	int status = Fl::run();

	font_importer::release_font();

	return status;
}
