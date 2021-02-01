#ifndef SRV_CLIENT_INCLUDE_SRV_CLIENT_SRV_CLIENT_HPP_
#define SRV_CLIENT_INCLUDE_SRV_CLIENT_SRV_CLIENT_HPP_

#include <rclcpp/rclcpp.hpp>
#include <service_msg/srv/my_service.hpp>

namespace srv_client
{
class SrvClient : public rclcpp::Node
{
public:
  explicit SrvClient(const rclcpp::NodeOptions& options);

private:
  void timer_callback();
  rclcpp::Node::SharedPtr service_node_;
  rclcpp::Client<service_msg::srv::MyService>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;
};
}  // namespace srv_client

#endif /* SRV_CLIENT_INCLUDE_SRV_CLIENT_SRV_CLIENT_HPP_ */
