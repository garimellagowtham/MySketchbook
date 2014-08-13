/** avr_rustler
*  Author: Subhransu Mishra
*  email: subhransu.kumar.mishra@gmail.com
*  Description:This program controls a rustler car by receiving
*              instruction sent from a computer over Serial2 in the
*              in the format specified in uav.h file.
*  TO run the node to receive ros messages on the computer,
*   rosparam set /serial_node/baud 115200
*   rosrun rosserial_python serial_node.py /dev/ttyACM1
*/

//firmware
//#include <PWM.h> //http://forum.arduino.cc/index.php?topic=117425.0
#include "uav.h"
#include <Servo.h>
#include <SPI.h>
#include "Timer.h"
#include <util.h>
#include <ros.h>
#include <rustler_comm/Encoder_data.h>
#include <diagnostic_msgs/DiagnosticStatus.h>
#include <rustler_comm/SerialCommand.h>
#include <std_msgs/String.h>
//#include "String"
//********************TODO*******************************/
//make your own servo library or some basic set of commands so that one doesn't have to stick to 50Hz pwm pulse
  //The escs don't need a 50Hz(20ms) pulse, they just do their work based on on time. 
  //This allows us to have faster update rate
//Make the Serial2 data receive non-blocking
  //Nows it waits for the next byte to receive
//Implement the functions
    //raw2finalFullRange- This is what is being used currently
    //raw2finalDirect-  

//The layout of the arduino mega pinouts are scrambled in apm2.5
//The followign sequence refers to the apm 2.5 out1 out2........out 11
int OUT[]={12,11,8,7,6,3,2,5,13,45,44};
int pin_batt_volt_pc=A0;
int pin_batt_volt_main=A13;
int pin_buzzer=OUT[2];//out 3 connected to buzzer
const float conToDeg = 0.08789;

//Encoder enable pin
#define CS A2
#define CS2 53
#define CS3 40
//set a timer
Timer t_timer;

//Declare Ros nodehandle and publishers
ros::NodeHandle  nh;

rustler_comm::Encoder_data enc_msg;
diagnostic_msgs::KeyValue voltkeyvals[2];
diagnostic_msgs::DiagnosticStatus diag_msg;
std_msgs::String debug_msg;
char debugdata[30];
ros::Publisher enc_pub("encoder", &enc_msg);
ros::Publisher diag_pub("heartbeat", &diag_msg);
ros::Publisher debug_pub("debuginfo", &debug_msg);

//Subscribers:
//Declaring Function type:
void CommandEvent(const rustler_comm::SerialCommand &);
ros::Subscriber<rustler_comm::SerialCommand> cmd_sub("serialcmd", &CommandEvent );



float volt_pc=0.0f, volt_main=0.0f;
//static const int BUF_LEN = 40;
  //char buf[BUF_LEN];
uint16_t servo_min[]={1000,1000};
uint16_t servo_max[]={2000,2000};
Servo servo_car[2];//0:steering, 1:Drive  

//The 16 bit number exactly as sent by the computer.
uint16_t servo_pwm_raw[2]={1500,1500};

//Processed data.
uint16_t servo_pwm[2] = {1500,1500};

//variable for Encoder
float ABSposition;
float ABSposition_last;
float ABSpeed;
uint8_t encoder[1];

float time_last;
float deg = 0.00;


void update_pwm(void) {
  for(int i=0; i<2; i++) {
    //servo_pwm[i] = (uint16_t)(servo_min[i] + (float)(servo_max[i]-servo_min[i])*((float)servo_pwm_raw[i]/65335.0) );
    servo_pwm[i]=servo_pwm_raw[i];
    //raw2finalFullRange
    //raw2finalDirect
    
    if(servo_pwm[i] < servo_min[i])
      servo_pwm[i]=servo_min[i];
      
    if(servo_pwm[i] > servo_max[i])
      servo_pwm[i]=servo_max[i];
     
    servo_car[i].writeMicroseconds(servo_pwm[i]);
    
    
    //Serial2.print("\tPwm");Serial2.print(i);Serial2.print(":");  Serial2.print(servo_pwm[i]);
  }
  //Serial2.println(""); 
}


