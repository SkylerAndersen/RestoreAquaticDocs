#ifndef FONT_IMPORTER_H
#define FONT_IMPORTER_H

#include <iostream>
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <fontconfig/fontconfig.h>
#endif

#ifdef __APPLE__
#include <CoreText/CoreText.h>
#endif

namespace font_importer {
	bool import (const char* ttf_file_path);
	void release_font();
}

#endif
