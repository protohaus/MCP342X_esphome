#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "MCP342X.h"

namespace esphome {
namespace mcp {


/// This class implements support for the EZO circuits in i2c mode
class CustomMCP342XSensor : public sensor::Sensor, public PollingComponent {
 public:
  
  void loop() override;
  void dump_config() override;
  void update() override;
  float get_setup_priority() const override { return setup_priority::DATA; };
  void setup() override;


 protected:
  MCP342X m_mcp342x;
  int16_t  m_result;
};

}  // namespace mcp
}  // namespace esphome
