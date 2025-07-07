#include "DearImKit/base/panel.h"

#include <string>

DearImKit::Panel::Panel(const std::string &name) : m_name(name) {};

std::string DearImKit::Panel::getName() const {
    return m_name;
}

bool DearImKit::Begin(const DearImKit::Panel &panel, bool *p_open, ImGuiWindowFlags flags) {
    return ImGui::Begin(panel.getName().c_str(), p_open, flags);
}