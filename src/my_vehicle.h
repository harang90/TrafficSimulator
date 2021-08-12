//
// Created by taisun_park@tmax.co.kr on 21. 8. 9..
//

#ifndef MY_PLACE_MAP_MY_VEHICLE_H
#define MY_PLACE_MAP_MY_VEHICLE_H

#include "my_object.h"
#include "my_street.h"

#include <cstdlib>
#include <ctime>

class MyVehicle : public MyObject {
 public:
  MyVehicle() = default;
  void setOnStreet(std::shared_ptr<MyStreet> onStreet) {
    onStreet_ = std::move(onStreet);
    onStreetSet();
  }
  void onStreetSet();

  void drive();
  void simulate() override;

  void setDir(std::string dir) { dir_ = std::move(dir); }
  std::string getDir() const { return dir_; }
 private:
  std::shared_ptr<MyStreet> onStreet_;
  std::string dir_;
};


#endif //MY_PLACE_MAP_MY_VEHICLE_H
