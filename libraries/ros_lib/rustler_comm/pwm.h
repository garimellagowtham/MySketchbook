#ifndef ros_rustler_comm_pwm_h
#define ros_rustler_comm_pwm_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros/msg.h"

namespace rustler_comm
{

  class pwm : public ros::Msg
  {
    public:
      float pwm_v;
      float pwm_s;
      float v_vel;
      float v_steer;

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      long * val_pwm_v = (long *) &(this->pwm_v);
      long exp_pwm_v = (((*val_pwm_v)>>23)&255);
      if(exp_pwm_v != 0)
        exp_pwm_v += 1023-127;
      long sig_pwm_v = *val_pwm_v;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_pwm_v<<5) & 0xff;
      *(outbuffer + offset++) = (sig_pwm_v>>3) & 0xff;
      *(outbuffer + offset++) = (sig_pwm_v>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_pwm_v<<4) & 0xF0) | ((sig_pwm_v>>19)&0x0F);
      *(outbuffer + offset++) = (exp_pwm_v>>4) & 0x7F;
      if(this->pwm_v < 0) *(outbuffer + offset -1) |= 0x80;
      long * val_pwm_s = (long *) &(this->pwm_s);
      long exp_pwm_s = (((*val_pwm_s)>>23)&255);
      if(exp_pwm_s != 0)
        exp_pwm_s += 1023-127;
      long sig_pwm_s = *val_pwm_s;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_pwm_s<<5) & 0xff;
      *(outbuffer + offset++) = (sig_pwm_s>>3) & 0xff;
      *(outbuffer + offset++) = (sig_pwm_s>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_pwm_s<<4) & 0xF0) | ((sig_pwm_s>>19)&0x0F);
      *(outbuffer + offset++) = (exp_pwm_s>>4) & 0x7F;
      if(this->pwm_s < 0) *(outbuffer + offset -1) |= 0x80;
      long * val_v_vel = (long *) &(this->v_vel);
      long exp_v_vel = (((*val_v_vel)>>23)&255);
      if(exp_v_vel != 0)
        exp_v_vel += 1023-127;
      long sig_v_vel = *val_v_vel;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_v_vel<<5) & 0xff;
      *(outbuffer + offset++) = (sig_v_vel>>3) & 0xff;
      *(outbuffer + offset++) = (sig_v_vel>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_v_vel<<4) & 0xF0) | ((sig_v_vel>>19)&0x0F);
      *(outbuffer + offset++) = (exp_v_vel>>4) & 0x7F;
      if(this->v_vel < 0) *(outbuffer + offset -1) |= 0x80;
      long * val_v_steer = (long *) &(this->v_steer);
      long exp_v_steer = (((*val_v_steer)>>23)&255);
      if(exp_v_steer != 0)
        exp_v_steer += 1023-127;
      long sig_v_steer = *val_v_steer;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_v_steer<<5) & 0xff;
      *(outbuffer + offset++) = (sig_v_steer>>3) & 0xff;
      *(outbuffer + offset++) = (sig_v_steer>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_v_steer<<4) & 0xF0) | ((sig_v_steer>>19)&0x0F);
      *(outbuffer + offset++) = (exp_v_steer>>4) & 0x7F;
      if(this->v_steer < 0) *(outbuffer + offset -1) |= 0x80;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      unsigned long * val_pwm_v = (unsigned long*) &(this->pwm_v);
      offset += 3;
      *val_pwm_v = ((unsigned long)(*(inbuffer + offset++))>>5 & 0x07);
      *val_pwm_v |= ((unsigned long)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_pwm_v |= ((unsigned long)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_pwm_v |= ((unsigned long)(*(inbuffer + offset)) & 0x0f)<<19;
      unsigned long exp_pwm_v = ((unsigned long)(*(inbuffer + offset++))&0xf0)>>4;
      exp_pwm_v |= ((unsigned long)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_pwm_v !=0)
        *val_pwm_v |= ((exp_pwm_v)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->pwm_v = -this->pwm_v;
      unsigned long * val_pwm_s = (unsigned long*) &(this->pwm_s);
      offset += 3;
      *val_pwm_s = ((unsigned long)(*(inbuffer + offset++))>>5 & 0x07);
      *val_pwm_s |= ((unsigned long)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_pwm_s |= ((unsigned long)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_pwm_s |= ((unsigned long)(*(inbuffer + offset)) & 0x0f)<<19;
      unsigned long exp_pwm_s = ((unsigned long)(*(inbuffer + offset++))&0xf0)>>4;
      exp_pwm_s |= ((unsigned long)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_pwm_s !=0)
        *val_pwm_s |= ((exp_pwm_s)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->pwm_s = -this->pwm_s;
      unsigned long * val_v_vel = (unsigned long*) &(this->v_vel);
      offset += 3;
      *val_v_vel = ((unsigned long)(*(inbuffer + offset++))>>5 & 0x07);
      *val_v_vel |= ((unsigned long)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_v_vel |= ((unsigned long)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_v_vel |= ((unsigned long)(*(inbuffer + offset)) & 0x0f)<<19;
      unsigned long exp_v_vel = ((unsigned long)(*(inbuffer + offset++))&0xf0)>>4;
      exp_v_vel |= ((unsigned long)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_v_vel !=0)
        *val_v_vel |= ((exp_v_vel)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->v_vel = -this->v_vel;
      unsigned long * val_v_steer = (unsigned long*) &(this->v_steer);
      offset += 3;
      *val_v_steer = ((unsigned long)(*(inbuffer + offset++))>>5 & 0x07);
      *val_v_steer |= ((unsigned long)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_v_steer |= ((unsigned long)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_v_steer |= ((unsigned long)(*(inbuffer + offset)) & 0x0f)<<19;
      unsigned long exp_v_steer = ((unsigned long)(*(inbuffer + offset++))&0xf0)>>4;
      exp_v_steer |= ((unsigned long)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_v_steer !=0)
        *val_v_steer |= ((exp_v_steer)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->v_steer = -this->v_steer;
     return offset;
    }

    const char * getType(){ return "rustler_comm/pwm"; };

  };

}
#endif