//
// Created by taisun_park@tmax.co.kr on 21. 8. 10..
//

#ifndef MY_PLACE_MAP_MY_WINDOW_MANAGER_H
#define MY_PLACE_MAP_MY_WINDOW_MANAGER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "my_intersection.h"
#include "my_street.h"
#include "my_vehicle.h"

class MyWindowManager {
 public:
  MyWindowManager();
  void setIntersects(std::unordered_map<std::string, std::shared_ptr<MyIntersection>>* intersects) { intersects_ = intersects; }
  void setStreets(std::vector<std::shared_ptr<MyStreet>>* streets) { streets_ = streets; }
  void setVehicles(std::vector<std::shared_ptr<MyVehicle>>* vehicles) { vehicles_ = vehicles; }

  [[noreturn]] void run();
 private:
  cv::Mat overlay_{};

  void draw();
  void show();

  std::string windowName_;
  std::unordered_map<std::string, std::shared_ptr<MyIntersection>>* intersects_{};
  std::vector<std::shared_ptr<MyStreet>>* streets_{};
  std::vector<std::shared_ptr<MyVehicle>>* vehicles_{};
};

#endif //MY_PLACE_MAP_MY_WINDOW_MANAGER_H
