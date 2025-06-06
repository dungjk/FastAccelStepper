#include "FastAccelStepper.h"

// As in StepperDemo for Motor 1 on AVR
// #define dirPinStepper    5
// #define enablePinStepper 6
// #define stepPinStepper   9  // OC1A in case of AVR

// As in StepperDemo for Motor 1 on ESP32
#define dirPinStepper 18
#define enablePinStepper 26
#define stepPinStepper 17

#if defined(PICO_RP2040) || defined(PICO_RP2350)
#undef dirPinStepper
#undef enablePinStepper
#undef stepPinStepper
#define dirPinStepper 16
#define enablePinStepper 7
#define stepPinStepper 17
#endif

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

void setup() {
  engine.init();
  stepper = engine.stepperConnectToPin(stepPinStepper);
  if (stepper) {
    stepper->setDirectionPin(dirPinStepper);
    // stepper->setEnablePin(enablePinStepper);
    stepper->setAutoEnable(true);

    // If auto enable/disable need delays, just add (one or both):
    // stepper->setDelayToEnable(50);
    // stepper->setDelayToDisable(1000);

    stepper->setSpeedInUs(1000);  // the parameter is us/step !!!
    stepper->setAcceleration(100);
    stepper->move(1000);
  }
}

void loop() {
    stepper->move(1000);
    delay(1000);
}
