#include<iostream>
#include <vector>
#include<queue>
#include <string.h>
#include <stdio.h>
#include<termios.h>
#include "smart_getway_init.h"
using namespace std;

queue<serial_ms_msg_t> send_queue;
vector<queue<sensor_controller_t> >g_queue;
extern pthread_mutex_t queue_lock;
int add_send_queue(serial_ms_msg_t* serial_sensor_data)
{
    pthread_mutex_lock(&queue_lock);
    send_queue.push(*serial_sensor_data);
    pthread_mutex_unlock(&queue_lock);
    cout<<"the queue size ="<<send_queue.size()<<endl;
    return 0;
}
int send_to_serial()
{
    g_queue.resize(7);


}





