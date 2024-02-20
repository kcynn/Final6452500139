#include <ros.h>
#include <std_msgs/Int32.h>


ros::NodeHandle nh;


const int button1_pin = 2;
const int button2_pin = 4;
const int button3_pin = 6;

std_msgs::Int32 button_msg;
ros::Publisher button_pub("button", &button_msg);

void setup() {
  nh.initNode();
  nh.advertise(button_pub);

  
  pinMode(button1_pin, INPUT);
  pinMode(button2_pin, INPUT);
  pinMode(button3_pin, INPUT);

  Serial.begin(9600); // เริ่มต้นการสื่อสารผ่าน Serial Monitor
}

void loop() {
  bool button1_pressed = digitalRead(button1_pin) == HIGH;
  bool button2_pressed = digitalRead(button2_pin) == HIGH;
  bool button3_pressed = digitalRead(button3_pin) == HIGH;

  if (button1_pressed && !button2_pressed && !button3_pressed) {
    button_pub.publish(&button_msg); // ส่งข้อมูลผ่าน publisher
    Serial.println("Turn Right");
    delay(1000);
  }
  
  if (!button1_pressed && button2_pressed && !button3_pressed) {
    button_pub.publish(&button_msg); // ส่งข้อมูลผ่าน publisher
    Serial.println("Turn Left");
    delay(1000);
    
  }
  
  if (!button1_pressed && !button2_pressed && button3_pressed) {
    button_pub.publish(&button_msg); // ส่งข้อมูลผ่าน publisher
    Serial.println("Backward");
    delay(1000);
    
  }
  
  if (button1_pressed && button2_pressed && !button3_pressed) {
    button_pub.publish(&button_msg); // ส่งข้อมูลผ่าน publisher
    Serial.println("Forward");
    delay(1000);
    
  }
  
  nh.spinOnce();
}
