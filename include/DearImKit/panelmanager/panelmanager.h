#ifndef PANELMANAGER_H
#define PANELMANAGER_H

#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "DearImKit/base/panel.h"

namespace DearImKit {
    namespace detail {
        void InsertPanel(DearImKit::Panel *p_panel_to_add);
        void Render();
    } // namespace detail

    /**
     * @brief Adds a panel to the be rendered.
     *
     * The panel will be rendered every subsequent frame until it should be destroyed (its draw() function returns false).
     *
     * @tparam T
     * The class of the panel to add,
     * must derive from DearImKit::Panel
     * @tparam Args
     * Types for arguments to constructor of T,
     * does not need to be specified
     * @param args
     * Arguments to constructor of T
     */
    template <typename T, typename... Args>
    void AddPanel(Args &&...args) {
        static_assert(std::is_base_of<DearImKit::Panel, T>::value, "T must be derived from DearImKit::Panel");
        DearImKit::detail::InsertPanel(new T(std::forward<Args>(args)...));
    }

    /**
     * @brief Prepares an error popup to be displayed on the next frame.
     *
     * The popup will persist until closed by pressing the close button.
     * Use to interrupt users and report an error (e.g. password field not filled out).
     *
     * @param panel
     * A reference to the panel queueing the error
     * @param title
     * The title of the error,
     * will be displayed as the title of the popup window
     * @param message
     * The body of the error,
     * will be displayed as the main text of the popup window
     */
    void QueueError(const DearImKit::Panel &panel, const std::string &title, const std::string &message);

} // namespace DearImKit

#endif // PANELMANAGER_H