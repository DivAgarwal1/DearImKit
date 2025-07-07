// See hello_world.cpp first

#include <functional>

#include "DearImKit/dearimkit.h"

class HelloWorld : public DearImKit::Panel {
public:
    HelloWorld(int num_times = 1) : DearImKit::Panel("Hello World"), m_num_times(num_times) {};

    bool draw() override {
        bool stay_open = true;

        // Check out https://github.com/ocornut/imgui for guide to ImGui logic
        if (!DearImKit::Begin(*this, &stay_open)) {
            ImGui::End();
            return stay_open;
        }

        for (int i = 0; i < m_num_times; i++) {
            ImGui::Text("Hello World from DearImKit");
        }

        if (ImGui::Button("Click to activate an error")) {
            // Create error with title "Oh No!" and body "You triggered an error."
            DearImKit::QueueError(*this, "Oh No!", "You triggered an error.");
        }

        ImGui::End();
        return stay_open;
    }

private:
    int m_num_times;
};

int main() {
    std::function<void(void)> at_start = []() {
        DearImKit::AddPanel<HelloWorld>(2);
    };

    DearImKit::SetupApp(at_start);
}
