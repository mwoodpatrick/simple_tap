/* tap_access.c - tap interface demo access
 * The Linux Channel
 * Author: Kiran Kankipati
 * Updated: 25-jan-2017
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netpacket/packet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <malloc.h>
#include <net/ethernet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <signal.h>


static int tap_open(char *dev)
{   struct ifreq ifr;
    int fd;

    if ((fd = open("/dev/net/tun", O_RDWR)) < 0) { return -1; }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    if (*dev) strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    if (ioctl(fd, TUNSETIFF, (void *) &ifr) < 0) { goto failed; } 

    strcpy(dev, ifr.ifr_name); return fd;

failed:
    close(fd); return -1;
}


int tapfd;
void signal_handler(int sig) { close(tapfd); exit(1); }

int main()
{	unsigned char buf[2000];
	unsigned char name[20];
	int i;
	int numbytes=0;
	
	
	strcpy(name,"tapint"); tapfd=tap_open(name); 
	if(tapfd<0) { printf("port open error!\n"); return 0; }

signal(SIGHUP,signal_handler);
signal(SIGTERM,signal_handler);
signal(SIGKILL,signal_handler);
signal(SIGSTOP,signal_handler);
signal(SIGINT,signal_handler);

repeat:	
	numbytes=read(tapfd, buf, 2000);
	if(numbytes<=0) { usleep(100); goto repeat;}
	
	printf("\tTAP Data:");
	for (i=0; i<numbytes; i++) printf("%02x:", buf[i]);
	printf("\n\n");
   
	goto repeat;	

	close(tapfd);
	return 0;
}
