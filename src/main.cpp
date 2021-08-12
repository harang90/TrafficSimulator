//
// Created by taisun_park@tmax.co.kr on 21. 7. 30..
//

#include <iostream>
#include <vector>

#include "my_intersection.h"
#include "my_street.h"
#include "my_vehicle.h"
#include "my_window_manager.h"

int main() {

  //1차 개발: clone coding
  //2차 개발: improvement

  // create and connect intersections and streets

  std::vector<std::tuple<std::string, int, int>> intersectionRecords;

  // 오리교1
  intersectionRecords.emplace_back("오리교1", 65, 423);

  // 오리교2
  intersectionRecords.emplace_back("오리교2", 309, 421);

  // 무지개
  intersectionRecords.emplace_back("무지개", 879, 421);

  std::unordered_map<std::string, std::shared_ptr<MyIntersection>> intersections;
  for (auto &intersectionRecord : intersectionRecords)
    intersections.emplace(
            std::make_pair(std::get<0>(intersectionRecord),
                           std::make_shared<MyIntersection>(std::get<1>(intersectionRecord), std::get<2>(intersectionRecord))));

  std::vector<std::pair<std::string, std::string>> fromToBoth;
  fromToBoth.emplace_back("오리교1", "오리교2");
  fromToBoth.emplace_back("오리교2", "무지개");

  std::vector<std::shared_ptr<MyStreet>> streets;
  std::for_each(fromToBoth.begin(), fromToBoth.end(), [&streets, &intersections](auto& record){
    std::shared_ptr<MyStreet> street1 = std::make_shared<MyStreet>();
    street1->setFrom(intersections.at(record.first));
    street1->setTo(intersections.at(record.second));
    street1->setDir("right");
    streets.emplace_back(street1);

    std::shared_ptr<MyStreet> street2 = std::make_shared<MyStreet>();
    street2->setFrom(intersections.at(record.second));
    street2->setTo(intersections.at(record.first));
    street2->setDir("left");
    streets.emplace_back(street2);
  });

  // vehicles

  std::vector<std::shared_ptr<MyVehicle>> vehicles;
  int nVehicles = 1;
  for (int i = 0; i < nVehicles; i++) {
    vehicles.emplace_back(std::make_shared<MyVehicle>());
  }

  for (int i = 0; i < nVehicles; i++) {
    vehicles.at(i)->setOnStreet(streets.at(i));
  }

  for (auto& vehicle : vehicles) {
    vehicle->simulate();
  }

  // visualize
  MyWindowManager windowManager;
  windowManager.setIntersects(&intersections);
  windowManager.setStreets(&streets);
  windowManager.setVehicles(&vehicles);
  windowManager.run();

  return EXIT_SUCCESS;
}