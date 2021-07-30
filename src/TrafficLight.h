#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <queue>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

// FP.3 Define a class „MessageQueue“ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// Also, there should be an std::condition_variable as well as an std::mutex as private members. 

template<typename T>
class MessageQueue {
  public:
  	void send(T&& message);
  	T receive();
  private:
  	std::queue<T> queue_;
  	std::condition_variable cv_;
  	std::mutex mtx_;
};

// FP.1 : Define a class „TrafficLight“ which is a child class of TrafficObject. 
// The class shall have the public methods „void waitForGreen()“ and „void simulate()“ 
// as well as „TrafficLightPhase getCurrentPhase()“, where TrafficLightPhase is an enum that 
// can be either „red“ or „green“. Also, add the private method „void cycleThroughPhases()“. 
// Furthermore, there shall be the private member _currentPhase which can take „red“ or „green“ as its value. 

class TrafficLight : public TrafficObject {
  public:
  	enum TrafficLightPhase {
      red,
      green
    };
  	TrafficLight();
  	void waitForGreen();
  	void simulate();
  	TrafficLightPhase getCurrentPhase() const;
  private:
  	void cycleThroughPhases();
  	TrafficLightPhase currentPhase_;
  	MessageQueue<TrafficLightPhase> messageQueue_;
};

#endif