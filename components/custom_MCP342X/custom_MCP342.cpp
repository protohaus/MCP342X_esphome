#include "custom_MCP342.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <string.h>
#include  <Wire.h>

namespace esphome {
namespace mcp {

static const char *const TAG = "mcp.sensor";


void CustomMCP342XSensor::dump_config() {
  LOG_SENSOR("", "MCP", this);
  LOG_UPDATE_INTERVAL(this);
}

void CustomMCP342XSensor::setup()
{
	Wire.begin();  // join I2C bus
    //TWBR = 12;  // 400 kHz (maximum)
    
	ESP_LOGD(TAG, "Starting up");
	ESP_LOGD(TAG, m_mcp342x.testConnection() ? "MCP342X connection successful" : "MCP342X connection failed");

      
    m_mcp342x.configure( MCP342X_MODE_CONTINUOUS |
                          MCP342X_CHANNEL_1 |
                          MCP342X_SIZE_16BIT |
                          MCP342X_GAIN_1X
                        );
						
    //ESP_LOGD(TAG, m_mcp342x.getConfigRegShdw(), HEX);
	
}

void CustomMCP342XSensor::update() {
  this->publish_state(m_result);
}



void CustomMCP342XSensor::loop() {
  static int16_t  result;
  
  m_mcp342x.startConversion();
  m_mcp342x.getResult(&result);
  m_result = result;
  
}

}  // namespace mcp
}  // namespace esphome
