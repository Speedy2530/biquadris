// window.h
#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>
#include <string>

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

private:
    Display *d;
    Window w;
    GC gc;
    int width;
    int height;
    unsigned long colorMap[15]; // To store pixel values for colors

    XFontStruct *font_info;

public:
    Xwindow(int width, int height);
    ~Xwindow();

    void fillRectangle(int x, int y, int width, int height, int color);
    void drawRectangle(int x, int y, int width, int height, int color);
    void drawLine(int x1, int y1, int x2, int y2, int colour = Black);
    void drawString(int x, int y, const std::string &msg);
    void redraw();

    int getTextWidth(const std::string &text);
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    // Define color mapping
    unsigned long getColor(int color);
};

#endif

