#include <kipr/wombat.h>
int closed = 655;
int open = 1900;
int servoPort = 0;
int threshold = 2000;
int maxspeed = 200;

void swipeClose() {
    set_servo_position(servoPort, closed);
}

void swipeOpen() {
	set_servo_position(servoPort, open);   
}

void fwdDistance(int d) {
    set_create_distance(0);
    while(get_create_distance()	< d) {
        create_drive_straight(500);
        msleep(10);
    }
}

void driveToLine() {
    int rspeed = maxspeed;
    int lspeed = maxspeed;
    while(get_create_lfcliff_amt() > threshold || get_create_rfcliff_amt() > threshold) {
        //if IR > threshold, then set lspeed to maxspeed. else, set lspeed to 0
        lspeed = (get_create_lcliff_amt() > threshold) ? maxspeed : 0;
        printf("lcliff: %d\n", get_create_lcliff_amt());
        rspeed = (get_create_rcliff_amt() > threshold) ? maxspeed : 0;
        printf("rcliff: %d\n", get_create_rcliff_amt());
        create_drive_direct(lspeed, rspeed);
        msleep(50);
    }
}

void turnLeft() {
	create_drive_direct(-maxspeed, maxspeed);
    msleep(1000);
}

void turnRight() {
	set_create_distance(0);
    while(get_create_distance()	< 180) {
        create_drive_direct(500, 0);
        msleep(10);
    }
}

void followLineLeft(int d) {
    set_create_distance(0);
    while(get_create_distance() < d) {
        if(get_create_lfcliff_amt() > threshold) {
            create_drive_direct(200, 400);
        } else {
            create_drive_direct(400, 200);
        }
        msleep(50);
    }
}

void twitchLeft() {
    create_drive_direct(-250, 250);
    msleep(50);
    create_drive_direct(250, -250);
    msleep(50);
}

int main()
{
    create_connect();
    enable_servos();
    //drive to the second line and open arms
    swipeClose();
    driveToLine();
    driveToLine();
    swipeOpen();
    
    //turn left and follow the line
    //rocks will be collected while moving
    turnLeft();
    followLineLeft(2000); //check
    
    //turn right and do the same thing
    //also push the 3 poms
    turnRight();
    followLineLeft(500); //check
    twitchLeft();
    followLineLeft(100); //check
    twitchLeft();
    followLineLeft(100); //check
    twitchLeft();
    followLineLeft(500); //check
    
    create_stop();
    disable_servos();
    create_disconnect();
    return 0;
}
