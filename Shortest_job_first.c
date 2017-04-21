#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char pname[5];//name
    int parrival;//arriving time
    int pburst;//burst time
    int remaining;//remaining time
    int finishtime;//finish time
}process;
int findMin(int *pArr,int procNum);
int main(int argc, char** argv) {
    int procCnt;//number of processes (user input)
    process *pArr;//process array (user input)
    process temp;// used for selection sort
    int totalBurst=0;//total burst time
    int i,j;//index variables
    printf("Enter total number of processes: ");
    scanf("%d",&procCnt);
    pArr = (process*)malloc(procCnt*sizeof(process));
    if(pArr == NULL){
        printf("There is not enough memory!");
        return -1;
    }
    for(i=0;i<procCnt;i++){
        printf("Enter p_name:");
        scanf("%s",pArr[i].pname);
        printf("Enter p_arrival:");
        scanf("%d",&pArr[i].parrival);
        printf("Enter p_burst:");
        scanf("%d",&pArr[i].pburst);
        pArr[i].remaining = pArr[i].pburst;//for beginning suppose that remaining
        totalBurst += pArr[i].pburst;       //time equals burst time
    }
    int minindex;
    for(i=0;i<procCnt-1;i++){//sorting by minimum arriving time by 
        minindex = i;       //selection sort
        for(j=i+1;j<procCnt;j++){
            if(pArr[j].parrival<pArr[minindex].parrival){
                minindex = j;
            }
        }
        temp = pArr[minindex];
        pArr[minindex] = pArr[i];
        pArr[i]=temp;
    }
    int burstCnt=0;//used for counting bursts against empty iterations
    int time;
    for(time=0;burstCnt<totalBurst;time++){//counting time
        minindex=0;
       for(j=0;(pArr[j].parrival<=time) && (j<procCnt);j++){
           if((pArr[j].remaining < pArr[minindex].remaining || pArr[minindex].remaining==0)
                   && pArr[j].remaining!=0){//finding minimum burst time
               minindex = j;//through the time
           }
       }
       if(pArr[minindex].parrival<=time && pArr[minindex].remaining!=0){
           pArr[minindex].remaining--;
           burstCnt++;
           if(pArr[minindex].remaining==0){//if remaining is 0 it means
              pArr[minindex].finishtime = time+1;//process finished
           }
       }       
    }
    int totalWaiting=0;
    int waitingTime;
    printf("Process name\tArrival time\tBurst Time\tWaiting Time\n");
     for(i=0;i<procCnt;i++){
         waitingTime = pArr[i].finishtime-pArr[i].parrival-pArr[i].pburst;
         totalWaiting+=waitingTime;//printing output and calculating waiting time
        printf("%s\t\t%d\t\t%d\t\t%d\n",pArr[i].pname,pArr[i].parrival,
                pArr[i].pburst,waitingTime);
    }
    printf("Total waiting time : %d\nAverage waitingtime: %f",
            totalWaiting,(float)totalWaiting/procCnt);
    for(i=0;i<procCnt;i++){
        
    }
    return (EXIT_SUCCESS);
}
