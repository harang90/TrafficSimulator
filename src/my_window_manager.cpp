//
// Created by taisun_park@tmax.co.kr on 21. 8. 10..
//

#include "my_window_manager.h"

#include <thread>

#include "my_intersection.h"

MyWindowManager::MyWindowManager() {
  windowName_ = "this is window";
  std::string fileName = "../data/ori.png";

  cv::namedWindow(windowName_);
  cv::Mat background = cv::imread(fileName);
  overlay_ = background.clone();

}

void MyWindowManager::draw() {
  // draw intersection

  // TODO check for pointer availability

  cv::Scalar green = cv::Scalar(0, 255, 0);
  cv::Scalar red = cv::Scalar(0, 0, 255);
  cv::Scalar blue = cv::Scalar(255, 0, 0);
  cv::Scalar yellow = cv::Scalar(0, 255, 205);

  for (auto& intersection : *intersects_) {
    cv::circle(overlay_, cv::Point2d(intersection.second->getX(), intersection.second->getY()), 25, green, -1);
  }

  // draw streets
  for (auto& street : *streets_) {
    const MyIntersection& fromInter = street->getFrom();
    const MyIntersection& toInter = street->getTo();
    if (street->getDir() == "left") {
      cv::line(overlay_, cv::Point2d(fromInter.getX(), fromInter.getY() - 10), cv::Point2d(toInter.getX(), toInter.getY() - 10), blue, 2, cv::LINE_8, 0);
    } else if (street->getDir() == "right") {
      cv::line(overlay_, cv::Point2d(fromInter.getX(), fromInter.getY() + 10), cv::Point2d(toInter.getX(), toInter.getY() + 10), blue, 2, cv::LINE_8, 0);
    }
  }

  // draw cars
  for (auto& vehicle : *vehicles_) {
    int x = vehicle->getX();
    int y = vehicle->getY();
    if (vehicle->getDir() == "left") {
      cv::arrowedLine(overlay_, cv::Point2d(x, y - 10), cv::Point2d(x, y - 10), yellow, 2, cv::LINE_8, 0, 0.1);
    } else if (vehicle->getDir() == "right") {
      cv::arrowedLine(overlay_, cv::Point2d(x - 5, y + 10), cv::Point2d(x + 5, y + 10), yellow, 2, cv::LINE_8, 0, 0.1);
    }
  }
}

void MyWindowManager::show() {
  cv::imshow(windowName_, overlay_);
  int k = cv::waitKey(33);
}

[[noreturn]] void MyWindowManager::run() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    draw();
    show();
  }
}