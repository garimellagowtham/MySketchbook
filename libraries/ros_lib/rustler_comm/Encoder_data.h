#ifndef ros_rustler_comm_Encoder_data_h
#define ros_rustler_comm_Encoder_data_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros/msg.h"

namespace rustler_comm
{

  class Encoder_data : public ros::Msg
  {
    public:
      float angle;
      float angvel;
      float time;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      union {
        float real;
        unsigned long base;
      } u_angle;
      u_angle.real = this->angle;
      *(outbuffer + offset + 0) = (u_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angle);
      union {
        float real;
        unsigned long base;
      } u_angvel;
      u_angvel.real = this->angvel;
      *(outbuffer + offset + 0) = (u_angvel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angvel.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_angvel.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_angvel.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->angvel);
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
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        unsigned long base;
      } u_angle;
      u_angle.base = 0;
      u_angle.base |= ((typeof(u_angle.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle.base |= ((typeof(u_angle.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angle.base |= ((typeof(u_angle.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angle.base |= ((typeof(u_angle.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angle = u_angle.real;
      offset += sizeof(this->angle);
      union {
        float real;
        unsigned long base;
      } u_angvel;
      u_angvel.base = 0;
      u_angvel.base |= ((typeof(u_angvel.base)) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angvel.base |= ((typeof(u_angvel.base)) (*(inbuffer + offset + 1))) << (8 * 1);
      u_angvel.base |= ((typeof(u_angvel.base)) (*(inbuffer + offset + 2))) << (8 * 2);
      u_angvel.base |= ((typeof(u_angvel.base)) (*(inbuffer + offset + 3))) << (8 * 3);
      this->angvel = u_angvel.real;
      offset += sizeof(this->angvel);
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
     return offset;
    }

    const char * getType(){ return "rustler_comm/Encoder_data"; };

  };

}
#endif