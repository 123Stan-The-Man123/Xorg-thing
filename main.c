#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>

#define NIL (0)

int main(void) {
    Display *display = XOpenDisplay(NULL);

    if (display == NULL) {
        printf("Could not open display.\n");
        return 1;
    }

    Window new_window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 500, 300, 0, BlackPixel(display, DefaultScreen(display)), BlackPixel(display, DefaultScreen(display)));

    XSelectInput(display, new_window, StructureNotifyMask);

    XMapWindow(display, new_window);

    GC gc = XCreateGC(display, new_window, 0, NIL);

    XSetForeground(display, gc, WhitePixel(display, DefaultScreen(display)));

    for (;;) {
        XEvent e;
        XNextEvent(display, &e);
        if (e.type == MapNotify) {
            break;
        }
    }

    XDrawLine(display, new_window, gc, 10, 60, 180, 20);

    XFlush(display);

    sleep(10);

    XCloseDisplay(display);
    return 0;
}