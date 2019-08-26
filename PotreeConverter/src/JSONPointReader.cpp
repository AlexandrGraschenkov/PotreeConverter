//
// Created by Alexander Graschenkov on 19.10.2018.
//

#include "JSONPointReader.hpp"


#include <fstream>
#include <iostream>
#include <vector>

#include <experimental/filesystem>
#include "stuff.h"

namespace fs = std::experimental::filesystem;

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using std::ios;

namespace Potree{

JSONPointReader::JSONPointReader(string path){
  this->path = path;
  this->aabb = aabb;
  this->scale = scale;

  if(fs::is_directory(path)){
    // if directory is specified, find all las and laz files inside directory

    for(fs::directory_iterator it(path); it != fs::directory_iterator(); it++){
      fs::path filepath = it->path();
      if(fs::is_regular_file(filepath)){
        files.push_back(filepath.string());
      }
    }
  }else{
    files.push_back(path);
  }

//  reader = nullptr;
  readAllFiles();
  pointIdx = -1;
  cout << "Points count " << allPoints.size() << endl;
}

void JSONPointReader::readFrame(nlohmann::json frameJs) {
  nlohmann::json cloud = frameJs["cloud"];
  if (cloud.size() == 0) return;

  Vector3<double> camPos(frameJs["camera"][3].get<double>(),
                         frameJs["camera"][7].get<double>(),
                         frameJs["camera"][11].get<double>());

  for (int pointIdx = 2; pointIdx < cloud.size(); pointIdx += 3) {
    Point p;
    p.position = Vector3<double>(cloud[pointIdx - 2].get<double>(),
                                 cloud[pointIdx - 1].get<double>(),
                                 cloud[pointIdx - 0].get<double>());
    double dist = (camPos - p.position).length();
    if (dist > 3.858) {
      continue;
    }
//    cout << cloud.size() << " - " << frameJs["colors"].size() << endl;

    if (pointIdx < frameJs["colors"].size()) {
      nlohmann::json colors = frameJs["colors"];
      p.color.x = colors[pointIdx - 2].get<unsigned char>();
      p.color.y = colors[pointIdx - 1].get<unsigned char>();
      p.color.z = colors[pointIdx - 0].get<unsigned char>();
//      point.color = Vector3<unsigned char>{0, 0, 255};
    } else {
      cout << "WTF " << frameJs["colors"].size() << "   " << frameJs["cloud"].size() << endl;
      p.color = Vector3<unsigned char>{255, 255, 255};
    }

    if (allPoints.size() < 10) {
      cout << "Start " << (int) p.color.x << " "
           << (int) p.color.y << " "
           << (int) p.color.z << endl;
    }
    allPoints.push_back(p);

    aabb.update(p.position);
  }
}

void JSONPointReader::readAllFiles() {
  cout << "Started" << endl;
  for (string file : files) {
    ifstream reader(file, ios::in | ios::binary);
    nlohmann::json js;
    reader >> js;
    if (!js.is_array()) {
      js = js["frames"];
    }

    for (int frameIdx = 0; frameIdx < js.size(); frameIdx++) {
      readFrame(js[frameIdx]);
    }
    reader.close();
  }
  cout << "FInished" << endl;
}

JSONPointReader::~JSONPointReader(){
  close();
}

void JSONPointReader::close(){
//  if(reader != NULL){
//    reader->close();
//    delete reader;
//    reader = NULL;
//  }
}

long long JSONPointReader::numPoints(){
  //TODO

  return 0;//allPoints.size();
}

bool JSONPointReader::readNextPoint() {
  pointIdx++;
  return pointIdx < allPoints.size();
}

Point JSONPointReader::getPoint(){
//  Point p(0, 0, 0, 255, 0, 0);
  if (pointIdx < 10) {
    cout << (int) allPoints[pointIdx].color.x << " "
         << (int) allPoints[pointIdx].color.y << " "
         << (int) allPoints[pointIdx].color.z << endl;
  }
  return allPoints[pointIdx];
//  return allPoints[pointIdx];
}

AABB JSONPointReader::getAABB(){
  return aabb;
}

}