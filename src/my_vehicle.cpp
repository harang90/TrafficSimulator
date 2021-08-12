//
// Created by taisun_park@tmax.co.kr on 21. 8. 9..
//

#include "my_vehicle.h"

#include <thread>
#include <chrono>

#include "my_intersection.h"

void MyVehicle::onStreetSet() {
  setDir(onStreet_->getDir());

  const MyIntersection& from = onStreet_->getFrom();
  const MyIntersection& to = onStreet_->getTo();
  int x = (from.getX() + to.getX()) / 2;
  int y = (from.getY() + to.getY()) / 2;

  setPos(x, y);
}

void MyVehicle::drive() {
  for (int i = 0; i < 100; i++) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (getDir() == "left") {
      setX(getX()-10);
    } else if (getDir() == "right") {
      setX(getX()+10);
    }
  }
}

void MyVehicle::simulate() {
  threads_.emplace_back(std::thread(&MyVehicle::drive, this));
}