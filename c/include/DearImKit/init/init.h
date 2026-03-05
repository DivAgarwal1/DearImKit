#ifndef C_INIT_H
#define C_INIT_H

extern "C" {

struct DearImKit_BackgroundColor {
    float r = 0.2, g = 0.3, b = 0.3, a = 1.0;
};

int DearImKit_SetupApp(const char* app_name, void (*at_start)(void), void (*during_loop)(void), DearImKit_BackgroundColor background_color);

}

#endif
