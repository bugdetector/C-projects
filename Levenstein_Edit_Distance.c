#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{//this struct is designed for keep direction information(0:false,1:true)
    int top;//coming from top
    int left;//coming from left
    int topleft;//coming from topleft
}direction;
typedef struct{ //this struct is designed for distance matrix
    int data;
    direction where;//coming from where
}cell;
typedef struct{//this struct is designed for keep direction in numbers
    int direction;//1:topleft,2:top,3:left
}Path;
typedef struct{//this struct is designed for using in aligning functions
    char first;
    char second;
    int penalty;
}Aligned;
cell distTable[1000][1000];//globally defined distance matrix
Path path[1000];//globally defined path array for keep path information
Path bestPath[1000];//using for keep best path
Aligned aligned[1000];//it will using for writing aligned strings
int pathCount;//it counts path number
int bestPenalty;//it is best penalty point in many paths
int replaceP,insertP,deleteP;
int findDist(char *str1, char *str2, int column, int row);//Edit distance function
int align(int column,int row, Path *direc,char *str1,char *str2);//aligning function
int findPath(int column,int row,int i,int j,int cnt,char *str1,char *str2);//finds paths to [0,0]
int max(int x, int y);//returns bigger one's value
int min(int x, int y,int z);//returns smallest ones value
int main(int argc, char **argv)//takes two strings as terminal parameter and calculates Levenstein edit distance
{
    pathCount=0;
    // your code goes here
    char *str1 = argv[1];//control string 1 and 2
    char *str2 = argv[2];
    int i,j;//index variables
    int column =strlen(str1)+1;
    int row =strlen(str2)+1;
    replaceP=1;//replacion penalty point
    insertP=2;//insertion penalty point
    deleteP=2;//deletion penalty point
    for(i=0;i<row;i++){
        bestPath[i].direction=0;//As default assingnin 0 value for 
        path[i].direction=0;    //avoid computotion errors
    }
    findDist(str1, str2,column , row); 
    bestPenalty = max(column,row);//chosing max value 
    findPath(column,row,column-1,row-1,0,str1,str2);  //finding paths..
    printf("\nPath count: %d \n", pathCount);
    printf("\nTotal Penalty:  %d\n",bestPenalty);
    printf("Path:\t\t");
     for(j=0;j<column;j++){
            printf("%d\t", bestPath[j].direction);
        }
     i=0;
     printf("\n");
    align(column,row,bestPath,str1,str2);//and alingning the best one
    return 0;
}
int findPath(int column,int row,int i,int j,int cnt,char *str1,char *str2){
    //assigning max values for avoid computation errors
    int penaltyPoint=max(column,row);
    printf("%d  %d  ",i,j);
    int a;//index variable
    if(i==0 && j==0){//if i and j equals to 0 this is our target we must stop
        pathCount++;
        printf("Path:\t\t");
        for(a=0;a<=cnt;a++){
            printf("%d\t", path[a].direction);//printing directions to coming there
        }
        printf("\n");
        penaltyPoint = align(column,row,path,str1,str2);
        if(penaltyPoint<bestPenalty){//if it is better than bestPath so 
            bestPenalty = penaltyPoint;//it is bestPath
            for(a=0;a<=row;a++){
                bestPath[a].direction = path[a].direction;    
            }
        }                      
        return penaltyPoint;
    }// direction: 1 means topleft, 2 means top, 3 means left
    if(distTable[i][j].where.topleft){
        path[cnt].direction = 1;        
        findPath(column,row,i-1,j-1,(cnt+1),str1,str2);//going top-left
    }
    if(distTable[i][j].where.top){
        path[cnt].direction = 2;
        findPath(column,row,i-1,j,(cnt+1),str1,str2);//going top
       
    }
    if(distTable[i][j].where.left){
        path[cnt].direction = 3;
        findPath(column,row,i,j-1,(cnt+1),str1,str2);//going left 
    } 
    return penaltyPoint;
}
int align(int column,int row, Path *direc,char *str1,char *str2){
     int a=column-1,b=row-1,i=0;
     int totalPenalty=0;
     while(direc[i].direction>0){         
         switch(direc[i].direction){
             case 1://going top-left and writing one char from two of strings
                 aligned[i].first=str1[a-1];
                 aligned[i].second=str2[b-1];//penalty can be 0 and one. calculating..
                 aligned[i].penalty = distTable[a][b].data==distTable[a-1][b-1].data ? 0:replaceP;
                 a--;
                 b--;
                 break;
             case 2://going top and only writing one char form first string
                 aligned[i].first=str1[a-1];//for second '-'
                 aligned[i].second='-';
                 aligned[i].penalty = insertP;//penalty is 2
                 a--;
                 break;
             case 3://going left and only writing one char form seconf string
                 aligned[i].first='-';//for first '-'
                 aligned[i].second=str2[b-1];
                 aligned[i].penalty = deleteP;//penalty is 2
                 b--;
                 break;
         }
         i++;
     }
     printf("Aligned1:\t");             //Writing operations
     for(a=i-1;a>=0;a--){
         printf("%c\t",aligned[a].first);
     }
     printf("\nAligned2:\t");
     for(a=i-1;a>=0;a--){
         printf("%c\t",aligned[a].second);
     }
     printf("\nPenalty:\t");
     for(a=i-1;a>=0;a--){
         printf("%d\t",aligned[a].penalty);
         totalPenalty+=aligned[a].penalty;//calculating total penalty 
     }
     printf("-> %d",totalPenalty);
     printf("\n\n");
     return totalPenalty;
}
int findDist(char *str1, char *str2, int column, int row)
{
    int i,j;//index variables
    for (i=0; i<=column; i++)
    {                           //theese two for loops are doing that 
        for (j=0; j<=row; j++)    //configures distance matrix as default
        {
            if (i==0){
                distTable[i][j].data = j*insertP;
                distTable[i][j].where.left = 1;
                distTable[i][j].where.top = 0;
            }
            else if (j==0){
                distTable[i][j].data = i*deleteP;
                distTable[i][j].where.left = 0;
                distTable[i][j].where.top = 1;
            }
            else{
                distTable[i][j].data = 0;                
                distTable[i][j].where.left = 0;
                distTable[i][j].where.top = 0;
            }            
            distTable[i][j].where.topleft = 0;            
        }
    }
    for (i=1; i<=column; i++)
    {                                   //theese two for loops are doing
        for (j=1; j<=row; j++)            //distance matrix as representing 
        {                               //values and directions
            int replace = str1[i-1] == str2[j-1] ? distTable[i-1][j-1].data:distTable[i-1][j-1].data + replaceP;
            int insert = distTable[i-1][j].data + insertP;//finding insertion, removing and
            int remove = distTable[i][j-1].data + deleteP;//replacing cost
            
            int k = min(insert,remove,replace);     //and choosing minimum one
            switch(k){
                case(1):
                    distTable[i][j].data = insert;
                    distTable[i][j].where.top = 1;      //if we are inserting
                    if(insert==remove){                 //controling that is there 
                        distTable[i][j].where.left = 1; //any equivalent operation
                    }
                    if(insert==replace){
                        distTable[i][j].where.topleft = 1;
                }
                break;
                case(2):
                    distTable[i][j].data = remove;
                    distTable[i][j].where.left = 1;     //and so removing and replacing...
                    if(remove==insert){
                        distTable[i][j].where.top = 1;
                    }
                    if(remove==replace){
                        distTable[i][j].where.topleft = 1;
                    }
                    break;
                case(3):
                    distTable[i][j].data = replace;
                    distTable[i][j].where.topleft = 1;
                    if(replace==remove){
                        distTable[i][j].where.left = 1;
                    }
                    if(replace==insert){
                        distTable[i][j].where.top = 1;
                    }
                    break;                   
            }                
        }
    }
    return (distTable[column][row].data);
}
int min(int x, int y, int z){
    if(x<=y && x<=z)
        return 1;
    else if(y<=x && y<=z)
        return 2;
    else
        return 3;
}
int max(int x, int y){
    if(x>y){
        return x;
    }
    else
        return y;
}
