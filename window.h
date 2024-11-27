#ifndef WINDOW_H
#define WINDOW_H

#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  unsigned long colours[5];
 public:
  Xwindow(int width=500, int height=500);
  ~Xwindow();

  enum {White=0, Black, Red, Green, Blue, Yellow, Magenta, Cyan};

  int getWidth() const;
  int getHeight() const;

  void fillRectangle(int x, int y, int width, int height, int colour=Black);
  void drawString(int x, int y, std::string msg);

  void drawLine(int x1, int y1, int x2, int y2, int colour=Black);
};

#endif
