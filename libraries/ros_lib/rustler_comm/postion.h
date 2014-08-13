#ifndef ros_rustler_comm_postion_h
#define ros_rustler_comm_postion_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../ros/msg.h"

namespace rustler_comm
{

  class postion : public ros::Msg
  {
    public:

    virtual int serialize(unsigned char *outbuffer)
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return "rustler_comm/postion"; };

  };

}
#endif