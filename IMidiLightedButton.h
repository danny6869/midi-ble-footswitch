#include "IMidiControllerComponent.h"

#ifndef DILIGHTEDBUTTON_H
#define DILIGHTEDBUTTON_H

class IMidiLightedButton : public IMidiControllerComponent {
  public:
    virtual void turnLEDOff();
    virtual void turnLEDOn();
};

#endif
