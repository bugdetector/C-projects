//Sıralı olduğu bilinen ama kaydırılmış bir dizide istenen elemanı bulmak
#include <stdio.h>
#include <stdlib.h>
void search(int *array,int size,int val);
int main(int argc, char** argv) {
    int n = 1024;//dizi boyutunu saklayacak değişken
    int array[n]; //Dizi  {11  10 11 1 2 3 4 5 6 7 8 9 };
    int i;//index değişkeni
    int rotateCount = 30;
    int reverseIndex = 0;
    int searchValue;
    for (i = 0; i <= n - 1; i++) {
        if (i <= (n - rotateCount - 1)){
            array[i + rotateCount] = i;
        }
        else {
            array[reverseIndex] = i;
            reverseIndex++;}
    }
    printf("Aranacak değeri giriniz:\n");
    scanf("%d",&searchValue);
    search(array,n,searchValue);//search fonksiyonundan dönen değer ekrana yazdırılıyor
    return (EXIT_SUCCESS);
}
void search(int *array,int size ,int val){
    //dizinin kendisi, boyutu ve aranan değer parametre olarak alınır
int head = 0;//başlangıç noktası dizinin başı kabul edilir.
int last = size-1;//bitiş noktası dizinin sonu kabul edilir.
int found=1;//aranan değerin bulunup bulunmadığını kontrol için kullanılacak
int middle;//baş ve son arasındaki orta noktayı tespit için kullanılacak
int steps = 0;
while (head <= last && found)
/*head>last ise bütün değerlere bakılmış demektir.
 ve eğer aranılan değer bulunmuşsa daha fazla işlem yapmama gerek yok*/
{
  steps++;
  middle = (head + last)/2;//orta nokta bilirlenir
  if (array[middle] == val)//değer bulundumu
  {
    found=0;//eğer bulunduysa while'den çıkmak için found=0 yap
  }
  else if(array[middle]<val){//eğer aranılan değerden daha küçük bir değere bakıyorsam-->
      if(array[head]<array[middle] || val<=array[last]){
          /*aradığım değer son elemandan küçükse veya baktığım değer baş değerden büyükse
           bu durumda daha sağa gitmek için head=middle yaparım*/
      if((last-head)==1){
              middle++;
      }
           head = middle;
      }else if(array[head]>array[middle]){
          /*eğer yukarıdaki değilse ve baktığım değer baş değerden küçükse bu durumda daha sola gitmem gerekir.*/
          last = middle;
      }
  }
  else if (array[middle]>val){//eğer aranılan değerden daha büyük bir değere bakıyorsam-->
      if(val<=array[last] && array[middle]>array[last]){
          /*aradığım değer ve baktığım değer son değerden küçükse
           daha sağa gitmeliyim*/
           head = middle;
      }else{//aksii takdirde daha sola
          last = middle;
      }
  }
}
printf("%d sayısı %d. indisde %d adımda bulundu.\n",val,middle,steps);
return;

}
