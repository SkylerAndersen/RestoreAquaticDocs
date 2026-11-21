cmake_minimum_required(VERSION 3.23)

project(readmd)

set(FLTK_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(FLTK_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(fltk)

add_library(font_importer)

if(APPLE)
	target_link_libraries(font_importer
		PUBLIC
			"-framework CoreText"
			"-framework CoreFoundation"
	)
elseif(UNIX)
	find_package(Fontconfig REQUIRED)
	target_link_libraries(my_font_loader
		PUBLIC
			Fontconfig::Fontconfig
	)
endif()

target_sources(font_importer
	PRIVATE
		./src/font_importer.cpp
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS
			include
		FILES
			include/font_importer.h
)
			

add_executable(readmd)

target_sources(readmd
	PRIVATE
		./src/main.cpp
)

target_link_libraries(readmd
	PRIVATE
		fltk::fltk
		font_importer
)
