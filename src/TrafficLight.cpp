#include <iostream>
#include <random>
#include "TrafficLight.h"
#include <chrono>
#include <cstdlib>
#include <ctime>

template<typename T>
void MessageQueue<T>::send(T&& message) {
  std::lock_guard<std::mutex> lk(mtx_);
  queue_.emplace(std::move(message));
  cv_.notify_one();
}

template<typename T>
T MessageQueue<T>::receive() {
  std::unique_lock<std::mutex> lk(mtx_);
  cv_.wait(lk, [this] () -> bool { return !queue_.empty(); });
  T message = std::move(queue_.front());
  queue_.pop();
  return message;
}

TrafficLight::TrafficLight() {
  currentPhase_ = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen() {
  while (1) {
    TrafficLightPhase phase = std::move(messageQueue_.receive());
    if (phase == TrafficLightPhase::green) {
      return;
    }
  }
}

void TrafficLight::simulate() {
  threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

TrafficLight::TrafficLightPhase TrafficLight::getCurrentPhase() const {
  return currentPhase_;
}

void TrafficLight::cycleThroughPhases() {
  while (true) {
    for (int i = 0; i < 2; i++) {
    	bool isGreen = getCurrentPhase() == TrafficLightPhase::green;
    	TrafficLightPhase nowSending;
    	if (isGreen) {
      		nowSending = TrafficLightPhase::red;
    	} else {
     	 	nowSending = TrafficLightPhase::green;
    	}
    	currentPhase_ = nowSending;
    	messageQueue_.send(std::move(nowSending));
	    
      	std::srand(std::time(0));
    	std::chrono::seconds seconds_((std::rand() % 3) + 4);
    	std::this_thread::sleep_for(seconds_);
    }
   	std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}