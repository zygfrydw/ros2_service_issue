#ifndef SRV_SERVICE_INCLUDE_SRV_SERVICE_AS_SERVICE_HPP_
#define SRV_SERVICE_INCLUDE_SRV_SERVICE_AS_SERVICE_HPP_

#include <rclcpp/rclcpp.hpp>
#include <service_msg/srv/my_service.hpp>

namespace srv_service
{
/// @brief Short description of responsibilities of this class and its purpose.
class SrvService : public rclcpp::Node
{
public:
  /// @brief Standard constructor required by RCLCPP_COMPONENTS library.
  ///
  /// @param options Structure which allows overriding parameters of the node:
  ///                - param-name - short description
  explicit SrvService(const rclcpp::NodeOptions& options);

private:
  void predict_transform(service_msg::srv::MyService::Request::SharedPtr request,
                         service_msg::srv::MyService::Response::SharedPtr response);

  rclcpp::Service<service_msg::srv::MyService>::SharedPtr service_;
};
}  // namespace srv_service

#endif /* SRV_SERVICE_INCLUDE_SRV_SERVICE_AS_SERVICE_HPP_ */
