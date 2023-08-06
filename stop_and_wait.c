#include <stdio.h>
#include <stdlib.h>

// data packet
struct frame{
    int info;
    int seq;
};

int i,ak,disconnect=0,t=5;
struct frame p;
int err_ack=1,err_frame=1; //no error
char turn = 's';

void sender();
void receiver();

void main()
{
    p.info=0,p.seq=0;

    while (!disconnect){
        sender();
        for (i=0;i<=10000000;i++);  // wait for finite time
        receiver();
    }
}

void sender()
{
    static int flag = 0;

    if (turn == 's'){

        // if ack has not arrived
        if (err_ack == 0){
            printf("sender: sent packet with seq. no. %d\n",p.seq);
            err_frame = rand()%4;
            if (err_frame == 0) {
                printf("error while sending packet.\n");
            }
            turn = 'r';
        }

        // if the ACK arrives successfully
        else{
            if (flag == 1) {
                printf("\nsender: received ack for packet %d\n",ak);
            }
            if (p.seq == 5) {
                disconnect = 1;
                return;
            }

            // send the next packet with an incremented sequence number
            p.info += 1;
            p.seq += 1;
            printf("sender: sent packet with seq. no. %d\n",p.seq);
            err_frame = rand()%4;
            if (err_frame == 0) {
                printf("error while sending packet.\n");
            }
            turn = 'r';
            flag = 1;
        }
    }

    else{
        t--;
        printf("sender time reducing!\n");
        if (t==0){
            turn = 's';
            err_ack=0;
            t=5;
        }
    }
}

void receiver()
{
    static int fr_exp = 1;

    if (turn == 'r') {
        if (err_frame != 0) {
            if (p.seq == fr_exp) {
                printf("\nreceiver: received packet with seq.no. %d\n",p.seq);
                ak = p.seq;
                
                fr_exp += 1;
                turn = 's';
                err_ack = rand()%4;
                if (err_ack == 0) {
                    printf("receiver: error while sending ack\n");
                }
            }
            else {
                printf("\nreceiver: received duplicate packet with seq.no. %d\n",fr_exp-1);
                ak = fr_exp-1;

                turn = 's';
                err_ack = rand()%4;
                if (err_ack == 0) {
                    printf("receiver: error while sending ack\n");
                }
            }
        }
    }
}