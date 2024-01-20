#ifndef _ROS_custom_msg_radio_h
#define _ROS_custom_msg_radio_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace custom_msg
{

  class radio : public ros::Msg
  {
    public:
      typedef bool _RadioConection_type;
      _RadioConection_type RadioConection;
      typedef int16_t _Throttle_type;
      _Throttle_type Throttle;
      typedef int16_t _Aileron_type;
      _Aileron_type Aileron;
      typedef bool _Gear_type;
      _Gear_type Gear;
      typedef bool _ElevdD_R_type;
      _ElevdD_R_type ElevdD_R;
      typedef bool _Flap_type;
      _Flap_type Flap;

    radio():
      RadioConection(0),
      Throttle(0),
      Aileron(0),
      Gear(0),
      ElevdD_R(0),
      Flap(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_RadioConection;
      u_RadioConection.real = this->RadioConection;
      *(outbuffer + offset + 0) = (u_RadioConection.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->RadioConection);
      union {
        int16_t real;
        uint16_t base;
      } u_Throttle;
      u_Throttle.real = this->Throttle;
      *(outbuffer + offset + 0) = (u_Throttle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Throttle.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->Throttle);
      union {
        int16_t real;
        uint16_t base;
      } u_Aileron;
      u_Aileron.real = this->Aileron;
      *(outbuffer + offset + 0) = (u_Aileron.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Aileron.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->Aileron);
      union {
        bool real;
        uint8_t base;
      } u_Gear;
      u_Gear.real = this->Gear;
      *(outbuffer + offset + 0) = (u_Gear.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Gear);
      union {
        bool real;
        uint8_t base;
      } u_ElevdD_R;
      u_ElevdD_R.real = this->ElevdD_R;
      *(outbuffer + offset + 0) = (u_ElevdD_R.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ElevdD_R);
      union {
        bool real;
        uint8_t base;
      } u_Flap;
      u_Flap.real = this->Flap;
      *(outbuffer + offset + 0) = (u_Flap.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->Flap);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_RadioConection;
      u_RadioConection.base = 0;
      u_RadioConection.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->RadioConection = u_RadioConection.real;
      offset += sizeof(this->RadioConection);
      union {
        int16_t real;
        uint16_t base;
      } u_Throttle;
      u_Throttle.base = 0;
      u_Throttle.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Throttle.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->Throttle = u_Throttle.real;
      offset += sizeof(this->Throttle);
      union {
        int16_t real;
        uint16_t base;
      } u_Aileron;
      u_Aileron.base = 0;
      u_Aileron.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Aileron.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->Aileron = u_Aileron.real;
      offset += sizeof(this->Aileron);
      union {
        bool real;
        uint8_t base;
      } u_Gear;
      u_Gear.base = 0;
      u_Gear.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->Gear = u_Gear.real;
      offset += sizeof(this->Gear);
      union {
        bool real;
        uint8_t base;
      } u_ElevdD_R;
      u_ElevdD_R.base = 0;
      u_ElevdD_R.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ElevdD_R = u_ElevdD_R.real;
      offset += sizeof(this->ElevdD_R);
      union {
        bool real;
        uint8_t base;
      } u_Flap;
      u_Flap.base = 0;
      u_Flap.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->Flap = u_Flap.real;
      offset += sizeof(this->Flap);
     return offset;
    }

    virtual const char * getType() override { return "custom_msg/radio"; };
    virtual const char * getMD5() override { return "c9090c1569f859ff634a5e4d5b725df5"; };

  };

}
#endif
