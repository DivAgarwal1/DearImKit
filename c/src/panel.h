#include <functional>

#include "DearImKit/base/base.h"

class ExternPanel : public DearImKit::Panel {
public:
    ExternPanel(std::string name, std::function<int(void*)> draw, void* state) : DearImKit::Panel(name), m_draw(draw), mp_state(state) {};

    bool draw() override {
        return m_draw(mp_state) > 0;
    }

private:
    std::function<int(void*)> m_draw;
    void* mp_state;
};

