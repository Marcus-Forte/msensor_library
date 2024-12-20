#pragma once

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <stdint.h>

struct Scan3D {
  pcl::PointCloud<pcl::PointXYZI> points;
  uint64_t timestamp;
};

class ILidar {
public:
  virtual ~ILidar() = default;

  virtual void init() = 0;
  virtual void startSampling() = 0;
  virtual void stopSampling() = 0;

  /** Return lidar scan. Associated timestamp is assumed to be the time
   * point[0] was measured. Unit: ns (1/1000000000 sec) */
  virtual Scan3D getScan() = 0;
};