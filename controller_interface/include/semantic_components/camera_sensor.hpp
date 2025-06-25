// Copyright 2021 PAL Robotics SL.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SEMANTIC_COMPONENTS__CAMERA_SENSOR_HPP_
#define SEMANTIC_COMPONENTS__CAMERA_SENSOR_HPP_

#include <algorithm>
#include <limits>
#include <string>
#include <vector>

#include "semantic_components/semantic_component_interface.hpp"
#include "sensor_msgs/msg/image.hpp"

namespace semantic_components
{
class CameraSensor : public SemanticComponentInterface<sensor_msgs::msg::Image>
{
public:
  explicit CameraSensor(const std::string & name)
  : SemanticComponentInterface(
      name, {{name + "/" + "data"}})
  {
  }

  /// Return image data.
  /**
   * Return image data reported by a Camera
   *
   * \return vector of bytes with image data.
   */
  std::vector<unsigned char, std::allocator<unsigned char>> get_data() const{
    const auto data = state_interfaces_[0].get().get_optional<std::vector<unsigned char>>();
    if (data.has_value())
    {
      return data.value();
    }
    return std::vector<unsigned char>{};
  }

  /// Return Camera message with image data
  /**
   * Constructs and return a Camera message from the current values.
   * \return Camera message from values;
   */
  bool get_values_as_message(sensor_msgs::msg::Image & message) const
  {
    message.data.clear();
    message.data = get_data();

    return true;
  }
};

}  // namespace semantic_components

#endif  // SEMANTIC_COMPONENTS__CAMERA_SENSOR_HPP_