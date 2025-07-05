#include "panelmanager/panelmanager.h"

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "imgui.h"

#include "base/panel.h"

static std::list<std::unique_ptr<DearImKit::Panel>> panels_to_display_p;
static std::vector<std::pair<std::string, std::string>> queued_errors;
static std::list<std::pair<std::string, std::string>> error_msgs;

void DrawModalPopup(std::pair<std::string, std::string> error, bool *p_open) {
    ImGuiWindowFlags flags = 0;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoCollapse;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoScrollbar;
    flags |= ImGuiWindowFlags_NoScrollWithMouse;
    if (ImGui::BeginPopupModal(error.first.c_str(), p_open, flags)) {
        ImGui::Text("%s", error.second.c_str());
        ImGui::EndPopup();
    }
}

void DearImKit::QueueError(const DearImKit::Panel &panel, const std::string &title, const std::string &message) {
    queued_errors.emplace_back(panel.getName() + ": " + title, message);
}

void DearImKit::detail::InsertPanel(DearImKit::Panel *p_panel_to_add) {
    panels_to_display_p.emplace_back(p_panel_to_add);
}

void DearImKit::detail::Render() {
    for (auto it = panels_to_display_p.begin(); it != panels_to_display_p.end(); ++it) {
        if (!(*it)->draw()) {
            it = panels_to_display_p.erase(it);
            --it;
        }
    }

    for (auto it = queued_errors.begin(); it != queued_errors.end(); ++it) {
        ImGui::OpenPopup(it->first.c_str());
        error_msgs.push_back(std::move(*it));
    }
    queued_errors.clear();

    for (auto it = error_msgs.begin(); it != error_msgs.end(); ++it) {
        bool pop_open = true;

        DrawModalPopup(*it, &pop_open);

        if (!pop_open) {
            it = error_msgs.erase(it);
            --it;
        }
    }
}