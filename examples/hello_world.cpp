#include <functional>

#include "DearImKit/dearimkit.h"

// Extend base class
class HelloWorld : public DearImKit::Panel {
public:
    // Call base class constructor
    HelloWorld(int num_times = 1) : DearImKit::Panel("Hello World"), m_num_times(num_times) {};

    // Override draw function
    bool draw() override {
        bool stay_open = true;

        // Check out https://github.com/ocornut/imgui for guide to ImGui logic
        if (!ImGui::Begin(DearImKit::Panel::getName().c_str(), &stay_open)) {
            ImGui::End();
            return stay_open;
        }

        for (int i = 0; i < m_num_times; i++) {
            ImGui::Text("Hello World from DearImKit");
        }

        ImGui::End();
        return stay_open;
    }

private:
    int m_num_times;
};

int main() {
    // Add windows to be displayed at startup with a std::function that will be passed to DearImKit::SetupApp(...)
    std::function<void(void)> at_start = []() {
        DearImKit::AddPanel<HelloWorld>(2);
    };

    // Can optionally set the parameters for the function to execute once per application loop and background color
    // Usually the once per loop function should be left blank, background color is safe to change
    DearImKit::SetupApp(at_start);
}