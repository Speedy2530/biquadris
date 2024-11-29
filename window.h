// window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>
#include <string>
#include <memory>

// Custom deleter for Display*
struct DisplayDeleter {
    void operator()(Display* d) const {
        if (d) {
            XCloseDisplay(d);
        }
    }
};

// Custom deleter for XFontStruct*
struct FontDeleter {
    Display* d; // Reference to the Display* for proper deallocation

    // Constructor to initialize the Display* reference
    FontDeleter(Display* display) : d(display) {}

    void operator()(XFontStruct* font) const {
        if (font) {
            XFreeFont(d, font);
        }
    }
};

class Xwindow {
public:
    // Enum for colors should be public to allow external access
    enum {
        White,
        Black,
        Red,
        Green,
        Blue,
        Yellow,
        Purple,
        Cyan,
        Orange,
        LightBlue,
        DarkGreen,
        Pink,
        Brown,
        Grey,
        NumColors
    };

    Xwindow(int width, int height);
    ~Xwindow();

    void fillRectangle(int x, int y, int width, int height, int color);
    void drawRectangle(int x, int y, int width, int height, int color);
    void drawLine(int x1, int y1, int x2, int y2, int colour = Black);
    void drawString(int x, int y, const std::string &msg, bool isTitle = false);
    void redraw();

    int getTextWidth(const std::string &text, bool isTitle = false);
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Define color mapping
    unsigned long getColor(int color);

private:
    int width;
    int height;
    Window w;
    GC gc;
    unsigned long colorMap[NumColors]; // Updated to match the enum size

    // Unique pointers with custom deleters
    std::unique_ptr<Display, DisplayDeleter> d;
    std::unique_ptr<XFontStruct, FontDeleter> font_info;
    std::unique_ptr<XFontStruct, FontDeleter> font_title_info; // New font for title

    // Disable copy and assignment to maintain unique ownership
    Xwindow(const Xwindow&) = delete;
    Xwindow& operator=(const Xwindow&) = delete;
};

#endif