uint8_t SPI_T (uint8_t msg)    //Repetitive SPI transmit sequence
{
   uint8_t msg_temp = 0;           //vairable to hold recieved message
   digitalWrite(CS,LOW);    //select spi device enable slave
   delayMicroseconds(5);
   msg_temp = SPI.transfer(msg);   //send command and recieve message
   delayMicroseconds(5);
   digitalWrite(CS,HIGH);          //deselect spi device
   return msg_temp;     //return recieved 8-bit message
}


void myEncoderEvent()
{
   uint8_t recieved;           //vairable to hold recieved position
   ABSposition = 0;            //reset position vairable
   
   SPI.begin();                //start transmition
   digitalWrite(CS,LOW);
   
  
   SPI_T(0x10);                    //issue read position command
   delayMicroseconds(5);  //delay a minimum of 5 microseconds
   
   recieved = SPI_T(0x00);     //issue NOP message to check if encoder is ready to send
   while (recieved != 0x10)    //loop while encoder sends back echo of command
   {
     recieved = SPI_T(0x00);   //cleck again if encoder is still working 
     delayMicroseconds(5);     //wait 5 microseconds
   }
   encoder[0] = SPI_T(0x00);    //Recieve MSB
   delayMicroseconds(5);     //delay 5 microseconds before reading in LSB
   encoder[1] = SPI_T(0x00);    // recieve LSB
 
   SPI.end();                //end transmition
   
   encoder[0] &=~ 0xF0;        //mask out the first 4 bits
   float time_now = millis();   
   ABSposition = encoder[0] << 8;    //shift MSB to correct ABSposition in ABSposition message
   ABSposition += encoder[1];        // add LSB to ABSposition message to complete message
  ABSposition = ABSposition*conToDeg;
  if(ABSposition > 90 + ABSposition_last){ABSposition_last=360+ABSposition_last;}
  if(ABSposition_last > ABSposition)
    ABSpeed = double (1000.0*(ABSposition_last - ABSposition))/((double)(time_now - time_last));
  else
     ABSpeed = double (1000.0*(-ABSposition_last + ABSposition))/((double)(time_now - time_last));
  time_last = time_now; 
 
  ABSposition_last = ABSposition;    //set last position to current position
  //Publishing the data using ros publisher:
  enc_msg.angle = ABSpeed;
  enc_msg.angvel = ABSposition;
  enc_msg.time = time_now;
  enc_pub.publish(&enc_msg); 
}
void Heartbeat()
{
  //char buf[BUF_LEN]={'\0'};
  volt_pc = 0.013443*(float)analogRead(pin_batt_volt_pc);//0.013443=0.0049/0.3645
  volt_main = 0.049742*(float)analogRead(pin_batt_volt_main);
   //if(volt_pc<6.2)
    //tone(pin_buzzer,1000,1000);
 /* if (volt_main<9.3)
    tone(pin_buzzer,5000,1000);
  else
    noTone(pin_buzzer);
    */
  //Setting Message and publishing it
  diag_msg.level = diag_msg.OK;
  sprintf(voltkeyvals[0].value,"%f",volt_pc);
  sprintf(voltkeyvals[1].value,"%f",volt_main);
  diag_pub.publish(&diag_msg);
//  sprintf(buf,"volt_pc:%f\n volt_main:%f\n",volt_pc, volt_main);
  //send_statusmsg(buf);
  //Serial.println(volt_pc);
    
  //sprintf(buf,"volt_main:%f\n",volt_pc);
  //send_statusmsg(buf);
  
  //Serial2.write(buf,
  //Serial.println(volt_main);
}
void CommandEvent(const rustler_comm::SerialCommand & cmd)
{
   uint16_t hostpwm[2];
   uint16_t timediff[3];
    switch(cmd.signature)
    {      
      case (char)(UAV_DEV_MOTORS  | UAV_CMD_ON) :
        //char *msg = "avr is on";
        //buf = "avr is on";
        sprintf(debugdata,"avr is on");
        debug_pub.publish(&debug_msg);
        break;
        
      case (char)(UAV_DEV_MOTORS  | UAV_CMD_WRITE) :
        
        sprintf(debugdata,"Received cmd");
        debug_pub.publish(&debug_msg);
        if(cmd.data_length != 2)
        {
          sprintf(debugdata,"Received wrong length msg");
          debug_pub.publish(&debug_msg);
          break;
        }
        servo_pwm_raw[0] = cmd.data[0];
        servo_pwm_raw[1] = cmd.data[1];

        update_pwm();
        break;
        
      case (char)(UAV_DEV_MOTORS  | UAV_CMD_READ) :
        sprintf(debugdata,"Servo_pwm_raw:%d\t%d",servo_pwm_raw[0], servo_pwm_raw[1]);
        debug_pub.publish(&debug_msg);
        break;
    }
}

