#pragma once

#include "imu/IImu.hh"
#include "lidar/ILidar.hh"
#include "sensors.grpc.pb.h"
#include <boost/lockfree/spsc_queue.hpp>

/**
 * @brief Call the methods of this service to publish data via gRPC.
 *
 */
class ScanService : public sensors::SensorService::Service {
public:
  ScanService();

  ::grpc::Status
  getScan(::grpc::ServerContext *context,
          const ::google::protobuf::Empty *request,
          ::grpc::ServerWriter<sensors::PointCloud3> *writer) override;

  ::grpc::Status
  getImu(::grpc::ServerContext *context,
         const ::google::protobuf::Empty *request,
         ::grpc::ServerWriter<sensors::IMUData> *writer) override;

  /**
   * @brief Puts a scan in the server queue.
   *
   * @param scan
   */
  void putScan(const msensor::Scan3DI &scan);
  /**
   * @brief Puts IMU into the server queue.
   *
   * @param imu_data
   */
  void putImuData(const msensor::IMUData &imu_data);

private:
  boost::lockfree::spsc_queue<msensor::Scan3DI> scan_queue_;
  boost::lockfree::spsc_queue<msensor::IMUData> imu_queue_;
};