#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include "Camera.h"

Camera::Camera(){
  std::string portname = "/dev/ttyUSB0";
  fd = open(portname.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  if(fd < 0){
    printf("Error attaching CMUcam v4 Camera on %s.\n", portname.c_str());
  }
  init();
}

int Camera::init(){
  struct termios tty;
  memset(&tty, 0, sizeof tty);
  if(tcgetattr (fd, &tty) != 0)
  {
    printf("Error %d from tcgetattr.\n", errno);
    return -1;
  }
    
    cfsetspeed (&tty, 19200);         // set the BAUD Rate
    
    cfmakeraw(&tty);                  // simplest version IO
    tty.c_cflag = (tty.c_cflag | CS8);// 8-bit chars
    tty.c_cflag &= ~CSTOPB;           // One Stop Bit
    tty.c_cflag &= ~CRTSCTS;          // No Hardware Flow Control
    
    tty.c_cc[VMIN]  = 0;              // read doesn't block
    tty.c_cc[VTIME] = 10;             // 0.5 seconds read timeout
  

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        printf ("Error %d from tcsetattr.\n", errno);
        return -1;
    }
    char buf[9];
    unsigned char c = '0';
    /*strcpy(buf,"BM 38400\r");
    write(fd,buf,1);
    write(fd,buf+1,1);
    write(fd,buf+2,1);
    write(fd,buf+3,1);
    write(fd,buf+4,1);
    write(fd,buf+5,1);
    write(fd,buf+6,1);
    write(fd,buf+7,1);
    write(fd,buf+8,1);
    while(c!='\r'){
      read(fd,&c,1);
    }
    
    cfsetspeed(&tty,38400);
    
    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        printf ("Error %d from tcsetattr. Problem when changing baud rate.\n", errno);
        return -1;
    }
    
    write(fd,&c,1);
    
    for(int i = 0; i < 4; i++){
      read(fd,buf+i,1);
    }
    if(buf[0] != 'A' or buf[1] != 'C' or buf[2] != 'K' or buf[3] != '\r'){
      printf ("Error recieving baud confirmation, %c%c%c%c was returned.\n", buf[0],buf[1],buf[2],buf[3]);
      return -1;
    }
    
    char buf2[5];
    strcpy(buf2,"AG 1\r");
    write(fd,buf,1);
    write(fd,buf+1,1);
    write(fd,buf+2,1);
    write(fd,buf+3,1);
    write(fd,buf+4,1);
    */
    return 0;
}

bitmap_image Camera::getFrame(){
  //tcflush(fd,TCIOFLUSH);
  bitmap_image image(80,60);
  char buf[9];// = {'s','f',' ','8','0',' ','6','0','\r'};
  strcpy(buf,"SF 80 60\r");
  write(fd,buf,1);
  write(fd,buf+1,1);
  write(fd,buf+2,1);
  write(fd,buf+3,1);
  write(fd,buf+4,1);
  write(fd,buf+5,1);
  write(fd,buf+6,1);
  write(fd,buf+7,1);
  write(fd,buf+8,1);
  unsigned char c = 0;
  for(int i = 0; i < 80; i++){
    while(c != ':'){
      read(fd,&c,1);
    }
    for(int k = 0; k < 60; k++){
      unsigned short Temp=0;
      read(fd,&c,1);
      Temp = c;
      Temp <<= 8;
      read(fd,&c,1);
      Temp |= c;
      unsigned char red=0, green=0, blue=0;
      red |= Temp >> 11;
      Temp-=(unsigned short)red << 11;
      green |= Temp >> 5;
      Temp-=(unsigned short)green << 5;
      blue |= Temp;
      red <<= 3;
      green <<= 2;
      blue <<= 3;
      image.set_pixel(i,k,red,green,blue);
    }
  }
  return image;
}
