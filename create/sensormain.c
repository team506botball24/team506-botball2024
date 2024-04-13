#include <kipr/wombat.h>

const int closed = 750;
const int open = 1500;
const int servoPort = 0;
const int wallPort = 1;
const int threshold = 2000;
const int maxspeed = 200; //things might break if this is changed

void raiseWall();
void lowerWall();
void swipeClose();
void swipeOpen();

void fwdDistance();
void backDistance();

void driveToLine();
void driveToLineSingle();

//warning: these are timing based
void turnLeft();
void turnRight();

void followLineLeft();
void followLineRight();

void twitchLeft(); //this can be removed
void arcToLineRight(); //THIS NEEDS TO BE CHECKED

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
    //follow the line, then catch the rock and turn left
    followLineLeft(360);
    lowerWall();
    turnLeft();
    fwdDistance(100);
    //line up with next line while pushing fuel poms
    driveToLine();
    backDistance(300);
    //turn to the rock heap and deposit rocks
    create_drive_direct(maxspeed, -maxspeed);
    msleep(400);
    raiseWall();
    fwdDistance(500);
    backDistance(150);
    // --FIRST BATCH DROPPED--
    //turn around and go back to the line
    turnRight();
    msleep(700);
    //set_servo_position(servoPort, 1950);
    driveToLineSingle();
    //follow the line up and then arc right, catching the 2 rocks
    create_drive_direct(maxspeed, -maxspeed);
    msleep(500);
    followLineLeft(250);
    arcToLineRight();
    //line up and then follow the line to the rock heap
    driveToLine();
    turnRight();
    followLineLeft(400);    
    backDistance(150);
    // --SECOND BATCH DROPPED--

    /* PSUEDO CODE!!
    //turn and drive to the middle
    turnRight();
    fwdDistance(250); //check
    turnRight();
    driveToLine();
    //line up again (could be removed if needed)
    backDistance(150);
    turnLeft();
    driveToLine();
    backDistance(150); //check
    turnRight();
    driveToLine();
    //drive forward and sort poms!
    
    */
    
    
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


