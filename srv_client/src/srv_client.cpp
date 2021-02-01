// Copyright (c) 2020 Autonomous Systems Sp. z o.o.
// All rights reserved. Proprietary and confidential.

#include "srv_client/srv_client.hpp"

#include <rclcpp/rclcpp.hpp>
#include <rclcpp_components/register_node_macro.hpp>
#include <chrono>
#include <functional>

namespace srv_client
{

rclcpp::NodeOptions create_options()
{
  rclcpp::NodeOptions options;
  options.arguments({ "--ros-args", "-r", "__node:=service_node" });
  options.start_parameter_event_publisher(false);
  options.start_parameter_services(false);
  return options;
}

SrvClient::SrvClient(const rclcpp::NodeOptions& options) : rclcpp::Node::Node("my_client", options)
{
  service_node_ = std::make_shared<rclcpp::Node>("service_node", create_options());
  client_ = service_node_->create_client<service_msg::srv::MyService>("/my_service");

  timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&SrvClient::timer_callback, this));
}

void SrvClient::timer_callback()
{
  if (client_->wait_for_service(std::chrono::milliseconds(100)))
  {
    RCLCPP_INFO(get_logger(), "Service avaliable - making a call");
    auto request = std::make_shared<service_msg::srv::MyService::Request>();
    request->question = "hello";

    auto result = client_->async_send_request(request);
    auto spin_result = rclcpp::spin_until_future_complete(service_node_->get_node_base_interface(), result);
    if (spin_result == rclcpp::FutureReturnCode::SUCCESS)
    {
      RCLCPP_INFO(get_logger(), "Received result: %s", result.get()->answare.c_str());
    }
    else
    {
      RCLCPP_ERROR(get_logger(), "The service call failed");
    }
  }
  else
  {
    RCLCPP_ERROR(get_logger(), "Service is not ready.");
  }
}

}  // namespace srv_client

RCLCPP_COMPONENTS_REGISTER_NODE(srv_client::SrvClient)