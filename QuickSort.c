#include <stdio.h>
#include <stdlib.h>
int partition(int *array,int head,int last);
int findQuick(int *array,int head,int last,int val);
int steps;
int main(int argc, char** argv) {
    int array[] = {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1}; //{16,1,10,3,4,6,5,12,2,14,11,8,7,13,9,15};
    int i;//index değişkeni
    int n = 16;//dizi boyutunun saklanacağı değişken
    int searchValue;//aranacak değerin saklanacağı değişken
    steps=0;
    printf("Kaçıncı büyük arıyorsunuz? :\n");
    scanf("%d",&searchValue);
    findQuick(array,0,n-1,searchValue-1);//Bu fonksiyon aranılan indexe gelmesi gereken
    for(i=0;i<n;i++){// değeri bulur, ancak herhangi birşey geri döndürmez.
        printf("%d  ",array[i]);
    }
    return 0;
}
int findQuick(int *array,int head,int last,int val){
    /*dizinin kendisi, arama yapılacak kısmın baş ve son noktaları
     ve aranacak değer parametre olarak alınır.*/
    if(last<head){//eğer son nokta baştan büyükse bütün elemanlar kontrol edilmiş
        // ancak sonuç bulunamamış demektir.
        printf("sayı bulunamadı\n");
        return -1;
    }

    int pivot = partition(array,head,last);//partitionun dönüş değeri olarak dönderdiği indis
    //o elemanın bulunması gereken yerdir.
    steps++;
    if(pivot == val){//eğer bu eleman aradığımız yerde ise bulunmuştur.
        printf("%d. büyük sayı %d dir. %d adımda bulundu.\n",val+1,array[pivot],steps);
    }
    else if(pivot>val){//aranılan yerden büyükse daha küçüklere bakmalıyız
        findQuick(array,head,pivot-1,val);
    }
    else if (pivot<val){//aksi taktirde daha büyükler
        findQuick(array,pivot+1,last,val);
    }
    return 0;

}
int partition(int *array,int head,int last){
    int pivot=head;
    int i=head,j=last,temp;
    while(i<j){
        while(array[i]<array[pivot]&&i<j){
            i++;
        }
        while(array[j]>array[pivot]){
            j--;
        }
        temp=array[i];
        array[i]=array[j];
        array[j]=temp;
    }
    temp=array[i];
    array[i]=array[j];
    array[j]=temp;
    temp=array[pivot];
    array[pivot]=array[j];
    array[j]=temp;
    return j;
}