void setup() {
  //Initialize ros nodehandle. 
  nh.initNode();
  nh.advertise(enc_pub);
  nh.advertise(diag_pub);
  nh.advertise(debug_pub);
  nh.subscribe(cmd_sub);
  //Setup messages:
  diag_msg.name = "RcCar";
  diag_msg.message = "The Heartbeat message";
  diag_msg.hardware_id = "CAR1"; //for now random id;
  voltkeyvals[0].key = "volt_pc";
  voltkeyvals[1].key = "volt_main";
  diag_msg.values = voltkeyvals;
  diag_msg.values_length = 2;
  
  debug_msg.data = debugdata;

  for(uint8_t i=0;i<2;i++)
    servo_car[i].attach(OUT[i]);
    
  pinMode(pin_buzzer,OUTPUT);
  
  pinMode(pin_batt_volt_pc, INPUT);
  pinMode(pin_batt_volt_main, INPUT);
  
  //disable the pullup regs so that the adc reading are not affected
  digitalWrite(pin_batt_volt_pc,LOW);
  digitalWrite(pin_batt_volt_main,LOW);
    
  //The startup value for the servo
  for(uint8_t i=0;i<2;i++)
    servo_car[i].writeMicroseconds(servo_pwm[i]);
    
  //setup  for encoder
  //Serial.println("Encoder Setup start");
  ABSposition = 0;                       //initilaize variables
  ABSposition_last = 0;
  pinMode(CS,OUTPUT);    //Slave Select
  pinMode(CS2,OUTPUT);
  pinMode(CS3,OUTPUT);
  digitalWrite(CS,HIGH);    
  digitalWrite(CS2,HIGH); 
  digitalWrite(CS3,HIGH); 
  SPI.begin();                           //Initialize SPI bus
  SPI.setBitOrder(MSBFIRST);             //Bits come in from encoder as MSB first
  SPI.setDataMode(SPI_MODE0);            //SPI mode 0: CPOL and CPHA are both 0
  SPI.setClockDivider(SPI_CLOCK_DIV16);  //Clock speed for SPI 

  delay(2000);                           //Delay 2 seconds
  SPI.end();                             //Disable SPI bus
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////read fist encoder postion
   uint8_t recieved;           //vairable to hold recieved position
   ABSposition_last = 0;            //reset position vairable
   
   SPI.begin();                //start transmition
   digitalWrite(CS,LOW);
   
  
   SPI_T(0x10);                    //issue read position command
   delayMicroseconds(5);  //delay a minimum of 5 microseconds
   
   recieved = SPI_T(0x00);     //issue NOP message to check if encoder is ready to send
   while (recieved != 0x10)    //loop while encoder sends back echo of command
   {
     recieved = SPI_T(0x00);   //cleck again if encoder is still working 
     delayMicroseconds(5);     //wait 5 microseconds
   }
   //Serial.println("received Next data command");
   encoder[0] = SPI_T(0x00);    //Recieve MSB
   delayMicroseconds(5);     //delay 5 microseconds before reading in LSB
   encoder[1] = SPI_T(0x00);    // recieve LSB
 
   SPI.end();                //end transmition
   
   encoder[0] &=~ 0xF0;        //mask out the first 4 bits
    
   ABSposition_last = encoder[0] << 8;    //shift MSB to correct ABSposition in ABSposition message
   ABSposition_last += encoder[1];        // add LSB to ABSposition message to complete message
   ///////////////////////////////////////////////////////////////////////////////////////////////////////
   
  t_timer.every(10,myEncoderEvent);
  t_timer.every(2*1000,Heartbeat); 
  delay(100);
  time_last = millis();

}

void loop() 
{
  t_timer.update();
  nh.spinOnce();//Publish all the messages  will change this to another callback
  delay(1);
}
