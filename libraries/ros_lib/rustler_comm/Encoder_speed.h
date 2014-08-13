#ifndef ros_rustler_comm_Encoder_speed_h
#define ros_rustler_comm_Encoder_speed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros/msg.h"

namespace rustler_comm
{

  class Encoder_speed : public ros::Msg
  {
    public:
      float time;
      float XSpeed;
      float YSpeed;
      float THSpeed;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      union {
        float real;
        unsigned long base;
      } u_time;
      u_time.real = this->time;
      *(outbuffer + offset + 0) = (u_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time);
      union {
        float real;
        unsigned long base;
      } u_XSpeed;
      u_XSpeed.real = this->XSpeed;
      *(outbuffer + offset + 0) = (u_XSpeed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_XSpeed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_XSpeed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_XSpeed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->XSpeed);
      union {
        float real;
        unsigned long base;
      } u_YSpeed;
      u_YSpeed.real = this->YSpeed;
      *(outbuffer + offset + 0) = (u_YSpeed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_YSpeed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_YSpeed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_YSpeed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->YSpeed);
      union {
        float real;
        unsigned long base;
      } u_THSpeed;
      u_THSpeed.real = this->THSpeed;
      *(outbuffer + offset + 0) = (u_THSpeed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_THSpeed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_THSpeed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_THSpeed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->THSpeed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        unsigned long base;
      } u_time;
      u_time.base = 0;
      u_time.base |= ((typeof(u_time.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time.base |= ((typeof(u_time.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time.base |= ((typeof(u_time.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time.base |= ((typeof(u_time.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->time = u_time.real;
      offset += sizeof(this->time);
      union {
        float real;
        unsigned long base;
      } u_XSpeed;
      u_XSpeed.base = 0;
      u_XSpeed.base |= ((typeof(u_XSpeed.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_XSpeed.base |= ((typeof(u_XSpeed.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_XSpeed.base |= ((typeof(u_XSpeed.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_XSpeed.base |= ((typeof(u_XSpeed.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->XSpeed = u_XSpeed.real;
      offset += sizeof(this->XSpeed);
      union {
        float real;
        unsigned long base;
      } u_YSpeed;
      u_YSpeed.base = 0;
      u_YSpeed.base |= ((typeof(u_YSpeed.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_YSpeed.base |= ((typeof(u_YSpeed.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_YSpeed.base |= ((typeof(u_YSpeed.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_YSpeed.base |= ((typeof(u_YSpeed.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->YSpeed = u_YSpeed.real;
      offset += sizeof(this->YSpeed);
      union {
        float real;
        unsigned long base;
      } u_THSpeed;
      u_THSpeed.base = 0;
      u_THSpeed.base |= ((typeof(u_THSpeed.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_THSpeed.base |= ((typeof(u_THSpeed.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_THSpeed.base |= ((typeof(u_THSpeed.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_THSpeed.base |= ((typeof(u_THSpeed.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->THSpeed = u_THSpeed.real;
      offset += sizeof(this->THSpeed);
     return offset;
    }

    const char * getType(){ return "rustler_comm/Encoder_speed"; };

  };

}
#endif