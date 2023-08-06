#include <stdio.h>

struct node{
    // ensure values are non-negative integers
    unsigned dist[20];
    unsigned from[20];
}rt[20];

int main()
{
    int costmat[20][20],newmat[20][20];
    int i,j,k,nodes,count=0;

    printf("enter number of nodes : ");
    scanf("%d",&nodes);

    // read cost-matrix and initialise rt
    printf("enter the cost matrix : \n");
    for (i=0;i<nodes;i++){
        printf("for node %d : ",i+1);
        for(j=0;j<nodes;j++){
            scanf("%d",&costmat[i][j]);
            // initialise diagonals to 0
            costmat[i][i]=0;
            newmat[i][i]=0;
            rt[i].dist[j]=costmat[i][j];
            rt[i].from[j]=j;
        }
    }

    // update rt using bellman-ford eqn
    do{
        count = 0;
        for (i=0;i<nodes;i++){
            for(j=0;j<nodes;j++){
               for(k=0;k<nodes;k++){
                    if(rt[i].dist[j] > (costmat[i][k] + rt[k].dist[j])){
                        rt[i].dist[j] = rt[i].dist[k]+rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                } 
            }
        }
    }while (count!=0);

    // display the updated routing table values
    for (i=0;i<nodes;i++){
        printf("\nfor router %d",i+1);
        printf("\ndestination\tnext hop\tdistance\n",i);
        for(j=0;j<nodes;j++){
            newmat[i][j] = rt[i].dist[j];
            if (i!=j) {
                printf("%d\t\t%d\t\t%d\n",j+1,rt[i].from[j]+1,rt[i].dist[j]);
            }
        }
    }

    // updated cost matrix
    printf("\nThe updated cost matrix is:\n");
    for (i=0;i<nodes;i++){
        for(j=0;j<nodes;j++){
            printf("%d\t",newmat[i][j]);
        }printf("\n");
    }

    return 0;
}