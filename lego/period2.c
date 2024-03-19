#include <kipr/wombat.h>
int clawup=300;
int clawdown=1050;
int clawopen=1200;
int clawclosed=1950;
int main()
{
    enable_servos();
    set_servo_position(0,1050);
    set_servo_position(1,1200);
    mav(0,1000);
    mav(3,1000);
    msleep(8000);
    mav(0,1000);
    mav(3,-1000);
    msleep(800);
    ao();
    set_servo_position(0,1000);
    set_servo_position(0,800);
    set_servo_position(0,600);
    set_servo_position(0,400);
    set_servo_position(0,300);
    msleep(500);
    mav(0,500);
    mav(3,500);
    msleep(200);
    ao();
    set_servo_position(1,1950);
    disable_servos();
    return 0;
}
