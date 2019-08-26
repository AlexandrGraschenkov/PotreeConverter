//
// Created by Alexander Graschenkov on 19.10.2018.
//

#ifndef POTREE_JSONPOINTREADER_HPP
#define POTREE_JSONPOINTREADER_HPP

#include <string>
#include <iostream>
#include <vector>

#include "Point.h"
#include "PointReader.h"
#include "PointAttributes.hpp"
#include "json.hpp"

using std::string;

using std::ifstream;
using std::cout;
using std::endl;
using std::vector;

namespace Potree{

class JSONPointReader : public PointReader {
 private:
  AABB aabb;
  double scale;
  string path;
  vector<string> files;
  vector<string>::iterator currentFile;
  int pointIdx;
  std::vector<Point> allPoints;

  void readAllFiles();
  void readFrame(nlohmann::json frameJs);

 public:

  JSONPointReader(string path);

  ~JSONPointReader();

  bool readNextPoint();

  Point getPoint();

  AABB getAABB();

  long long numPoints();

  void close();
};

};

#endif //POTREE_JSONPOINTREADER_HPP
