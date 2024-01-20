#ifndef _ROS_custom_msg_motor_speed_h
#define _ROS_custom_msg_motor_speed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace custom_msg
{

  class motor_speed : public ros::Msg
  {
    public:
      typedef int16_t _leftMotor_type;
      _leftMotor_type leftMotor;
      typedef int16_t _rightMotor_type;
      _rightMotor_type rightMotor;

    motor_speed():
      leftMotor(0),
      rightMotor(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_leftMotor;
      u_leftMotor.real = this->leftMotor;
      *(outbuffer + offset + 0) = (u_leftMotor.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_leftMotor.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->leftMotor);
      union {
        int16_t real;
        uint16_t base;
      } u_rightMotor;
      u_rightMotor.real = this->rightMotor;
      *(outbuffer + offset + 0) = (u_rightMotor.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_rightMotor.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->rightMotor);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_leftMotor;
      u_leftMotor.base = 0;
      u_leftMotor.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_leftMotor.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->leftMotor = u_leftMotor.real;
      offset += sizeof(this->leftMotor);
      union {
        int16_t real;
        uint16_t base;
      } u_rightMotor;
      u_rightMotor.base = 0;
      u_rightMotor.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_rightMotor.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->rightMotor = u_rightMotor.real;
      offset += sizeof(this->rightMotor);
     return offset;
    }

    virtual const char * getType() override { return "custom_msg/motor_speed"; };
    virtual const char * getMD5() override { return "12f7007aed09f42ba3aeb9e9a9e1b026"; };

  };

}
#endif
