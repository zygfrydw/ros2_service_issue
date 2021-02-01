#include "srv_service/srv_service.hpp"

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <functional>
#include <sstream>

namespace srv_service
{
SrvService::SrvService(const rclcpp::NodeOptions& options) : rclcpp::Node::Node("Service", options)
{
  service_ = create_service<service_msg::srv::MyService>(
      "/my_service", std::bind(&SrvService::predict_transform, this, std::placeholders::_1, std::placeholders::_2));
}

void SrvService::predict_transform(service_msg::srv::MyService::Request::SharedPtr request,
                                   service_msg::srv::MyService::Response::SharedPtr response)
{
  RCLCPP_INFO(get_logger(), "Incoming request");
  std::stringstream stream;
  stream << request->question << " - " << "serice response";
  response->answare = stream.str();
}

}  // namespace srv_service

RCLCPP_COMPONENTS_REGISTER_NODE(srv_service::SrvService)