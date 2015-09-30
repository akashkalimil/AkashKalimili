#include <stdio.h>

void inchForwardPoms(int);
void forward(int);
void slowForward(int);
void backward(int);
void turnLeft(int);
void turnRight(int);
void collectPoms(int, int);
void openGate(int);
void closeGate(int);
#define motorR 1
#define motorL 3
#define motorRoller 0
#define motorSort 2
#define Servo1 3
#define servoRed 0
#define servoGreen 2


int main()
{
	printf("%d \n", get_channel_count());
	printf("%d \n", camera_open());
	
	
	//forward(1350);
	//inchForwardPoms(20);
	//motor(motorRoller, 850);
	//msleep(7000);
	//backward(1600);
	openGate(servoRed);
	//forward(1550);
	closeGate(servoRed);
	//turnLeft(1675);
	//backward(7000);
	//openGate(servoGreen);
	//forward(2200);
	//closeGate(servoRed);
	
	ao();
	return 0;
}

void openGate(int servo) {
	enable_servo(servo);
	if(servo==servoGreen) {
		printf("GREEEEN!!!!!!");
		set_servo_position(servo, 1200);
	}
	else if(servo==servoRed) {
		printf("RED!!!!\n");
		printf("%d\n",get_servo_enabled(servo));
		printf("%d\n",get_servo_position(servo));
		set_servo_position(servo, 590);
		printf("%d\n",get_servo_position(servo));
	}
	printf("papapa");
	disable_servo(servo);
}

void closeGate(int servo) {
	enable_servo(servo);
	if(servo==servoGreen) {
		set_servo_position(servo, 300);
	}
	else if(servo==servoRed) {
		set_servo_position(servo, 1250);
	}
	disable_servo(servo);
}

void inchForwardPoms(int duration)
{
	int inch;
	for(inch = 0; inch < duration; printf("incrementing: %d \n", inch++, duration)) {
		printf("inch beginning: %d \n", inch, duration);
		slowForward(200);
		collectPoms(4, 10); 
		printf("inching: %d to %d \n", inch, duration);
	}
	printf("end: %d to %d \n", inch, duration);
}

void collectPoms(int duration, int sortLimit)
{
	printf("%d \n", camera_update());
	int i = 0;
	int redCount = 0;
	int greenCount = 0;
	while(i < duration)
	{
		i = i + 1;//
		int numObjsRed = 0;
		int numObjsGreen = 0;
		printf("pom try: %d \n", i);
		motor(motorRoller, -850);
		msleep(500);
		off(motorRoller);
		camera_update();
		numObjsRed = get_object_count(0);
		numObjsGreen = get_object_count(1);
		if(numObjsRed >= 1 && redCount < sortLimit)
		{
			printf("found red: %d \n", i);
			motor(motorSort, 500);
			msleep(1000);
			off(motorSort);
			i = 0;
			redCount++;
		}
		else if(numObjsGreen >= 1 && greenCount < sortLimit)
		{
			printf("found green: %d \n", i);
			motor(motorSort, -500);
			msleep(1000);
			off(motorSort);
			greenCount++;
		}
		else {
			redCount = 0;
			greenCount = 0;
		}
		printf("pom loop bottom: %d \n", i);
	}
	printf("pom end: %d \n", i);
}

void forward(int dist)
{
	motor(motorL, 120);  //USE THESE VALUES!!!!
	motor(motorR, 160);  //Use accel_x() to calibrate straightness
	msleep(dist);
	off(motorL);
	off(motorR);
}

void slowForward(int dist)
{
	motor(motorL, 50);  //USE THESE VALUES!!!!
	motor(motorR, 60);  //Use accel_x() to calibrate straightness
	msleep(dist);
	off(motorL);
	off(motorR);	
}

void backward(int dist)
{
	motor(motorR, -120);  //USE THESE VALUES!!!!	
	motor(motorL, -160);
	msleep(dist);
	off(motorR);
	off(motorL);
}

void turnLeft(int dist)
{
	motor(motorL, -75);
	motor(motorR, 90); //645 when no motion afterwards
	msleep(dist);
	off(motorL);
	off(motorR);
	
}

void turnRight(int dist)
{
	motor(motorL, 75);
	motor(motorR, -90);
	msleep(dist); //645 when no motion afterwards
	off(motorR);
	off(motorL);
}
