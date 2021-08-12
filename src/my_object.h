//
// Created by taisun_park@tmax.co.kr on 21. 8. 4..
//

#ifndef MY_PLACE_MAP_MY_OBJECT_H
#define MY_PLACE_MAP_MY_OBJECT_H

#include <mutex>
#include <vector>
#include <thread>

class MyObject {
 public:
  MyObject(int x, int y) : posX_(x), posY_(y) {

  }
  MyObject() : posX_(0), posY_(0) {}
  virtual void simulate() = 0;
  void setPos(int x, int y) {
    setX(x);
    setY(y);
  };
  void setX(int x) {
    posX_ = x;
  }
  void setY(int y) {
    posY_ = y;
  }
  int getX() const {
    return posX_;
  }
  int getY() const {
    return posY_;
  }
 protected:
  int posX_;
  int posY_;

  std::vector<std::thread> threads_;

 private:
  std::mutex mtx_;
};

#endif //MY_PLACE_MAP_MY_OBJECT_H
