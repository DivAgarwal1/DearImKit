#ifndef INIT_H
#define INIT_H

#include <functional>
#include <tuple>

namespace DearImKit {
    /**
     * @brief Run this function once at your entry point (usually main()).
     *
     * Sets up environment and runs application loop. Calling this function is sufficient for creating a GUI app.
     *
     * @param at_start
     * A function to execute after setup and before the application loop,
     * use especially to add windows at startup like home windows or menu bars
     * @param during_loop
     * A function to execute during each iteration of the application loop,
     * usually use default
     * @param background_color
     * A tuple of 4 numbers representing background color of window in (r, g, b, a) all as floats from 0 to 1
     * @return int - The exit code,
     * can be used as the return value of entry point
     */
    int SetupApp(std::function<void(void)> at_start, std::function<void(void)> during_loop = []() {}, const std::tuple<float, float, float, float> &background_color = std::make_tuple(0.2f, 0.3f, 0.3f, 1.0f));
    int SetupApp(std::function<void(void)> at_start, const std::tuple<float, float, float, float> &background_color);
} // namespace DearImKit

#endif // INIT_H