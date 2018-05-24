#include<iostream>
#include<queue>
#include<cstdio>
#include<termios.h>
#include<string.h>
#include "smart_getway_forward.h"
#include "smart_getway_init.h"
using namespace std;

queue<server_control_cmd_t> send_queue;
extern pthread_mutex_t queue_lock;
int add_send_queue(server_control_cmd_t server_control_data)
{
    pthread_mutex_lock(&queue_lock);
    send_queue.push(server_control_data);
    pthread_mutex_unlock(&queue_lock);
    cout<<"the queue size ="<<send_queue.size()<<endl;
    return 0;
}
int del_send_queue(server_control_cmd_t* server_control_data)
{
	pthread_mutex_lock(&queue_lock);
	//serial_sensor_data = send_queue.front();
	server_control_cmd_t server_control_front = send_queue.front();
	memcpy(server_control_data, &server_control_front, sizeof(send_queue.front()));
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

