#ifndef _BEACON_H_
#define _BEACON_H_

extern double show_chn[50];


//send a frame to car ,call when it is necessary;
void send_data(uint8 chn , double data);
//look up data in 24l01 to receive new data,call it in pit interrupt ;
void data_rec();
void data_refresh();
#endif

