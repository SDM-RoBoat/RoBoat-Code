#ifndef _ROS_custom_msg_heading_h
#define _ROS_custom_msg_heading_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace custom_msg
{

  class heading : public ros::Msg
  {
    public:
      typedef float _Speed_type;
      _Speed_type Speed;
      typedef float _Theta_type;
      _Theta_type Theta;

    heading():
      Speed(0),
      Theta(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Speed;
      u_Speed.real = this->Speed;
      *(outbuffer + offset + 0) = (u_Speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Speed);
      union {
        float real;
        uint32_t base;
      } u_Theta;
      u_Theta.real = this->Theta;
      *(outbuffer + offset + 0) = (u_Theta.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Theta.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Theta.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Theta.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Theta);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Speed;
      u_Speed.base = 0;
      u_Speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Speed = u_Speed.real;
      offset += sizeof(this->Speed);
      union {
        float real;
        uint32_t base;
      } u_Theta;
      u_Theta.base = 0;
      u_Theta.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Theta.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Theta.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Theta.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Theta = u_Theta.real;
      offset += sizeof(this->Theta);
     return offset;
    }

    virtual const char * getType() override { return "custom_msg/heading"; };
    virtual const char * getMD5() override { return "8f431155f3e96759ba9fd9cd4952bf9b"; };

  };

}
#endif
