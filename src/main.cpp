#include <filesystem>
#include <iostream>
#include <string>

#include <xcb/xcb.h>
#include <xcb/xproto.h>

#include <X11/Xlib.h>

#include "config/config.h"

#include "xdg.hpp"

//int check_x();
//int check_other_wm();
void autostart(Config conf);

int main() {

#ifndef __DEBUG__
    Config config(std::filesystem::canonical("./"));
#else
    std::string path = xdg::ConfigHomeDir();
    path += "/swm/";
    Config config(std::filesystem::canonical(path));
#endif

    // TODO: Turn this into `int check_x()`
    Display* disp = XOpenDisplay(NULL);
    if (!disp) {
        // Can't really start an X window manager without X.
        std::cerr << "X is not running, please start X first!" << std::endl;
        return 1;
    }
    XCloseDisplay(disp);
    free(disp); // Not sure if X frees this pointer, going to do it anyways until told otherwise.

    xcb_connection_t* connection = xcb_connect(NULL, NULL);

    // grab first screen
    const xcb_setup_t* setup = xcb_get_setup(connection);
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t* screen = iter.data;

    // TODO: Turn this into `int check_other_wm()`
    xcb_generic_error_t* error;
    unsigned int mask[1] = {XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT};
    error = xcb_request_check(connection, xcb_change_window_attributes_checked(connection, screen->root, XCB_CW_EVENT_MASK, mask));
    xcb_flush(connection);
    if (error) {
        std::cerr << "Another WM is running, please close out of it first!" << std::endl;
        return 1;
    }

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

// I stole this from a DWM patch, There has got to be a better way to do this!
void autostart(Config conf) {
    // The & daemonizes the shell script, we need this unless we want to be blocked from starting
    std::string autostart_command = "cd " + conf.path + "; sh ./autostart.sh &";
    system(autostart_command.c_str());
}