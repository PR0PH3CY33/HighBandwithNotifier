// Written by Antoine Zayyat 14-08-2022 Licensed under the GNU General Public License

#include <arpa/inet.h>

#include <linux/if_packet.h>

#include <linux/ip.h>

#include <linux/udp.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <sys/ioctl.h>

#include <sys/socket.h>

#include <net/if.h>

#include <netinet/ether.h>

#include <unistd.h>

#include <pthread.h>

#include <ctype.h>

#define ETHER_TYPE 0x0800

int nob;

void *getTimelyConsumption()
{

	while (1)
	{

		long int conversion = nob / 1000000;

		if (conversion >= 20)
		{

			// add something for the program to do when it reaches 20 Megabytes per second.
		}

		printf("%lu Megabytes/second\n", conversion);

		nob = 0;

		sleep(1);
	}
}

int main(int argc, char *argv[])
{

	int rawSocket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	(rawSocket < 0) ? (perror("socket creation"), exit(0)) : 1;

	char buffer[65535];

	pthread_t thread;

	pthread_create(&thread, 0, getTimelyConsumption, 0);

	while (1)
	{

		int data_size = recvfrom(rawSocket, buffer, 65536, 0, NULL, NULL);

		nob = nob + data_size;
	}
}
