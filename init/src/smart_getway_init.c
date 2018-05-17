#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "smart_getway_init.h"
#include "smart_getway_parse.h"

case_controller_t* fill_case_controller() 
{
    case_controller_t* case_controller = (case_controller_t*)malloc(sizeof(case_controller_t));
    if(!case_controller) {
        printf("malloc serial_controller fail\n");
        return NULL;
    }
    case_controller->serial_num = get_sys_serial_num();
    case_controller->serial_control = (serial_controller_t*)malloc(sizeof(serial_controller_t)*get_sys_serial_num());
    if(!(case_controller->serial_control)) {
        printf("malloc case_controller->serial_control fail\n");
    }
    return case_controller;
}
int  fill_serial_controller(int serial_id, serial_controller_t* serial_controller)
{
    printf("_____fill_serial_controller0,%d\n",get_sys_serial_num());
    if (serial_id >= get_sys_serial_num()){
        return -1;
    }
    printf("_____fill_serial_controller1\n");
    serial_controller->dev_num = get_sys_serial_dev_num(serial_id);
    printf("_____fill_serial_controller2\n");
    //serial_controller->dev_num = get_sys_serial_dev_num(serial_id);
    printf("_____fill_serial_controller2.1\n");
    serial_controller->dev_control = (dev_controller_t*)malloc(sizeof(dev_controller_t)*(serial_controller->dev_num));
    if(!serial_controller->dev_control) {
        printf("malloc serial_controller->dev_control fail\n");
    }
    printf("_____fill_serial_controller3\n");
    snprintf(serial_controller->serial_name,SERIAL_NAME_LENGTH, "serial-%d", serial_id);
    printf("_____fill_serial_controller4\n");
    return 0;
}
int  fill_dev_controller(int serial_id, int dev_id , dev_controller_t* dev_control)
{
    printf("______fill_dev_controller__start_____________\n");
    int sensor_num = get_sys_dev_info_sensor_num(serial_id, dev_id);
    dev_control->sensor_control = (sensor_controller_t*)malloc(sizeof(sensor_controller_t)*sensor_num);
    dev_control->dev_id = dev_id;
    dev_control->sensor_num = get_sys_dev_info_sensor_num(serial_id, dev_id);
    printf("______fill_dev_controller__end_____________\n");
    return 0;
}

int fill_sensor_controller(int serial_id, int dev_id, int sensor_id, 
                                            sensor_controller_t* sensor_control) {
    
  
    sensor_control->sensor_id = sensor_id;
    sensor_control->sensor_type = get_sys_sensor_info_sensor_type(serial_id, dev_id, sensor_id);
    get_sys_sensor_info_sensor_name(serial_id, dev_id, sensor_id,sensor_control->sensor_name);
    get_sys_sensor_info_sensor_gather_cmd(serial_id, dev_id, sensor_id,sensor_control->gather_cmd);
    sensor_control->gather_freq = get_sys_sensor_info_sensor_gather_freq(serial_id, dev_id, sensor_id);      
    return 0;
}

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	if  ( tcgetattr( fd,&oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}

	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':  
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch( nSpeed )
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;
	else if ( nStop == 2 )
        newtio.c_cflag |=  CSTOPB;
        newtio.c_cc[VTIME]  = 0;
        newtio.c_cc[VMIN] = 0;
        tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0) {
		perror("com set error");
		return -1;
	}
	return 0;
}

int serial_init() 
{
    int fd;
    int ret;
    fd = open( "/dev/ttyS0", O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd == -1) {
        perror("Can't Open Serial Port\n");
        return(-1);
    } else {
        printf("open ttyS0 .....\n");
    }
    if(fcntl(fd, F_SETFL, 0) < 0) {
        printf("fcntl failed!\n");
    } else {
        printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));
    }
    if(isatty(STDIN_FILENO) == 0) {
        printf("standard input is not a terminal device\n");
    }
    else {
        printf("isatty success!\n");
    }
    printf("fd-open = %d\n",fd);
    if((ret = set_opt(fd, 9600, 8, 'N', 1))<0)
    {
        perror("set_opt error");
        return;
    }
    return fd;
}