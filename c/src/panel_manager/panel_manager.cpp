#include "../../include/DearImKit/panel_manager/panel_manager.h"

#include <functional>
#include <string>

#include "../panel.h"

#include "DearImKit/base/base.h"
#include "DearImKit/panel_manager/panel_manager.h"

void DearImKit_AddPanel(const char* name, int (*draw)(void*), void* state) {
    DearImKit::AddPanel<ExternPanel>(name, draw, state);
}

void DearImKit_QueueError(const char *panel_name, const char *title, const char *message) {
    ExternPanel panel(panel_name, nullptr, nullptr);
    DearImKit::QueueError(panel, title, message);
}
