#include "base/panel.h"

#include <string>

DearImKit::Panel::Panel(const std::string &name) : m_name(name) {};

std::string DearImKit::Panel::getName() const {
    return m_name;
}