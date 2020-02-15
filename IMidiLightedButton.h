#include "IMidiControllerComponent.h"

#ifndef DILIGHTEDBUTTON_H
#define DILIGHTEDBUTTON_H

// XXX - Turn this into a real class to take most of the functionality away from the others?!  Or just leave as is!?  Too many layers creeping in!?

class IMidiLightedButton : public IMidiControllerComponent {
  public:
    virtual void turnLEDOff();
    virtual void turnLEDOn();
};

#endif
