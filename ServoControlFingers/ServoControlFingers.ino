#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h>
#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";

Servo servo_array[4];
void servo_cb( const std_msgs::Float32MultiArray& msg){
  chatter.publish( &str_msg );
  for (int i=0; i < sizeof(servo_array)/sizeof(Servo); i++){
      servo_array[i].write(msg.data[i]);
      }
                                           
}

ros::Subscriber<std_msgs::Float32MultiArray> sub("test", servo_cb);

void setup(){
  pinMode(13, OUTPUT);
  str_msg.data = hello;
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);   

  for (int i=0; i < sizeof(servo_array)/sizeof(Servo); i++){
      servo_array[i].attach(2+i); //attach it to pin 2-5                                                      
      }
}

void loop(){
  nh.spinOnce();
  delay(1);
}
