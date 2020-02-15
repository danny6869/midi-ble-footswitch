

#ifndef DICONTROLLERCOMPONENT_H
#define DICONTROLLERCOMPONENT_H

class IMidiControllerComponent {
  public:
    virtual void initGPIOPins();
    virtual void resetState();
    virtual void handleState();
};

#endif
