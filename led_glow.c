#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define GPIO 488 //gpio 2_0 in Hikey 96 board
#define MAX_BUF 100
main()
{

  int fd  = 0 ;
  char buf[MAX_BUF] = { 0 } ;

  sprintf(buf, "/sys/class/gpio/export");
  fd = open(buf, O_WRONLY);
  if(fd < 0) {
    printf("file:: %s open failed\n",buf);
    return;
  }
  printf("file:: %s open success fd %d\n",buf, fd);
  sprintf(buf, "%d", GPIO);
  printf("file :: %s\n", buf);
  write(fd, buf, strlen(buf));
  close(fd);

  sprintf(buf, "/sys/class/gpio/gpio%d/direction", GPIO);
  fd = open(buf, O_WRONLY);
  if(fd < 0) {
    printf("file:: %s open failed\n",buf);
    return;
  }

  printf("file:: %s open success fd %d\n",buf, fd);
  //Set out direction
  write(fd, "out", 3); 
  close(fd);

  sprintf(buf, "/sys/class/gpio/gpio%d/value", GPIO);
  fd = open(buf, O_WRONLY);
  if(fd < 0) {
    printf("file:: %s open failed\n",buf);
    return;
  }

  printf("file:: %s open success fd %d\n",buf, fd);

  while(1) {
    write(fd, "1", 1);
    sleep(1);
    write(fd, "0", 1);
    sleep(1);
  }
}


