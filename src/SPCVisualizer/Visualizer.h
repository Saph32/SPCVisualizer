#pragma once

#include "IGfx.h"

class Visualizer final
{
public:

    Visualizer() {}
    Visualizer(const Visualizer&) = delete;
    Visualizer& operator=(const Visualizer&) = delete;

    void RenderFrame();

private:

};