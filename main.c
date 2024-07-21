#include <X11/Xlib.h>

int main(void) {
    Display *display = XOpenDisplay(":1");

    int screen = DefaultScreen(display);
    Window root_window = RootWindow(display, 0);
    unsigned long valuemask = CWBackPixel | CWBorderPixel | CWEventMask;
    XSetWindowAttributes window_attributes;

    window_attributes.background_pixel = WhitePixel(display, 0);
    window_attributes.border_pixel = BlackPixel(display, 0);
    window_attributes.event_mask = ExposureMask | KeyPressMask;

    Window new_window = XCreateWindow(display, root_window, 500, 500, 500, 300, 10, CopyFromParent, InputOutput, CopyFromParent, valuemask, &window_attributes);

    XStoreName(display, new_window, "My First Window");

    XMapWindow(display, new_window);

    XEvent event;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            XFillRectangle(display, new_window, DefaultGC(display, screen), 20, 20, 10, 10);
        }
        else if (event.type == KeyPress) {
            break;
        }
    }

    XCloseDisplay(display);
    return 0;
}