
#pragma once

#include <Arduboy2.h>
#include "../utils/Enums.h"
#include "../utils/Enums.h"
#include "../../fxdata/fxdata.h"


struct SoundSettings {

    bool led = false;
    RenderSize renderSize = RenderSize::Auto;

    bool getLED()                           { return this->led; }
    RenderSize getRenderSize()              { return this->renderSize; }

    void setLED(bool val)                   { this->led = val; }
    void setRenderSize(RenderSize val)      { this->renderSize = val; }

};
