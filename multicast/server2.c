#define LOG_TAG "DataProvider"

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
#define FR_C_LDR_LH 0
#define FR_C_LDR_RH 1

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define DATA_PACKET_SIZE 1304
#define DATA_PACKET_COUNT_PER_FRAME 144
#define MAX_DATA_FRAME_SIZE (DATA_PACKET_SIZE * DATA_PACKET_COUNT_PER_FRAME)

#define DIAG_PACKET_SIZE 1440
#define DIAG_PACKET_COUNT_PER_FRAME 55
#define MAX_DIAG_FRAME_SIZE (DIAG_PACKET_SIZE * DIAG_PACKET_COUNT_PER_FRAME)



static uint8_t lidarDataL[MAX_DATA_FRAME_SIZE];
static uint8_t lidarDataR[MAX_DATA_FRAME_SIZE];
static uint8_t lidarDiagL[MAX_DIAG_FRAME_SIZE];
static uint8_t lidarDiagR[MAX_DIAG_FRAME_SIZE];

#define _LIDAR_DATA_PORT_L 2368
#define _LIDAR_DATA_PORT_R (_LIDAR_DATA_PORT_L + 1)
#define _LIDAR_DIAG_PORT_L 8308
#define _LIDAR_DIAG_PORT_R (_LIDAR_DIAG_PORT_L + 1)
static uint32_t ports[] = {_LIDAR_DATA_PORT_L, _LIDAR_DATA_PORT_R, _LIDAR_DIAG_PORT_L, _LIDAR_DIAG_PORT_R};

#define IDX_DATA_L 0
#define IDX_DATA_R 1
#define IDX_DIAG_L 2
#define IDX_DIAG_R 3

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static unsigned int total[4] = {0};

static void data_thread_create(void* (*func)(void*)) {
    pthread_t pt;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 2 * 1024 * 1024); /* 2MB */
    pthread_create(&pt, &attr, func, NULL);
    pthread_attr_destroy(&attr);
}

static unsigned int store_data(const int fd, uint8_t *buf, const int size, const int remaining) {
    uint8_t tmp[size];
    int nread = recvfrom(fd, tmp, size, 0, NULL, NULL);
    if (nread == -1) {
        perror("recv error\n");
        return 0;
    }
    if (nread > remaining) {
        printf("%s, drop received packet: not enough buff (remaining:%d vs read size:%d)\n",
               __func__, remaining, nread);
        return 0;
    }
    printf("%s, received packet: read size=%d\n", __func__, nread);
    memcpy(buf, tmp, nread);
    return nread;
}


_Noreturn void*
data_provider_thread_internal(void* arg) {
    printf("%s, thread started\n", __func__);
    int32_t sock[4];
    struct sockaddr_in addr[4];
    int highestFd = 0;
    memset(&addr, 0, sizeof(addr));
    for (int i=0; i<4; i++) {
        addr[i].sin_addr.s_addr = INADDR_ANY;
        addr[i].sin_family = AF_INET;
        addr[i].sin_port = htons(ports[i]);
        sock[i] = socket(PF_INET, SOCK_DGRAM, 0);
        if (bind(sock[i], (struct sockaddr *) &addr[i], sizeof(addr)) == -1) {
            printf("port:%d ",  ports[i]);
            perror("bind error\n");
        }
        printf("%s, %d: fd:%d, port=%d\n", __func__ , i, sock[i], ports[i]);
        highestFd = highestFd < sock[i] ? sock[i] : highestFd;
    }

    fd_set rfds;
    while (1) {
        FD_ZERO(&rfds);
        for(int i=0; i<4; i++) FD_SET(sock[i], &rfds);
        select(highestFd+1, &rfds, NULL, NULL, NULL);
        pthread_mutex_lock(&lock);
        if (FD_ISSET(sock[IDX_DATA_L], &rfds)) {
            total[IDX_DATA_L] += store_data(sock[IDX_DATA_L], lidarDataL + total[IDX_DATA_L],
                                            DATA_PACKET_SIZE, MAX_DATA_FRAME_SIZE - total[IDX_DATA_L]);
        }
        if (FD_ISSET(sock[IDX_DATA_R], &rfds)) {
            total[IDX_DATA_R] += store_data(sock[IDX_DATA_R], lidarDataR + total[IDX_DATA_R],
                                            DATA_PACKET_SIZE, MAX_DATA_FRAME_SIZE - total[IDX_DATA_R]);
        }
        if (FD_ISSET(sock[IDX_DIAG_L], &rfds)) {
            total[IDX_DIAG_L] += store_data(sock[IDX_DIAG_L], lidarDiagL + total[IDX_DIAG_L],
                                            DIAG_PACKET_SIZE, MAX_DIAG_FRAME_SIZE - total[IDX_DIAG_L]);
        }
        if (FD_ISSET(sock[IDX_DIAG_R], &rfds)) {
            total[IDX_DIAG_R] += store_data(sock[IDX_DIAG_R], lidarDiagR + total[IDX_DIAG_R],
                                            DIAG_PACKET_SIZE, MAX_DIAG_FRAME_SIZE - total[IDX_DIAG_R]);
        }
        pthread_mutex_unlock(&lock);
    }
}

void
init_data_provider_thread(void) {
    data_thread_create(data_provider_thread_internal);
}

void
data_provider_get_lidar_data(int lidarIndex, uint8_t *lidarData) {
    unsigned int copied;
    pthread_mutex_lock(&lock);
    memset(lidarData, 0, MAX_DATA_FRAME_SIZE * sizeof(lidarData[0]));
    if (lidarIndex == FR_C_LDR_LH) {
        copied = total[IDX_DATA_L] * sizeof(lidarDataL[0]);
        memcpy(lidarData, &lidarDataL, copied);
        total[IDX_DATA_L] = 0;
    } else if (lidarIndex == FR_C_LDR_RH) {
        copied = total[IDX_DATA_R] * sizeof(lidarDataR[0]);
        memcpy(lidarData, &lidarDataR, copied);
        total[IDX_DATA_R] = 0;
    }
    pthread_mutex_unlock(&lock);
    printf("%s, lidarIndex(%u) %d bytes copied.\n",
           __func__, lidarIndex, copied);
}

void
data_provider_get_lidar_diag(int lidarIndex, uint8_t *lidarData) {
    unsigned int size;
    pthread_mutex_lock(&lock);
    memset(lidarData, 0, MAX_DIAG_FRAME_SIZE * sizeof(lidarData[0]));
    if (lidarIndex == FR_C_LDR_LH) {
        size = total[IDX_DIAG_L] * sizeof(lidarDiagL[0]);
        memcpy(lidarData, &lidarDiagL, size);
        total[IDX_DIAG_L] = 0;
    } else if (lidarIndex == FR_C_LDR_RH) {
        size = total[IDX_DIAG_R] * sizeof(lidarDiagR[0]);
        memcpy(lidarData, &lidarDiagR, total[IDX_DIAG_R] * sizeof(uint8_t));
        total[IDX_DATA_R] = 0;
    }
    pthread_mutex_unlock(&lock);
    printf("%s, lidarIndex(%u) %d bytes copied.\n",
           __func__, lidarIndex, size);
}



int main(int argc, char** argv) {
    data_provider_thread_internal(NULL);
}
