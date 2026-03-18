#ifndef C_INIT_H
#define C_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DearImKit_BackgroundColor {
    float r, g, b, a;
} DearImKit_BackgroundColor;

static const DearImKit_BackgroundColor DEARIMKIT_BACKGROUND_COLOR_DEFAULT = { 0.2f, 0.3f, 0.3f, 1.0f };

int DearImKit_SetupApp(const char* app_name, void (*at_start)(void), void (*during_loop)(void), DearImKit_BackgroundColor background_color);

#ifdef __cplusplus
}
#endif

#endif
