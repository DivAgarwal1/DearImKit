#ifndef PANEL_H
#define PANEL_H

#include <string>

#include "imgui.h"

namespace DearImKit {
    /**
     * @brief The base class for any panel to display.
     *
     * Override the pure virtual draw() function to display content.
     * Call the Panel(std::string name) constructor with your derived class constructors.
     *
     */
    class Panel {
    public:
        Panel(const std::string &name);

        /**
         * @brief Draws panel content.
         *
         * Use ImGui logic to create content.
         *
         * @return bool - Whether the panel should stay open
         */
        virtual bool draw() = 0;

        virtual std::string getName() const final;

        virtual ~Panel() = default;

    private:
        std::string m_name;
    };

    bool Begin(const DearImKit::Panel &panel, bool *p_open = nullptr, ImGuiWindowFlags flags = 0);

    void Image(std::string filename, int width, int height);

    void DearImKit::ImageBackground(std::string filename);
} // namespace DearImKit

#endif // PANEL_H