#ifndef C_INIT_H
#define C_INIT_H

extern "C" {
struct BackgroundColor {
    float r, g, b, a;
};

int DearImKit_SetupApp(const char* app_name, void (*at_start)(void), void (*during_loop)(void), BackgroundColor background_color);

}

#endif
