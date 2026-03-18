#include "../../include/DearImKit/base/base.h"

#include "../panel.h"
#include "DearImKit/base/base.h"
#include <functional>

int DearImKit_Begin(const char* panel_name, int* p_open, int flags) {
    bool open_bool = p_open ? *p_open > 0 : false;
    ExternPanel panel(panel_name, nullptr, nullptr);
    int should_draw = DearImKit::Begin(panel, p_open ? &open_bool : nullptr, flags) ? 1 : 0;
    if (p_open) *p_open = open_bool ? 1 : 0;
    return should_draw;
}

void DearImKit_Image(const char* filename, DearImKit_Size size) {
    DearImKit::Image(filename, DearImKit::Size{size.width, size.height});
}

void DearImKit_ImageBackground(const char* filename) {
    DearImKit::ImageBackground(filename);
}
