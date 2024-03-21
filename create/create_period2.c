#include <kipr/wombat.h>
// Wombat #3867

void drive_forward();
void turn_left90();
void turn_right90();
void turn_left();
void turn_right();
void drive_back();
void swipe_close();
void swipe_open();

int main()
{
    create_connect();
    enable_servos();
 // 0-15 drive forward to the first moon rocks on a line then turn left
    set_servo_position(0,1700);
    msleep(100);
    drive_forward();
    msleep(4000);
    turn_left90();
    set_servo_position(0,1500);
    drive_forward();
    msleep(1000);
    turn_right();
    msleep(1000);
    drive_forward();
    msleep(2000);
    create_stop();
    disable_servos();
    
    

 // 15-30 drive forward to collect 3 other moon rocks and push all moon rocks into Rock heap

    
 // 30-45 Turn to fuel poms and push them into Area 4

    
 // 45-60 Drive to green and red poms to sort them into Areas 2 and 3
enable_servos();
    swipe_open();
    msleep(100);
    drive_forward();
    msleep(550);
    create_stop();
    swipe_close();
    msleep(500);
    swipe_open();
    swipe_close();
    drive_forward();
    msleep(900);
    create_stop();
    swipe_open();
    msleep(500);
    swipe_close();
    

    disable_servos();
    create_disconnect();
}

//Functions for create
//something for robot to drive forward & backward
void drive_forward()
{
    create_drive_direct(250,250);
}

void drive_back()
{
    create_drive_direct(-250,-250);
}
//something for left turn & right turn(90 degrees+non 90 degree turns)
void turn_right90()
{
    create_drive_direct(250,-250);
    msleep(750);
    create_stop();
}
void turn_left90()
{
    create_drive_direct(-250,250);
    msleep(750);
    create_stop();
}
void turn_left()
{ 
    create_drive_direct(-250,250);
    create_stop();
}
void turn_right()
{ 
    create_drive_direct(250,-250);
    create_stop();
}

//something to swipe with pom sorter
void swipe_close()
{
    set_servo_position(0,420);
    msleep(500);
}
void swipe_open()
{
    set_servo_position(0,1350);
    msleep(500);
}
      
