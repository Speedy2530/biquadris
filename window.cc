// window.cc
#include "window.h"
#include <X11/Xutil.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

// Constructor
Xwindow::Xwindow(int width, int height) 
    : width(width), height(height), 
      d(nullptr, DisplayDeleter()), 
      font_info(nullptr, FontDeleter(nullptr)), // Temporarily initialize with nullptr
      font_title_info(nullptr, FontDeleter(nullptr)) // Initialize with nullptr
{
    // Open the display
    d.reset(XOpenDisplay(nullptr));
    if (!d) {
        throw std::runtime_error("Cannot open display");
    }

    int screen = DefaultScreen(d.get());
    w = XCreateSimpleWindow(d.get(), RootWindow(d.get(), screen), 10, 10, width, height, 1,
                           BlackPixel(d.get(), screen), WhitePixel(d.get(), screen));
    if (!w) {
        throw std::runtime_error("Failed to create X window");
    }

    XSelectInput(d.get(), w, ExposureMask | KeyPressMask);
    XMapWindow(d.get(), w);

    gc = XCreateGC(d.get(), w, 0, 0);
    if (!gc) {
        throw std::runtime_error("Failed to create graphics context");
    }

    // Initialize color map
    colorMap[White] = WhitePixel(d.get(), screen);
    colorMap[Black] = BlackPixel(d.get(), screen);

    // Define color names corresponding to enum indices starting from Red
    const char* colorNames[] = {
        "#FF0000", // Red
        "#00FF00", // Green
        "#0000FF", // Blue
        "#FFFF00", // Yellow
        "#800080", // Purple
        "#00FFFF", // Cyan
        "#FFA500", // Orange
        "#ADD8E6", // LightBlue
        "#006400", // DarkGreen
        "#FFB7CE", // Pink
        "#A52A2A", // Brown
        "#808080"  // Grey
    };
    for (int i = Red; i < NumColors; ++i) {
        XColor xcolor;
        Colormap colormap = DefaultColormap(d.get(), screen);
        if (!XParseColor(d.get(), colormap, colorNames[i - Red], &xcolor)) {
            throw std::runtime_error("Failed to parse color");
        }
        if (!XAllocColor(d.get(), colormap, &xcolor)) {
            throw std::runtime_error("Failed to allocate color");
        }
        colorMap[i] = xcolor.pixel;
        // Optional: Debugging output
        // std::cerr << "Allocated color " << colorNames[i - Red] << " for enum index " << i << std::endl;
    }


    // Load regular font
    const char *regular_fontname = "-*-helvetica-bold-r-normal--18-*-*-*-*-*-*-*";
    XFontStruct *loaded_regular_font = XLoadQueryFont(d.get(), regular_fontname);
    if (!loaded_regular_font) {
        std::cerr << "Unable to load font " << regular_fontname << ". Attempting to load default font.\n";
        // Attempt to load a default font
        loaded_regular_font = XQueryFont(d.get(), XGContextFromGC(gc));
        if (!loaded_regular_font) {
            throw std::runtime_error("Failed to load default font");
        }
    }

    // Assign the loaded regular font to the unique_ptr with the correct deleter
    font_info = std::unique_ptr<XFontStruct, FontDeleter>(loaded_regular_font, FontDeleter(d.get()));

    // Load title font
    const char *title_fontname = "-*-helvetica-bold-r-normal--24-*-*-*-*-*-*-*"; // Larger size
    XFontStruct *loaded_title_font = XLoadQueryFont(d.get(), title_fontname);
    if (!loaded_title_font) {
        std::cerr << "Unable to load title font " << title_fontname << ". Using regular font as fallback.\n";
        loaded_title_font = loaded_regular_font; // Fallback to regular font
    } else {
        // Assign the loaded title font to the unique_ptr with the correct deleter
        font_title_info = std::unique_ptr<XFontStruct, FontDeleter>(loaded_title_font, FontDeleter(d.get()));
    }

    // Set the regular font in the graphics context
    XSetFont(d.get(), gc, font_info->fid);
}

// Destructor
Xwindow::~Xwindow() = default;

// Color mapping method
unsigned long Xwindow::getColor(int color) {
    if (color >= White && color < NumColors) {
        return colorMap[color];
    }
    return WhitePixel(d.get(), DefaultScreen(d.get()));
}

// Fill a rectangle with a specific color
void Xwindow::fillRectangle(int x, int y, int width, int height, int color) {
    XSetForeground(d.get(), gc, getColor(color));
    XFillRectangle(d.get(), w, gc, x, y, width, height);
}

// Draw a rectangle border with a specific color
void Xwindow::drawRectangle(int x, int y, int width, int height, int color) {
    XSetForeground(d.get(), gc, getColor(color));
    XDrawRectangle(d.get(), w, gc, x, y, width, height);
}

// Draw a line with a specific color
void Xwindow::drawLine(int x1, int y1, int x2, int y2, int colour) {
    XSetForeground(d.get(), gc, getColor(colour));
    XDrawLine(d.get(), w, gc, x1, y1, x2, y2);
}

// Draw a string at a specific location
void Xwindow::drawString(int x, int y, const std::string &msg, bool isTitle) {
    if (isTitle && font_title_info) {
        XSetFont(d.get(), gc, font_title_info->fid);
    } else {
        XSetFont(d.get(), gc, font_info->fid);
    }

    if (isTitle) {
        XSetForeground(d.get(), gc, BlackPixel(d.get(), DefaultScreen(d.get()))); // Customize as needed
    } else {
        XSetForeground(d.get(), gc, BlackPixel(d.get(), DefaultScreen(d.get())));
    }

    XDrawString(d.get(), w, gc, x, y, msg.c_str(), msg.length());

    // Reset to regular font if was using title font
    if (isTitle && font_info) {
        XSetFont(d.get(), gc, font_info->fid);
    }
}

// Flush the output buffer and redraw the window
void Xwindow::redraw() {
    XFlush(d.get());
}

// Calculate the width of the given text in pixels
int Xwindow::getTextWidth(const std::string &text, bool isTitle) {
    int direction, ascent, descent;
    XCharStruct overall;

    if (isTitle && font_title_info) {
        XTextExtents(font_title_info.get(), text.c_str(), text.length(), &direction, &ascent, &descent, &overall);
    } else {
        XTextExtents(font_info.get(), text.c_str(), text.length(), &direction, &ascent, &descent, &overall);
    }

    return overall.width;
}
