#ifndef StatefulController_h
#define StatefulController_h

#include <Arduino.h>
#include "eventdrivenstates/EventBus.h"

class State{
    public:
        virtual State* transition(Event *event);
        virtual ~State(){}
};

class StatefulController : public EventListener {
  private:
    State *currentState = NULL;
  public:
    StatefulController(State *initialState);
    void receiveEvent(Event *event);
};

StatefulController::StatefulController(State *initialState){
  this->currentState = initialState;
}

void StatefulController::receiveEvent(Event *event){
        State *oldState = this->currentState;
        this->currentState = this->currentState->transition(event);
        if (oldState != this->currentState){
            delete(oldState);
        }
        Serial.printf("StatefulController: event received: %s (proc: %d)\n", event->getEventKey(), xPortGetCoreID());

    }

#endif