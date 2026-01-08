#include "init.h"
#include <tuple>

#include "DearImKit/init/init.h"

int DearImKit_SetupApp(const char *app_name, void (*at_start)(), void (*during_loop)(), BackgroundColor background_color) {
    return DearImKit::SetupApp(app_name, at_start, during_loop, std::make_tuple(background_color.r, background_color.g, background_color.b, background_color.a));
}
