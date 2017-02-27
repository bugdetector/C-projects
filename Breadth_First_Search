#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node{
    struct list *pointsto;//işaret edilen yer
    struct node *next;//bir sonraki
};
struct list{
    char *name;//film ya da artist ismini gösterir.
    struct node *head;//linkli listenin başını işaret eder.
    struct node *temp;//Liste filmler için artistleri, artistler için filmleri işaret eder.
    struct list *parent;//geri dönüş yapmak için tutulan gelinen yer işareti
    short isFilm;//1-> film , 0->oyuncu
    int visited;//ziyaret edilip edilmediği bilgisi
};
void newHash(struct node *hash,int size);//yeni bir hash dizisine başlangıç olarak NULL yükler.
void addToHash(struct node *hash,int hashSize,struct list *nod);//belirtilen hash dizisine belirtilen elemanı ekler.
struct list *getHash(struct node *hash,int hashSize,char *name);//Hash dizisinden belirtilen elemanı döndürür.
int getHornersHash(int hashSize,char *strin);//belirtilen katarın hash dizisindeki indexini bulur.
void BreadthFirstSearch(struct list *startNode,char *who,int visitCount);//enine arama yapar
int findBacon(struct list *cell);//verilen liste elemanının parent bilgisini kullanarak bacon sayısı hesaplar
int main(int argc, char** argv) {
    FILE *fp = fopen("cast.rated.txt","r");
    struct list *movietemp; //Film ögesi oluşturmak için gezici değer. Kök değerler yok, çünkü ihtiyaç yok.
    struct list *controller;//Oyuncu ögesi kontrolü için gezici değer
    struct list *startNode;//Enine arama işlemi yaparken kullanılacak başlangıç düğümü
    int hashSize = 100000;//hash dizisinin boyutunu belirleyen değişken
    struct node hash[hashSize];//hash dizisi
    char *buffer;//Dosyadan okunan satırın tutulduğu değişken
    char *delim;// '/' işareti ile bölümlenmiş alanların tutulduğu değişken
    char who[100];//Kullanıcıdan alınan kişi isimlerinin tutulduğu değişken
    printf("Program yükleniyor...\n");
    newHash(hash,hashSize);//Hash tablosunun değerleri NULL olarak atanıyor.
    while(!feof(fp)){
        fscanf(fp,"%m[^\n]\n",&buffer);//satır okunuyor
        delim = strtok(buffer,"/");//satır ilk defa bölümleniyor
        movietemp = malloc(sizeof(struct list));//yeni bir film oluştutuluyor
        movietemp->name = delim;//isim ataması
        movietemp->head = malloc(sizeof(struct node));//bulunan oyuncuların listesi oluşturuluyor
        movietemp->temp = movietemp->head;
        movietemp->visited = 0;//henüz ziyaret edilmedi
        movietemp->isFilm = 1;//bu filmdir.
        movietemp->parent = NULL;
        delim = strtok(NULL,"/");//satır bitene kadar sürekli bölümleniyor
        while(delim){
            controller = getHash(hash,hashSize,delim);//bu ismin daha önce eklenip eklenmediği kontrol ediliyor
            if(controller == NULL){//eğer eklenmemişse
                controller =  malloc(sizeof(struct list));//yeni bir oyuncu oluşturuluyor
                controller->visited = 0;
                controller->head = malloc(sizeof(struct node));
                controller->temp = controller->head;//bulunduğu filmler listesi oluşturuluyor
                controller->name = delim;//isim ataması
                controller->isFilm = 0; //bu oyuncudur.
                controller->parent=NULL;
                addToHash(hash,hashSize,controller);//hash tablosuna bu oyuncu ekleniyor
            }
            controller->temp->pointsto = movietemp;//film ilişkilendiriliyor
            controller->temp->next = malloc(sizeof(struct node));
            controller->temp = controller->temp->next;//yeni bir bulunduğu film oluşturuluyor
            controller->temp->next = NULL;
            movietemp->temp->pointsto = controller;//film ile oyuncu ilişkilendiriliyor
            movietemp->temp->next = malloc(sizeof(struct node));
            movietemp->temp = movietemp->temp->next;//yeni bir bulunan oyuncu oluşturuluyor
            movietemp->temp->next = NULL;
            delim = strtok(NULL,"/");
        }
    }
    system("clear");
    short exit = 1;//kullanıcının çıkmak isteyip istemediğini tutan değişken.
    int visitCount=0;//sürekli tekrarlananan aramalarda ziyaret sayısının değişken olmasını sağlar.
    startNode = getHash(hash,hashSize,"Bacon, Kevin");
    while(exit){
        printf("Kimi arıyorsunuz?\n");
        gets(who);
        if(!strcmp(who,"çıkış"))
            exit = 0;
        else if(!strcmp(who,startNode->name)){
            printf("BKevın Bacon'ın, Kevin Bacon sayısı 0'dır.\n");
        }
        else{
            visitCount++;//ziyaret edilme sayısı sürekli artar.
            BreadthFirstSearch(startNode,who,visitCount);//enine arama yapılıyor
        }
    }
    fclose(fp);
    return (EXIT_SUCCESS);
}
void BreadthFirstSearch(struct list *startNode,char *who,int visitCount){
    struct list *result;//sonuç değişkeni
    struct list *parent;//üst değişken
    struct node *mover;//gezici değişken
    int queueSize = 300000;//kuyruk boyutu
    int go=1;//while döngüsünde devam için doğruluk kontrolünde kullanılacak
    int bacon;//kevin bacon sayısının hesaplanıp tutlduğu değişken
    struct list *queue[queueSize];//kuyruk
    int head=0,last=0;// kuyruğun başı ve sonu
    mover = startNode->head;//bulunduğu film dizisi(node)
    parent = startNode;//üst katman başlangıçta startNode olarak seçilir
    parent->parent = NULL;//bu en üst katmandır ve bir üstü daha yoktur
    parent->visited = visitCount;//bu yere şimdi uğranıldı
    mover->pointsto->parent = parent;//bu filme bu oyuncudan gelindi
    while(go==1){
        while(mover->next!=NULL && go==1){
            if(mover->pointsto->visited<visitCount){
                mover->pointsto->parent = parent;//üst katman işaretleniyor
                if(!mover->pointsto->isFilm){
                    bacon = findBacon(mover->pointsto);//bacon sayısı bulunuyor
                    if(bacon>3){//bacon 6 dan büyükse bu kişinin ilişkisi yoktur.
                        go = -1;
                    }else if(!strcmp(mover->pointsto->name,who)){
                        go = 0;//kişi bulundu
                        result = mover->pointsto;
                    }
                }
                mover->pointsto->visited = visitCount;//bu yer ziyaret edildi
                queue[last]=mover->pointsto;//kuyruğa ekleniyor
                last = (last+1)%(queueSize);
            }
            mover = mover->next;//ağacın bir sonraki dalına bakılıyor.
        }
        if(head!=last){//'kuyruk boş mu?' kontrolü
            parent = queue[head];//kuyruktan çekiliyor
            mover = parent->head;//bu film ya da oyuncunun bir üst mertebesi
            head = (head+1)%(queueSize);
        }
        else go = -1;
    }
    if(go==0){
        printf("\n%s, Kevin Bacon sayısı: %d\n",who,bacon);
        while(result->parent!=NULL){
            printf("%s - %s '%s' \n",result->name,result->parent->parent->name,result->parent->name);
            result = result->parent->parent;
        }
    }else if(go == -1){
        printf("\nBu kişinin Kevin Bacon sayısı 6 dan büyüktür ya da böyle biri yok.\n%s\n\n",who);
    }
    printf("\n\n");
    return;
}
int findBacon(struct list *cell){
    struct list *temp = cell;
    int bacon = 0;
    while(temp->parent!=NULL){
        bacon++;
        temp = temp->parent;
    }
    return bacon/2;
}
void newHash(struct node *hash,int size){
    int i;
    for(i=0;i<size;i++){
        hash[i].pointsto=NULL;//başlangıç olarak tüm değerler NULL atanır.
        hash[i].next = NULL;
    }
    return;
}
void addToHash(struct node *hash,int hashSize,struct list *nod){
    int index = getHornersHash(hashSize,nod->name);
    struct node *temp = &hash[index];
    while(temp->next!=NULL){//boş yer görene kadar ilerlenir
        temp = temp->next;
    }
    temp->pointsto = nod;//boş bulunan yere eklenir.
    temp->next = malloc(sizeof(struct node));
    temp->next->pointsto = NULL;
    temp->next->next = NULL;
    return;
}
struct list *getHash(struct node *hash,int hashSize,char *name){
    int index = getHornersHash(hashSize,name);
    struct node *temp = &hash[index];
    while(temp->pointsto!=NULL){//herhangi bir boş yer görene kadar ilerleniyor
        if(!strcmp(name,temp->pointsto->name))
            return temp->pointsto;//isim uyuşuyosa aranan dönderilir.
        else
            temp = temp->next;
    }
    return NULL;//boş yer görülmüşse aranan yoktur.
}
int getHornersHash(int hashSize,char *strin){
    int stringLenght = (int)strlen(strin);//gönderilen karakter dizisinin uzunluğu hesaplanıyor
    int i;//index değişkeni
    int hash=0;//hesaplanacak olan hash değişkeni
    for(i=0;i<stringLenght;i++){
        hash+= 31*hash + strin[i];// hash hesaplanıyor
    }
    return abs(hash%hashSize);//negatif sonuç olma ihtimaline karşı mutlak değeri dönderiliyor
}
