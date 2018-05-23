#include<iostream>
#include<queue>
#include<cstdio>
#include<termios.h>
#include<string.h>
#include "smart_getway_forward.h"
#include "smart_getway_init.h"
using namespace std;

queue<serial_ms_msg_t> send_queue;
extern pthread_mutex_t queue_lock;
int add_send_queue(serial_ms_msg_t serial_sensor_data)
{
    pthread_mutex_lock(&queue_lock);
    send_queue.push(serial_sensor_data);
    pthread_mutex_unlock(&queue_lock);
    cout<<"the queue size ="<<send_queue.size()<<endl;
    return 0;
}
 int del_send_queue(serial_ms_msg_t* serial_sensor_data)
{
	pthread_mutex_lock(&queue_lock);
	//serial_sensor_data = send_queue.front();
	serial_ms_msg_t serial_sensor_front = send_queue.front();
	memcpy(serial_sensor_data, &serial_sensor_front, sizeof(send_queue.front()));
	send_queue.pop();
    pthread_mutex_unlock(&queue_lock);
    cout<<"the queue size ="<<send_queue.size()<<endl;
    return 0;
}
int size_send_queue()
{
	int size = send_queue.size();
	return size;
}

int send_to_serial()
{
	


}

