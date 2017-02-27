//İşletim Sistemi: Linux x64
//Derleyici: gcc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void searchForValue(char **hash,int hashSize);//kelime girdisini alıp hash dizisinde arayan fonksiyon
void newArray(char **array,int size);//hash dizisinin değerlerinin başlangıç olarak NULL'a atar
void addToHash(char **hash,int hashSize,char *word);//hash dizisine verilen elemanı ekler
int getHash(char **hash,int hashSize,char *word);//verilen hash dizisinden verilen kelimenin adresini dönderir. Eğer yoksa -1.
int GetHashCode(char *strin);//verilen katar için hashcode dönderir.
int main(int argc, char** argv) {
    FILE *fp = fopen("smallDictionary.txt","r");//338 kelime var
    if(fp == NULL){
        printf("Dosya bulunamadı.\n");
        return -1;
    }
    int hashSize = 569;//yük çarpanı = 0.6
    char *hash[hashSize];//hash dizisi
    char *buffer;//okuma işlemlerinde geçici işaretçi değer
    int option=0;
    newArray(hash,hashSize);
    fscanf(fp,"%ms",&buffer);
    while(!feof(fp)){
        addToHash(hash,hashSize,buffer);
        fscanf(fp,"%ms",&buffer);                
    }
    printf("1- Kelime ara\n2- Hash yazdır\n3- Çıkış\n");
    while(option!=3){
        scanf("%d",&option);
        if(option == 1){
            searchForValue(hash,hashSize);
        }else if(option==2){
            printHash(hash,hashSize);
        }
        else if(option!=3){
            printf("Geçerli bir seçenek değil!\n");
        }
    }
    return (EXIT_SUCCESS);
}
void searchForValue(char **hash,int hashSize){
    char *recommendeds[10];
    char *input;
    char *temp;//harf değiştirmelerde kullanılan geçici değer
    int i,j;//indeks değişkenleri
    int len;//okunan kelimenin uzunluğunu tutacak olan değişken
    int wordCount=0;
    int index;
    printf("Bir kelime yazınız:\n");
    scanf("%ms",&input);//kullanıcıdan girdi alınıyor.
    index = getHash(hash,hashSize,input);//var olup olamdığı kontrol ediliyor.
    if(index == -1){
        printf("\nKelime yanlış yazılmıştır.\n");
        len = strlen(input);
        temp = malloc((len+1)*sizeof(char));
        for(i=0;i<len;i++){
            strcpy(temp,input);
            for(j=0;j<('z'-'a')+1;j++){
                temp[i] = 'a'+j;
                if(getHash(hash,hashSize,temp)!=-1){
                    recommendeds[wordCount] = malloc((len+1)*sizeof(char));
                    strcpy(recommendeds[wordCount],temp);
                    wordCount++;
                }
            }
        }
        free(temp);
        free(input);
        if(wordCount>0){
            printf("\nŞunları demek istemiş olabilir misiniz?\n");
            for(i=0;i<wordCount;i++){
                printf("%s\n",recommendeds[i]);
            }
        }
        printf("\n");
    }
    else{
        printf("\nKelime doğru yazılmıştır:\n%s\n",hash[index]);
    }
return;
}
void printHash(char **hash,int hashSize){
    int i;
    for(i=0;i<hashSize;i++){
        printf("%d -> %s\n",i,hash[i]);
    }
}
void newArray(char **array,int size){
    int i;
    for(i=0;i<size;i++){
        array[i]=NULL;//başlangıç olarak tüm değerler NULL atanır.
    }
    return;
}
void addToHash(char **hash,int hashSize,char *word){
    int hashCode = GetHashCode(word);
    int key=hashCode%hashSize;
    int i=1;
    while(hash[key]!=NULL){
         key = ((hashCode%hashSize) + i*(1+(hashCode%(hashSize-1))))%hashSize;
         i++;
    }
    hash[key] = word;//boş bulunan yere eklenir.
    return;
}
int getHash(char **hash,int hashSize,char *word){
    int hashCode = GetHashCode(word);
    int key = hashCode%hashSize;
    int i=1;
    while(hash[key]!=NULL){
        if(!strcmp(hash[key],word)){
            printf("\nDeğer bulundu: %s indis: %d, %d adımda bulundu.\n",word,key,i);
            return key;
        }        
        printf("\nBakılan indis: %d, İndisteki değer: %s\n",key,hash[key]);
        key = ((hashCode%hashSize) + i*(1+(hashCode%(hashSize-1))))%hashSize;
        i++;     //^h1                    ^h2        
    }
    printf("\nDeğer bulunamadı: %s, bakılan indis: %d, adım sayısı: %d\n",word,key,i);
    return -1;
}
int GetHashCode(char *strin){
    int stringLenght = strlen(strin);//gönderilen karakter dizisinin uzunluğu hesaplanıyor
    int i;//index değişkeni
    int key=0;//hesaplanacak olan hash değişkeni
    for(i=0;i<stringLenght;i++){
        key+= (strin[i]-'a')*26*(i);// hash hesaplanıyor
    }
    return abs(key);//negatif sonuç olma ihtimaline karşı mutlak değeri dönderiliyor
}
