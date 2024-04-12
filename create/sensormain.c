#include <kipr/wombat.h>
int closed = 750;
int open = 1500;
int servoPort = 0;
int wallPort = 1;
int threshold = 2000;
int maxspeed = 200;

void raiseWall() {
    set_servo_position(wallPort, 500);
}
void lowerWall() {
    set_servo_position(wallPort, 1400);
}
void swipeClose() {
    set_servo_position(servoPort, closed);
}

void swipeOpen() {
	set_servo_position(servoPort, open);   
}

void fwdDistance(int d) {
    set_create_distance(0);
    while(get_create_distance()	< d) {
        create_drive_straight(250);
        msleep(10);
    }
}
void backDistance(int d) {
    set_create_distance(0);
    while(get_create_distance()	> -d) {
        create_drive_straight(-250);
        msleep(10);
    }
}

void driveToLine() {
    int rspeed = maxspeed;
    int lspeed = maxspeed;
    while(get_create_lcliff_amt() > threshold || get_create_rcliff_amt() > threshold) {
        //if IR > threshold, then set lspeed to maxspeed. else, set lspeed to 0
        lspeed = (get_create_lcliff_amt() > threshold) ? maxspeed : 0;
        rspeed = (get_create_rcliff_amt() > threshold) ? maxspeed : 0;
        create_drive_direct(lspeed, rspeed);
        msleep(10);
    }
}
void driveToLineSingle() {
    while(get_create_lfcliff_amt() > threshold) {
        create_drive_direct(maxspeed, maxspeed);
        msleep(10);
    }
}

void turnLeft() {
	create_drive_direct(-maxspeed, maxspeed);
    msleep(1000);
}

void turnRight() {
    create_drive_direct(maxspeed, -maxspeed);
    msleep(1000);
	/*set_create_distance(0);
    while(get_create_distance()	< 180) {
        create_drive_direct(250, 0);
        msleep(10);
    }*/
}

void followLineLeft(int d) {
    set_create_distance(0);
    while(get_create_distance() < d) {
        if(get_create_lfcliff_amt() > threshold) {
            create_drive_direct(150, 200);
        } else {
            create_drive_direct(200, 150);
        }
        msleep(50);
    }
}
void followLineRight(int d) {
    set_create_distance(0);
    while(get_create_distance() < d) {
        if(get_create_rfcliff_amt() > threshold) {
            create_drive_direct(100, 50);
        } else {
            create_drive_direct(50, 100);
        }
        msleep(50);
    }
}

void twitchLeft() {
    create_stop();
    msleep(500);
    create_drive_direct(-150, 150);
    msleep(200);
    create_drive_direct(150, -150);
    msleep(200);
    create_stop();
    msleep(500);
}

void arcToLineRight() {
	   while(get_create_rfcliff_amt() > threshold) {
           create_drive_direct(150, 110);
           msleep(10);
       }
}

int main()
{
    create_connect();
    enable_servos();
    //drive to the second line and open arms
    swipeClose();
    raiseWall();
    driveToLine();
    fwdDistance(200);
    swipeOpen();
    driveToLine();
    fwdDistance(100);
    followLineLeft(360);
    lowerWall();
    turnLeft();
    fwdDistance(100);
    driveToLine();
    backDistance(300);
    create_drive_direct(maxspeed, -maxspeed);
    msleep(400);
    raiseWall();
    fwdDistance(500);
    backDistance(150);
    //FIRST BATCH DROPPED
    
    turnRight();
    msleep(700);
    //set_servo_position(servoPort, 1950);
    driveToLineSingle();
    create_drive_direct(maxspeed, -maxspeed);
    msleep(500);
    followLineLeft(250);
    arcToLineRight();
    driveToLine();
    turnRight();
    followLineLeft(400);
    
    /*
    
    //follow the line and turn left
    //rocks will be collected while moving
    followLineRight(300);
    turnLeft();
    fwdDistance(100);
    
    driveToLine();
    backDistance(400);*/
    
    
    
    create_stop();
    disable_servos();
    create_disconnect();
    return 0;
}
