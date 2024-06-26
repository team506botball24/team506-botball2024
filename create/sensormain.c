#include <kipr/wombat.h>

const int closed = 800;
const int open = 1100;
const int inverted = 300;
const int servoPort = 0;
const int wallPort = 1;
const int threshold = 2000;
const int maxspeed = 200; //things might break if this is changed

void raiseWall();
void lowerWall();
void swipeClose();
void swipeOpen();
void swipeInverted();
void swipeStraight();

void fwdDistance(int d);
void backDistance(int d);

void driveToLine();
void driveToLineFront();
void driveToLineSingle();

//warning: these are timing based
void turnLeft();
void turnLeftTime(int t);
void turnRight();
void turnRightTime(int t);

void followLineLeft(int d);
void followLineWideLeft(int d);
void followLineRight(int d);
void followLineInsideRight(int d);
void followLineWideRight(int d);
void followLineMiddle(int d);

void twitchLeft(); //this can be removed
void arcToLineRight(); //THIS NEEDS TO BE CHECKED

int main()
{
    wait_for_light(0); //<--- *NOT TESTED*
    shut_down_in(119);
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
    //drive straight, then catch the rock and turn left
    fwdDistance(400);
    lowerWall();
    turnLeft();
    fwdDistance(100);
    //line up with next line while pushing fuel poms
    driveToLineFront();
    backDistance(200);
    //turn to the rock heap and deposit rocks
    create_drive_direct(maxspeed, -maxspeed);
    msleep(400);
    raiseWall();
    fwdDistance(500);
    backDistance(140);
    // --FIRST BATCH DROPPED--
    //turn around and follow line to middle
    turnLeft();
    msleep(300);
    //turn the arms into a straight line
    set_servo_position(servoPort, 570);
    followLineRight(150);
    //twitch the pom right
    turnRightTime(400);
    turnLeftTime(400);
    //open the arms up
    create_stop();
    swipeOpen();
    msleep(300);
    //go forward and capture first rock
    fwdDistance(200);
    create_stop();
    lowerWall();
    msleep(200);
    backDistance(200);
    //turn and go to second rock
    turnLeftTime(200);
    raiseWall();
    fwdDistance(160);
    create_stop();
    //    set_servo_position(servoPort, 1200);
    //    msleep(500);
    lowerWall();
    msleep(500);
    //turn around and go back
    turnLeftTime(1200);
    followLineWideLeft(300);
    raiseWall();
    fwdDistance(100);
    turnLeftTime(300);
    fwdDistance(50);
    backDistance(250); // this part keeps changing for some reason
  
    // --SECOND BATCH DROPPED--
    //turn and drive to center line
    ao();
    turnLeftTime(1300);
    ao();
    driveToLine();
    //go forward to first pom pile and stop
    //fwdDistance(100);
    create_stop();
    //sort first pile
    swipeInverted();
    msleep(1000);
    swipeOpen();
    msleep(500);
    swipeInverted();
    msleep(500);
    //go forward to second pom pile and stop
    fwdDistance(200);
    create_stop();
    //sort second pile
    swipeOpen();
    msleep(1000);
    swipeInverted();
    msleep(500);
    swipeStraight();
    backDistance(400);
    turnRightTime(400);
    backDistance(600);
    turnLeftTime(900);
    create_stop();
        
    
    disable_servos();
    create_disconnect();
    return 0;
}

// implementations:
void raiseWall() {
    set_servo_position(wallPort, 500);
}
void lowerWall() {
    set_servo_position(wallPort, 1500);
}
void swipeClose() {
    set_servo_position(servoPort, closed);
}

void swipeInverted() {
    set_servo_position(servoPort, inverted);
}

void swipeOpen() {
	set_servo_position(servoPort, open);   
}

void swipeStraight() {
    set_servo_position(servoPort, 530);
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
void driveToLineFront() {
    int rspeed = maxspeed;
    int lspeed = maxspeed;
    while(get_create_lfcliff_amt() > threshold || get_create_rfcliff_amt() > threshold) {
        //if IR > threshold, then set lspeed to maxspeed. else, set lspeed to 0
        lspeed = (get_create_lfcliff_amt() > threshold) ? maxspeed : 0;
        rspeed = (get_create_rfcliff_amt() > threshold) ? maxspeed : 0;
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
	create_drive_direct(-200, 200);
    msleep(1000);
}

void turnLeftTime(int t) {
	create_drive_direct(-200, 200);
    msleep(t);
}

void turnRight() {
    create_drive_direct(200, -200);
    msleep(1000);
}
        
void turnRightTime(int t) {
	create_drive_direct(200, -200);
    msleep(t);
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
void followLineWideLeft(int d) {
    set_create_distance(0);
    while(get_create_distance() < d) {
        if(get_create_lcliff_amt() > 2200) {
            create_drive_direct(50, 200);
        } else {
            create_drive_direct(200, 50);
        }
        msleep(50);
    }
}
void followLineRight(int d) {
    set_create_distance(0);
    while(get_create_distance() < d) {
        if(get_create_rfcliff_amt() > 2200) {
            create_drive_direct(200, 100);
        } else {
            create_drive_direct(100, 200);
        }
        msleep(50);
    }
}
void followLineWideRight(int d) {
    set_create_distance(0);
    while(get_create_distance() < d) {
        if(get_create_rcliff_amt() > 2200) {
            create_drive_direct(200, 50);
        } else {
            create_drive_direct(50, 200);
        }
        msleep(50);
    }
}
void followLineInsideRight(int d) {
    set_create_distance(0);
    while(get_create_distance() < d) {
        if(get_create_rfcliff_amt() > threshold) {
            create_drive_direct(150, 200);
        } else {
            create_drive_direct(200, 150);
        }
        msleep(50);
    }
}
void followLineMiddle(int d) {
    set_create_distance(0);
    int rspeed = maxspeed;
    int lspeed = maxspeed;
    while(get_create_distance() < d) {
        lspeed = (get_create_lcliff_amt() > threshold) ? maxspeed : maxspeed/2;
        rspeed = (get_create_rcliff_amt() > threshold) ? maxspeed : maxspeed/2;
        create_drive_direct(lspeed, rspeed);
        msleep(10);
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
