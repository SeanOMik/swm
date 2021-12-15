#include <iostream>
#include <string>

#include <xcb/xcb.h>
#include <xcb/xproto.h>

#include <X11/Xlib.h>

#include "config/config.h"

#include "xdg.hpp"

int main() {

#ifndef __DEBUG__
    Config config("config.toml");
#else
    std::string path = xdg::ConfigHomeDir();
    path += "/swm/config.toml";
    Config config(path);
#endif

    // Check if X is running
    Display* disp = XOpenDisplay(NULL);
    if (!disp) {
        // Can't really start an X window manager without X.
        std::cerr << "X is not running, please start X first!";
        return 1;
    }
    XCloseDisplay(disp);
    free(disp); // Not sure if X frees this pointer, going to do it anyways until told otherwise.

    // opens connection to display server (xorg)
    xcb_connection_t* connection = xcb_connect(NULL, NULL);

    // grab first screen
    const xcb_setup_t* setup = xcb_get_setup(connection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t* screen = iter.data;

    // create basic window
    xcb_window_t window = xcb_generate_id(connection);
    xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, screen->root, 0, 0, 150, 150, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, screen->root_visual, 0, NULL);
    xcb_map_window(connection, window);
    xcb_flush(connection);
    
    std::cout << "Press enter to resume ";
    std::cin.get();

    xcb_disconnect(connection);

    return 0;
}