#include "base/base.h"

#include "../panel.h"
#include "DearImKit/base/base.h"

extern "C" {

bool DearImKit_Begin(void* panel, bool* p_open, int flags) {
    return DearImKit::Begin(*static_cast<ExternPanel*>(panel), p_open, flags);
}

void DearImKit_Image(const char* filename, DearImKit_Size size) {
    DearImKit::Image(filename, DearImKit::Size{size.width, size.height});
}

void DearImKit_ImageBackground(const char* filename) {
    DearImKit::ImageBackground(filename);
}
}
