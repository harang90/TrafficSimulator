//
// Created by taisun_park@tmax.co.kr on 21. 8. 2..
//

#ifndef MY_PLACE_MAP_MY_INTERSECTION_H
#define MY_PLACE_MAP_MY_INTERSECTION_H

#include <memory>

#include "my_object.h"

class MyIntersection : public MyObject, public std::enable_shared_from_this<MyIntersection> {
 public:
  MyIntersection(int x, int y) : MyObject(x, y) {

  }
  void simulate() override {

  }
 private:
};

#endif //MY_PLACE_MAP_MY_INTERSECTION_H
