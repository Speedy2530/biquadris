// window.cc
#include "window.h"
#include <X11/Xutil.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

// Constructor
Xwindow::Xwindow(int width, int height) : width(width), height(height) {
    std::cerr << "Initializing Xwindow with width: " << width << ", height: " << height << std::endl;
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        throw "Cannot open display";
    }

    int screen = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, screen), 10, 10, width, height, 1,
                           BlackPixel(d, screen), WhitePixel(d, screen));
    if (!w) {
        throw "Failed to create X window";
    }

    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapWindow(d, w);

    gc = XCreateGC(d, w, 0, 0);
    if (!gc) {
        throw "Failed to create graphics context";
    }

    // Initialize color map
    colorMap[White] = WhitePixel(d, DefaultScreen(d));
    colorMap[Black] = BlackPixel(d, DefaultScreen(d));

    // Define color names corresponding to enum indices
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
        Colormap colormap = DefaultColormap(d, DefaultScreen(d));
        if (!XParseColor(d, colormap, colorNames[i - Red], &xcolor)) {
            throw "Failed to parse color";
        }
        if (!XAllocColor(d, colormap, &xcolor)) {
            throw "Failed to allocate color";
        }
        colorMap[i] = xcolor.pixel;
        std::cerr << "Allocated color " << colorNames[i - Red] << " for enum index " << i << std::endl;
    }

    XFontStruct *font = XLoadQueryFont(d, "-*-helvetica-bold-r-normal--*-120-*-*-*-*-*-*");
    if (font) {
        XSetFont(d, gc, font->fid);
    }
}

// Destructor
Xwindow::~Xwindow() {
    if (gc) {
        XFreeGC(d, gc);
    }
    if (w) {
        XDestroyWindow(d, w);
    }
    if (d) {
        XCloseDisplay(d);
    }
}

// Color mapping method
unsigned long Xwindow::getColor(int color) {
    if (color >= White && color < NumColors) {
        return colorMap[color];
    }
    return WhitePixel(d, DefaultScreen(d));
}

// Fill a rectangle with a specific color
void Xwindow::fillRectangle(int x, int y, int width, int height, int color) {
    XSetForeground(d, gc, getColor(color));
    XFillRectangle(d, w, gc, x, y, width, height);
}

// Draw a rectangle border with a specific color
void Xwindow::drawRectangle(int x, int y, int width, int height, int color) {
    XSetForeground(d, gc, getColor(color));
    XDrawRectangle(d, w, gc, x, y, width, height);
}

// Draw a line with a specific color
void Xwindow::drawLine(int x1, int y1, int x2, int y2, int colour) {
    XSetForeground(d, gc, getColor(colour));
    XDrawLine(d, w, gc, x1, y1, x2, y2);
}

// Draw a string at a specific location
void Xwindow::drawString(int x, int y, const std::string &msg) {
    XSetForeground(d, gc, BlackPixel(d, DefaultScreen(d)));
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
}

// Flush the output buffer and redraw the window
void Xwindow::redraw() {
    XFlush(d);
}

