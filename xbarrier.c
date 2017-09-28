#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>


// to compile this run:
// sudo apt install build-essential pkg-config libx11-dev libxtst-dev
// gcc xbarrier.c $(pkg-config --cflags --libs x11 xfixes) -o xbarrier


int main(int argc, char **argv)
{
    Display *dpy;
    PointerBarrier b;
    int x1, y1, x2, y2, dirs;

    if (argc != 6) {
      printf("Usage: xbarrier x1 y1 x2 y2 dirs\ndirs: PositiveX    1\n      PositiveY    2\n      NegativeX    4\n      NegativeY    8\n");
      return 1;
    }

    dpy = XOpenDisplay(NULL);
    if (!dpy) {
	return 1;
    }

    x1 = atoi(argv[1]);
    y1 = atoi(argv[2]);
    x2 = atoi(argv[3]);
    y2 = atoi(argv[4]);
    dirs = atoi(argv[5]);

    b = XFixesCreatePointerBarrier(dpy, DefaultRootWindow(dpy), x1, y1, x2, y2, dirs, 0, NULL);
    XSync(dpy, 1);

    if (!b) {
	return 1;
    }

    pause();

    XFixesDestroyPointerBarrier(dpy, b);

    XCloseDisplay(dpy);
    return 0;
}
