#include <functional>

#include "DearImKit/base/base.h"

class ExternPanel : public DearImKit::Panel {
public:
    ExternPanel(std::string name, std::function<bool(void*, void*)> draw, void* state) : DearImKit::Panel(name), m_draw(draw), mp_state(state) {};

    bool draw() override {
        return m_draw(this, mp_state);
    }

private:
    std::function<bool(void*, void*)> m_draw;
    void* mp_state;
};

