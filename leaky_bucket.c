#include <stdio.h>

int main()
{
    int incoming,outgoing,n,bucket_size,store=0;

    printf("enter bucket size, outgoing rate & umber of packets : ");
    scanf("%d %d %d",&bucket_size,&outgoing,&n);

    while (n!=0)
    {
        // store incoming
        printf("enter incoming packet size : ");
        scanf("%d",&incoming);

        if (incoming <= (bucket_size-store)){
            store += incoming;
            printf("bucket buffer size = %d out of %d\n",store,bucket_size);
        }
        else{
            printf("bucket overflow !!\ndropped %d out of %d packets (leaked)\n",incoming-(bucket_size-store),incoming);
            store = bucket_size;
            printf("bucket buffer size = %d out of %d\n",store,bucket_size);
        }

        // outgoing
        if (store <= outgoing){
            store = 0;
        }
        else{
            store -= outgoing;
        }
        printf("after outgoing, %d out of %d packets left in buffer\n",store,bucket_size);
        n--;
    }

    return 0;
}