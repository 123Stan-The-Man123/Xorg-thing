#include <stdio.h>
#include <X11/Xlib.h>

int main(void) {
    Display *dpy = XOpenDisplay(NULL);

    if (dpy == NULL) {
        printf("Could not open display.\n");
        return 1;
    }

    int scr = XDefaultScreen(dpy);

    Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 500, 300, 0, WhitePixel(dpy, scr), BlackPixel(dpy, scr));

    XSelectInput(dpy, w, ExposureMask | KeyPressMask);
    
    XMapWindow(dpy, w);

    for(;;) {
        XEvent e;
        XNextEvent(dpy, &e);
        if (e.type == Expose) {
            XFillRectangle(dpy, w, DefaultGC(dpy, scr), 20, 20, 10, 10);
        }
        if (e.type == KeyPress) {
            break;
        }
    }

    XCloseDisplay(dpy);
    return 0;
}
