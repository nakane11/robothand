#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h>
#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/UInt16.h>

Servo servo_array[4];
std_msgs::UInt16 sensorValue;

void servo_cb( const std_msgs::Float32MultiArray& msg){
  for (int i=0; i < sizeof(servo_array)/sizeof(Servo); i++){
      servo_array[i].write(msg.data[i]);
      }
}

ros::NodeHandle  nh;
ros::Subscriber<std_msgs::Float32MultiArray> sub("servo", servo_cb);
ros::Publisher pub("sensor", &sensorValue);

void setup(){
  pinMode(0, INPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);   

  for (int i=0; i < sizeof(servo_array)/sizeof(Servo); i++){
      servo_array[i].attach(2+i); //attach it to pin 2-5                                                      
      }
}

void loop(){
  sensorValue.data = analogRead(0);
  pub.publish(&sensorValue);
  nh.spinOnce();
  delay(1);
}
