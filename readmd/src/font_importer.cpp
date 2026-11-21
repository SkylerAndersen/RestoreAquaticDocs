#include <font_importer.h>

namespace font_importer {
const char* TTF_PATH = nullptr;

bool import (const char* ttf_file_path) {
	// save the TTF file path for later
	if (TTF_PATH != nullptr) {
		free((void*)TTF_PATH);
		TTF_PATH = nullptr;
	}
	
	int len = std::strlen(ttf_file_path) + 1;
	char* temp = (char*) malloc(sizeof(char) * len);
	std::strcpy(temp, ttf_file_path);
	temp[len-1] = '\0';

	TTF_PATH = (const char*) temp;

	// handle importing with the win32 API if it is a viable route
	#ifdef _WIN32
	return AddFontResourceExA(TTF_PATH, FR_PRIVATE, 0) > 0;
	#endif

	// handle importing with fontconfig if available
	#ifdef __linux__
	return FcConfigAppFontAddFile(FcConfigGetCurrent(),
			(const FcChar8*)TTF_PATH) == FcTrue;
	#endif

	// handle importing with CoreText
	#ifdef __APPLE__
	CFURLRef url = CFURLCreateFromFileSystemRepresentation(NULL,
			(const UInt8*)TTF_PATH, std::strlen(TTF_PATH), false);
	bool status = CTFontManagerRegisterFontsForURL(url,
				kCTFontManagerScopeProcess, NULL);
	CFRelease(url);
	return status;
	#endif
}

void release_font () {
	#ifdef _WIN32
	RemoveFontResourceExA(TTF_PATH, FR_PRIVATE, 0);
	#endif
}
}
