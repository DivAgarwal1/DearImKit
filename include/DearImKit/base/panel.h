#ifndef PANEL_H
#define PANEL_H

#include <string>

#include "imgui.h"

namespace DearImKit {
    struct Size {
        int width = -1;
        int height = -1;
    };

    /**
     * @brief The base class for any panel to display.
     *
     * Override the pure virtual `draw()` function to display content.
     * Call the `Panel(std::string name)` constructor with your derived class constructors.
     *
     */
    class Panel {
    public:
        Panel(const std::string& name);

        /**
         * @brief Draws panel content.
         *
         * Use ImGui logic to create content.
         *
         * @return `bool` - Whether the panel should stay open
         */
        virtual bool draw() = 0;

        virtual std::string getName() const final;

        virtual ~Panel() = default;

    private:
        std::string m_name;
    };

    /**
     * @brief Starts drawing an ImGui window.
     * Use within the `draw()` function of a panel.
     *
     * @param panel
     * A reference to the panel calling Begin,
     * usually pass `*this`.
     * @param p_open
     * A `bool` pointer representing where to store if the ImGui window has been closed.
     * In order to stop rendering an ImGui window that has been closed, return from `draw()` the variable whose address you pass here.
     * Pass `nullptr` or leave as default to make an uncloseable ImGui window.
     * @param flags
     * `ImGuiWindowFlags` for the created ImGui window.
     * @return true
     * @return false
     */
    bool Begin(const DearImKit::Panel& panel, bool* p_open = nullptr, ImGuiWindowFlags flags = 0);

    void Image(std::string filename, DearImKit::Size size);

    void ImageBackground(std::string filename);
} // namespace DearImKit

#endif // PANEL_H