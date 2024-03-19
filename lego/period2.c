#include <kipr/wombat.h>
int clawup=300;
int clawdown=1050;
int clawopen=1200;
int clawclosed=1950;
void timedServo(int port, int targetPos, int delay, int increment) {
    int currentPos = get_servo_position(port);
    if(targetPos - currentPos > 0) {
        while(currentPos < targetPos) {
            set_servo_position(port, currentPos + increment);
            currentPos = get_servo_position(port);
            msleep(delay);
        }
    } else {
        while(currentPos > targetPos) {
            set_servo_position(port, currentPos - increment);
            currentPos = get_servo_position(port);
            msleep(delay);
        }
    }
}
int main()
{
    enable_servos();
    timedServo(0, clawdown, 30, 10);
    set_servo_position(1,1200);
    mav(0,1000);
    mav(3,1000);
    msleep(8500);
    mav(0,900);
    mav(3,-900);
    msleep(1200);
    mav(0,-900);
    mav(3,-900);
    msleep(1500);
    ao();
    timedServo(0, clawup, 30, 10);
    msleep(500);
    mav(0,900);
    mav(3,900);
    msleep(900);
    ao();
    set_servo_position(1,1950);
    msleep(1500);
    disable_servos();
    return 0;
}
