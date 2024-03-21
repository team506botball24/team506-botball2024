#include <kipr/wombat.h>
int clawup=300;
int clawdown=1050;
int clawopen=1200;
int clawclosed=1950;

int armPort = 0;
int clawPort = 1;
int leftPort = 0;
int rightPort = 3;
void timedServo(int port, int targetPos, int delay, int increment) {
    int currentPos = get_servo_position(port);
    int dx = targetPos - currentPos;
    int sign = (0 < dx) - (dx < 0);
    //if dx is positive, sign becomes 1
    //if dx is negative, sign becomes -1
    for(int i = 0; i < abs(dx/increment); i++) {
        set_servo_position(port, currentPos + increment * sign));
        currentPos = get_servo_position(port);
        msleep(delay);
    }
}

void timedDriveStraight(int time, int vel) {
    mav(leftPort, vel);
    mav(rightPort, vel);
    msleep(time);
}
int main()
{
    enable_servos();
    //lower the arm and open the claw
    timedServo(armPort, clawdown, 30, 10);
    set_servo_position(clawPort,1200);
    //drive straight for 8.5 seconds
    timedDriveStraight(8500, 1000);
    //turn 90 degrees
    mav(0,900);
    mav(3,-900);
    msleep(1200);
    //straight for 1.5 seconds to moon base and then stop
    timedDriveStraight(1500, -900);
    ao();
    //raise the arm and drive forward, then stop
    timedServo(armPort, clawup, 30, 10);
    msleep(500);
    timedDriveStraight(900, 900);
    ao();
    //close the claw to grab the cube
    set_servo_position(clawPort,1950);
    msleep(1500);
    disable_servos();
    return 0;
}
