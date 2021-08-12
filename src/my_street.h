//
// Created by taisun_park@tmax.co.kr on 21. 8. 4..
//

#ifndef MY_PLACE_MAP_MY_STREET_H
#define MY_PLACE_MAP_MY_STREET_H

#include "my_intersection.h"

#include <memory>
#include <string>
#include <utility>

class MyStreet : public MyObject, public std::enable_shared_from_this<MyStreet> {
 public:
  void setFrom(std::shared_ptr<MyIntersection> from) {
    from_ = std::move(from);
  }
  void setTo(std::shared_ptr<MyIntersection> to) {
    to_ = std::move(to);
  }
  void onDirSet();
  void setDir(std::string dir) {
    dir_ = std::move(dir);
    onDirSet();
  }
  const MyIntersection& getFrom() const { return *from_; }
  const MyIntersection& getTo() const { return *to_; }
  std::string getDir() const { return dir_; }
  const std::pair<int, int>& getFromPos() const { return fromPos_; }
  const std::pair<int, int>& getToPos() const { return toPos_; }

  void simulate() override {

  }
 private:
  std::shared_ptr<MyIntersection> from_;
  std::shared_ptr<MyIntersection> to_;
  std::string dir_;
  std::pair<int, int> fromPos_{};
  std::pair<int, int> toPos_{};

  void setFromPos() {

  }
  void setToPos() {

  }
};

#endif //MY_PLACE_MAP_MY_STREET_H