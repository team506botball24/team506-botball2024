#include <kipr/wombat.h>
//servo positions
int clawup=679;
int clawdown=1200;
int clawopen=1000;
int clawclosed=1450;

//motor & servo ports
int armPort = 0;
int clawPort = 1;
int leftPort = 0;
int rightPort = 3;

//move a servo at a controlled speed by incrementing its position periodically
void timedServo(int port, int targetPos, int delay, int increment) {
    int currentPos = get_servo_position(port);
    int dx = targetPos - currentPos;
    int sign = (0 < dx) - (dx < 0);
    //if dx is positive, sign becomes 1
    //if dx is negative, sign becomes -1
    for(int i = 0; i < abs(dx/increment); i++) {
        set_servo_position(port, currentPos + increment * sign);
        currentPos = get_servo_position(port);
        msleep(delay);
    }
}

//drive both motors at the same velocity for a time
void timedDriveStraight(int time, int vel) {
    mav(leftPort, vel);
    mav(rightPort, vel);
    msleep(time);
}

int main()
{
    enable_servos();
    //lower the arm and open the claw
    set_servo_position(clawPort,300);
    timedServo(armPort, clawdown, 30, 10);
    
    //drive straight for 9 seconds
    timedDriveStraight(9000, 1000);
    
    //turn 90 degrees
    mav(0,900);
    mav(3,-900);
    msleep(1000);
    
    //straight back for 1.5 seconds and then stop
    timedDriveStraight(1500, -900);
    ao();
    
    //raise the arm and drive forward, then stop
    timedServo(armPort, clawup, 30, 10);
    msleep(500);
    timedDriveStraight(1200, 900);
    ao();
    
    //close the claw to grab the cube
    set_servo_position(clawPort, clawclosed);
    msleep(1500);
    timedDriveStraight(1000, -900);
    
    //turn 90 degrees
    mav(0,900);
    mav(3,-900);
    msleep(200);
    
    //open the claw
    set_servo_position(clawPort,clawopen);
    msleep(1000);
    disable_servos();
    return 0;
}
