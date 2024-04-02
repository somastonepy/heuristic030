#include <stdio.h>
#include <stdlib.h>

  int cheacked_d[20];
  int fields[20][400][2]; // Assuming maximum of 100 points per field
  int cheacked[20][20],oiled[20][20],d[200],zero_cnt[20][20];
  int sort[20];
    int has_oil[400][2]; // Assuming maximum of N*N squares with oil
    int count = 0;
    int resp,num=5,resp_cnt=0,cheacked_cnt=0,improve=0,n_cnt=0,M_cnt=0;
    //int cheack[num][2];

int reset(int N){
    count=0;
    for(int l=0;l<N;l++){
        for(int k=0;k<N;k++){
            if(cheacked[l][k]>0){
                has_oil[count][0]=l;
                has_oil[count][1]=k;
                count++;
            }
        }
    }
    printf("a %d", count);
    for (int l = 0; l < count; l++) {
        printf(" %d %d", has_oil[l][0], has_oil[l][1]);
    }
    printf("\n");
    fflush(stdout);
    scanf("%d", &resp);
    return resp;

}

void nanamin(int M,int N,int UN){
    int cnt=count+1;
   while(count != cnt){//7割以上同じ型はその方法も検討する
    cnt=count;
    for(int dc=0;dc<M;dc++){
        int xx=sort[dc];
        //if(cheacked_d[xx])continue;
        for(int l=0;l<N;l++){
            int imp=0;
            for(int k=0;k<N;k++){
                imp=2;
                int cn=0;
                for(int p=0;p<d[xx];p++){
                    int now_i=fields[xx][p][0]+l;
                    int now_j=fields[xx][p][1]+k;
                    if(cheacked[now_i][now_j]==0){
                        imp=2;
                        break;
                    }else if(now_i>=N||now_j>=N){
                        imp=0;
                        break;
                    }else if(cheacked[now_i][now_j]<0)imp=1;    
                    else cn++;
                }
                if(imp==0)break;
                else if(imp==2)continue;

                //printf("%d--%d \n",(cn*100)/d[xx],cn);
                if(0<cn && ((cn*100)/d[xx])>=75){
                // printf("q %d",d[xx]);
                // for(int p=0;p<d[xx];p++){
                //     printf(" %d %d",fields[xx][p][0]+l,fields[xx][p][1]+k);
                // }printf("\n");
                // fflush(stdout);
                // scanf("%d",&resp);
                    for(int p=0;p<d[xx];p++){
                      int now_i=fields[xx][p][0]+l;
                      int now_j=fields[xx][p][1]+k;
                      if(cheacked[now_i][now_j]<0){
                        printf("q 1 %d %d\n",now_i,now_j);
                        fflush(stdout);
                        scanf("%d",&resp);
                        cheacked[now_i][now_j]=resp;
                        if(resp != 0){
                            has_oil[count][0]=now_i;
                            has_oil[count][1]=now_j;
                            count++;
                            oiled[now_i][now_j]=1;
                        }else {
                            imp=0;
                            break;
                        }
                      }                        
                    }
                }
            }
        }
    }
   }
}

void kousi(int l_start,int l_kousa,int k_start,int k_kousa,int M,int N){
    int improve=1;
    for(int l=0;l<M;l++){
        if(cheacked_d[l] != 1)improve=0;
    }
    if(improve)return;

        //格子上にやる
        if(l_start != 2){
           for(int l=l_start;l<N;l+=l_kousa){
            for(int k=k_start;k<N;k+=k_kousa){
                if(cheacked[l][k]<0){
                    printf("q 1 %d %d\n",l,k);
                    fflush(stdout);
                    scanf("%d",&resp);
                    cheacked[l][k]=resp;
                }
            }
           }
        }

        //格子上にや
           for(int l=l_start;l<N;l+=l_kousa){
            if(l>=N)break;
            for(int k=k_start;k<N;k+=k_kousa){
                if(k>=N)break;
                if(cheacked[l][k]<0){
                    printf("q 1 %d %d\n",l,k);
                    fflush(stdout);
                    scanf("%d",&resp);
                    cheacked[l][k]=resp;
                }
                //printf("%d %d\n",l,k);
                if(cheacked[l][k] == 0 || oiled[l][k]==1){
                    continue;
                
                }else{
                    if(oiled[l][k]<0){
                        has_oil[count][0]=l;
                        has_oil[count][1]=k;
                        count++;
                        oiled[l][k]=1;
                    }
                    
                    int imp=0;
                    if(l_start != 2)imp=1;
                    if(imp)for(int p=0;p<M;p++)cheacked_d[p]=0;
                    for(int dc=0;dc<M;dc++){
                        int xx=sort[dc];
                        if(cheacked_d[xx]==1)continue;
                        for(int high=0;high<N;high++){
                            for(int wide=0;wide<N;wide++){
                                int good=0;
                            
                                for(int p=0;p<d[xx];p++){
                                  //型にその座標が含まれているか
                                  //printf("%d-%d  %d-%d\n",l,k,fields[xx][p][0],fields[xx][p][1]);
                                  if(fields[xx][p][0]+high == l && fields[xx][p][1]+wide == k)good=1;
                                  if(fields[xx][p][0]+high>=N||fields[xx][p][1]+wide>=N){
                                    improve=1;
                                    break;
                                  //型の中に既に０がないか調べる
                                  }else if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]==0){
                                    improve=1;
                                    break;

                                  //調べていないところがあるか
                                  }else if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                    improve=0;
                                  }
                                  
                                }
                                //printf("%d",good);
                                if(improve==1||good==0)continue;

                                //型に対してステップ２
                                int kk=0;
                                improve=0;
                                for(int p=0;p<d[xx];p++)
                                    if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]>=0){
                                        kk++; 
                                        if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]>0)
                                                if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                                    has_oil[count][0]=fields[xx][p][0]+high;
                                                    has_oil[count][1]=fields[xx][p][1]+wide;
                                                    count++;
                                                    oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                                }  
                                    }
                                    if(d[xx]-kk<1)continue;
                                    else if(d[xx]-kk<4){
                                        for(int p=0;p<d[xx];p++){
                                            if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]>0){
                                                if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                                    has_oil[count][0]=fields[xx][p][0]+high;
                                                    has_oil[count][1]=fields[xx][p][1]+wide;
                                                    count++;
                                                    oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                                }                                             
                                                continue;
                                            }else if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]==0)continue;
                                            printf("q 1 %d %d\n",fields[xx][p][0]+high,fields[xx][p][1]+wide);
                                            fflush(stdout);
                                            scanf("%d",&resp);
                                            cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]=resp;
                                            if(resp != 0){
                                                if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]>0)continue;//同じのは追加しない
                                                has_oil[count][0]=fields[xx][p][0]+high;
                                                has_oil[count][1]=fields[xx][p][1]+wide;
                                                count++;
                                                oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                            }else improve=1;
                                        }
                                        if(improve)continue;
                                        else{
                                            cheacked_d[xx]=1;
                                            improve=2;
                                            break;
                                        }
                                                                        
                                    }else{
                                        printf("q %d",d[xx]-kk);
                                        for(int p=0;p<d[xx];p++){
                                            if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]>0){
                                                if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                                    has_oil[count][0]=fields[xx][p][0]+high;
                                                    has_oil[count][1]=fields[xx][p][1]+wide;
                                                    count++;
                                                    oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                                }  
                                                continue;
                                            }else if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]==0)continue;
                                            printf(" %d %d",fields[xx][p][0]+high,fields[xx][p][1]+wide);                                   
                                        }
                                        printf("\n");
                                        fflush(stdout);
                                        scanf("%d",&resp);
                                    }
                                        //よい値なら調べる
                                        improve=1;
                                        if(d[xx]*0.6<=resp+kk){
                                            for(int p=0;p<d[xx];p++){
                                                int now_i=fields[xx][p][0]+high;
                                                int now_j=fields[xx][p][1]+wide;
                                                if(cheacked[now_i][now_j]>0){
                                                    if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                                      has_oil[count][0]=fields[xx][p][0]+high;
                                                      has_oil[count][1]=fields[xx][p][1]+wide;
                                                      count++;
                                                      oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                                    }                                             
                                                    continue;//二回以上調べない
                                                }else if(cheacked[now_i][now_j]==0){
                                                    improve=0;
                                                    break;
                                                }else{
                                                    printf("q 1 %d %d\n",now_i,now_j);
                                                    fflush(stdout);
                                                    scanf("%d",&resp);
                                                    cheacked[now_i][now_j]=resp;
                                                    if(resp==0){
                                                       improve=0;
                                                    }else{
                                                       if(oiled[now_i][now_j]>0)continue;//同じのは追加しない
                                                       has_oil[count][0]=now_i;
                                                       has_oil[count][1]=now_j;
                                                       count++;
                                                       oiled[now_i][now_j]=1;
                                                    }
                                                }
                                            }
                                        

                                         //すべてあっていれば次
                                         if(improve>0){
                                            for(int p=0;p<d[xx];p++){
                                                 int now_i=fields[xx][p][0]+high;
                                                 int now_j=fields[xx][p][1]+wide;
                                              if(oiled[now_i][now_j]<0){
                                                 has_oil[count][0]=now_i;
                                                 has_oil[count][1]=now_j;
                                                 count++;
                                                 oiled[now_i][now_j]=1;
                                                }  
                                            }
                                            cheacked_d[xx]=1;
                                            improve=2;
                                            break;
                                         }
                                        }else if(resp+kk<=d[xx]*0.3){
                                            improve=3;
                                            break;
                                
                                        //  //少ないrespが続くところは0と考える    
                                        // }else if(resp<=d[xx]*0.1){
                                        //     for(int p=0;p<d[xx];p++){
                                        //         if(oiled[fields[xx][p][0]][fields[xx][p][1]])continue;
                                        //         zero_cnt[fields[xx][p][0]][fields[xx][p][1]]++;
                                        //         if(zero_cnt[fields[xx][p][0]][fields[xx][p][1]]>3)cheacked[fields[xx][l][0]][fields[xx][l][1]]=0;
                                        //     }
                                        }
                                    
                            }
                            if(improve>=2)break;
                        }
                        if(improve==2)break;
                        nanamin(M,N,30);
                    }

                    //if(improve==2)break;
                    
                
                }
            }
           }

}



void kasa(int M,int N){

   //重なっているのを探す
   int imp=0;
    for(int dc=0;dc<M;dc++){
        int xx=sort[dc];
        if(cheacked_d[xx])continue;
        for(int l=0;l<N;l++){
            for(int k=0;k<N;k++){
                imp=1;
                for(int p=0;p<d[xx];p++){
                    int now_i=fields[xx][p][0]+l;
                    int now_j=fields[xx][p][1]+k;
                    if(cheacked[now_i][now_j]<=0){
                        imp=0;
                        break;
                    }
                }
                if(imp){
                    cheacked_d[xx]=1;
                    break;
                }
            }
            if(imp)break;
        }
    }

}

int main() {
    int N, M;
    float eps;
    scanf("%d %d %f", &N, &M, &eps);
    for(int p=0;p<M;p++)cheacked_d[p]=0;

    for(int i=0;i<N;i++)
     for(int j=0;j<N;j++){
       cheacked[i][j]=-1;
       oiled[i][j]=-1;
       zero_cnt[i][j]=0;
     }
    
    
    for (int i = 0; i < M; i++) {
        scanf("%d", &d[i]);
        
        for (int j = 0; j < d[i]; j++) {
            scanf("%d %d", &fields[i][j][0], &fields[i][j][1]);
        }
    }

    //小さい順にソート
  
    for(int i=0;i<M;i++)sort[i]=i;
    for(int i=0;i<M-1;i++){
        for(int j=0;j<M-i-1;j++){
            if(d[sort[j]]>d[sort[j+1]]){
                int tmp=sort[j];
                sort[j]=sort[j+1];
                sort[j+1]=tmp;

            }

        }
    }

//１回目

int tmp_count=0,UN=1;
    // kousi(1,8,1,8,M,N);
    // //kasa(M,N);
    // nanamin(M,N,30);

    kousi(1,4,1,4,M,N);
    //kasa(M,N);    
    nanamin(M,N,30);
 
    // kousi(3,8,3,8,M,N);
    // nanamin(M,N,30);
    // //kasa(M,N);

    kousi(3,4,3,4,M,N);
    nanamin(M,N,30);
    //kasa(M,N);



if(tmp_count<count){
    tmp_count=count;
      printf("a %d", count);
      for (int l = 0; l < count; l++) {
          printf(" %d %d", has_oil[l][0], has_oil[l][1]);
        }
      printf("\n");
      fflush(stdout);
      scanf("%d", &resp);
      if (resp == 1)return 0;
}
    
    for(int l=0;l<M;l++)
      cheacked_d[l]=-1;


    kousi(2,4,0,6,M,N);
    nanamin(M,N,30);

if(tmp_count<count){
    tmp_count=count;
      printf("a %d", count);
      for (int l = 0; l < count; l++) {
          printf(" %d %d", has_oil[l][0], has_oil[l][1]);
        }
      printf("\n");
      fflush(stdout);
      scanf("%d", &resp);
      if (resp == 1)return 0;
}
    for(int l=0;l<M;l++)
      cheacked_d[l]=-1;
    kousi(2,2,2,4,M,N);
    nanamin(M,N,40);

if(tmp_count<count){
    tmp_count=count;
      printf("a %d", count);
      for (int l = 0; l < count; l++) {
          printf(" %d %d", has_oil[l][0], has_oil[l][1]);
        }
      printf("\n");
      fflush(stdout);
      scanf("%d", &resp);
      if (resp == 1)return 0;
}
    // kasa(M,N);

//     kousi(2,2,2,2,M,N);
//     nanamin(M,N,0);
//     // kasa(M,N);

// if(tmp_count<count){
//     tmp_count=count;
//       printf("a %d", count);
//       for (int l = 0; l < count; l++) {
//           printf(" %d %d", has_oil[l][0], has_oil[l][1]);
//         }
//       printf("\n");
//       fflush(stdout);
//       scanf("%d", &resp);
//       if (resp == 1)return 0;
// }

    //大きい順にソート
    for(int i=0;i<M;i++)sort[i]=i;
    for(int i=0;i<M-1;i++){
        for(int j=0;j<M-i-1;j++){
            if(d[sort[j]]<d[sort[j+1]]){
                int tmp=sort[j];
                sort[j]=sort[j+1];
                sort[j+1]=tmp;

            }

        }
    }


    
    //どこから調べるか決める
    int Z[4];

    //左
    int kk=0;
    for(int l=0;l<N;l++)
        for(int k=0;k<N/2;k++)
            if(cheacked[l][k]>=0)kk++; 
    if(N*(N/2)-kk>0){   
    printf("q %d",N*(N/2)-kk);
    for(int l=0;l<N;l++){
        for(int k=0;k<N/2;k++){
            if(cheacked[l][k]>=0)continue;
            printf(" %d %d",l,k);
        }
    }
    printf("\n");
    fflush(stdout);
    scanf("%d",&Z[0]);
    }else {Z[0]=0;}

    //右

    kk=0;
    for(int l=0;l<N;l++)
        for(int k=N/2;k<N;k++)
          if(cheacked[l][k]>=0)kk++;
    if((N-N/2)*N-kk>0){
    printf("q %d",(N-N/2)*N-kk);
    for(int l=0;l<N;l++){
        for(int k=N/2;k<N;k++){
            if(cheacked[l][k]>=0)continue; 
            printf(" %d %d",l,k);
        }
    }
    printf("\n");
    fflush(stdout);
    scanf("%d",&Z[1]);
    }else {Z[1]=0;}



    //上

    kk=0;
    for(int l=0;l<N/2;l++)
        for(int k=0;k<N;k++)
          if(cheacked[l][k]>=0)kk++;
    if(N*(N/2)-kk>0){
    printf("q %d",N*(N/2)-kk);
    for(int l=0;l<N/2;l++){
        for(int k=0;k<N;k++){
            if(cheacked[l][k]>=0)continue;
            printf(" %d %d",l,k);
        }
    }
    printf("\n");
    fflush(stdout);
    scanf("%d",&Z[2]);
    }else {Z[2]=0;}

    //下

    kk=0;
    for(int l=N/2;l<N;l++)
        for(int k=0;k<N;k++)
          if(cheacked[l][k]>=0)kk++;
    if((N-N/2)*N-kk>0){
    printf("q %d",(N-N/2)*N-kk);
    for(int l=N/2;l<N;l++){
        for(int k=0;k<N;k++){
            if(cheacked[l][k]>=0)continue;
            printf(" %d %d",l,k);
        }
    }
    printf("\n");
    fflush(stdout);
    scanf("%d",&Z[3]);
    }else {Z[3]=0;}

    int High,Wide,l_kousa,k_kousa;
    if(Z[0]>Z[1]){
        Wide=-1;
        k_kousa=2;
    }else{
        Wide=N;
        k_kousa=-2;
    }
    if(Z[2]>Z[3]){
        High=-1;
        l_kousa=2;
    }else{
        High=N;
        l_kousa=-2;
    }



//２回目以降
    while(1){    
        n_cnt++;
        //型ごとに調べる。
        for(int dc=0;dc<M;dc++){//油田のループ
         int xx=sort[dc];
         if(cheacked_d[xx])continue;
            int high=High;
        
            while(1){//高さを変える
                int wide=Wide;
                if(High==N){
                    high--;
                    if(high<0)break;
                }else{
                    high++;
                    if(high>=N)break;
                }
                while(1){//横を変える
                    if(Wide==N){
                        wide--;
                        if(wide<0)break;
                    }else{
                        wide++;
                        if(wide>=N)break;
                    }


                    improve=1;


                    
                                for(int p=0;p<d[xx];p++){
                                  //型にその座標が含まれているか
                                  //printf("%d-%d  %d-%d\n",l,k,fields[xx][p][0],fields[xx][p][1]);
                                 
                                  if(fields[xx][p][0]+high>=N||fields[xx][p][1]+wide>=N){
                                    improve=1;
                                    break;
                                  //型の中に既に０がないか調べる
                                  }else if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]==0){
                                    improve=1;
                                    break;

                                  //調べていないところがあるか
                                  }else if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                    improve=0;
                                  }
                                  
                                }
                                //printf("%d",good);
                                if(improve==1)continue;

                                //型に対してステップ２
                                int kk=0;
                                improve=0;
                                for(int p=0;p<d[xx];p++)
                                    if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]>0){
                                                if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                                    has_oil[count][0]=fields[xx][p][0]+high;
                                                    has_oil[count][1]=fields[xx][p][1]+wide;
                                                    count++;
                                                    oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                                } 
                                        kk++;
                                    }else if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]==0)kk++;

                                    if(d[xx]-kk<1)continue;
                                    else if(d[xx]-kk<4){
                                        int baka=0;
                                        for(int p=0;p<d[xx];p++){
                                            if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]>0){
                                                if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                                    has_oil[count][0]=fields[xx][p][0]+high;
                                                    has_oil[count][1]=fields[xx][p][1]+wide;
                                                    count++;
                                                    oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                                    baka++;
                                                }                                             
                                                continue;
                                            }else if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]==0)continue;
                                            printf("q 1 %d %d\n",fields[xx][p][0]+high,fields[xx][p][1]+wide);
                                            fflush(stdout);
                                            scanf("%d",&resp);
                                            cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]=resp;
                                            if(resp != 0){
                                                if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]>0)continue;//同じのは追加しない
                                                has_oil[count][0]=fields[xx][p][0]+high;
                                                has_oil[count][1]=fields[xx][p][1]+wide;
                                                count++;
                                                oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                                baka++;
                                            }else improve=1;
                                        }
                                        if(baka>0){
                                            //nanamin(M,N,30);
                                    
                                            printf("a %d", count);
                                            for (int l = 0; l < count; l++) {
                                                printf(" %d %d", has_oil[l][0], has_oil[l][1]);
                                            }
                                            printf("\n");
                                            fflush(stdout);
                                            scanf("%d", &resp);
                                            if (resp == 1)return 0;
                                        }
                                        
                                        if(improve)break;
                                        else{
                                            cheacked_d[xx]=1;
                                            improve=2;
                                            break;
                                        }
                                                                        
                                    }else{
                                        printf("q %d",d[xx]-kk);
                                        for(int p=0;p<d[xx];p++){
                                            if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]>0){
                                                if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                                    has_oil[count][0]=fields[xx][p][0]+high;
                                                    has_oil[count][1]=fields[xx][p][1]+wide;
                                                    count++;
                                                    oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                                }                                             
                                                continue;
                                            }else if(cheacked[fields[xx][p][0]+high][fields[xx][p][1]+wide]==0)continue;
                                            printf(" %d %d",fields[xx][p][0]+high,fields[xx][p][1]+wide);                                   
                                        }
                                        printf("\n");
                                        fflush(stdout);
                                        scanf("%d",&resp);
                                    }
                                        //よい値なら調べる
                                        improve=1;
                                        if(d[xx]*0.6<=resp+kk){
                                            int baka=0;
                                            for(int p=0;p<d[xx];p++){
                                                int now_i=fields[xx][p][0]+high;
                                                int now_j=fields[xx][p][1]+wide;
                                                if(cheacked[now_i][now_j]>0){
                                                    if(oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]<0){
                                                      has_oil[count][0]=fields[xx][p][0]+high;
                                                      has_oil[count][1]=fields[xx][p][1]+wide;
                                                      count++;
                                                      oiled[fields[xx][p][0]+high][fields[xx][p][1]+wide]=1;
                                                      baka++;
                                                    }                                             
                                                    continue;//二回以上調べない
                                                }else if(cheacked[now_i][now_j]==0){
                                                    improve=0;
                                                    break;
                                                }else{
                                                    printf("q 1 %d %d\n",now_i,now_j);
                                                    fflush(stdout);
                                                    scanf("%d",&resp);
                                                    cheacked[now_i][now_j]=resp;
                                                    if(resp==0){
                                                       improve=0;
                                                    }else{
                                                       if(oiled[now_i][now_j]>0)continue;//同じのは追加しない
                                                       has_oil[count][0]=now_i;
                                                       has_oil[count][1]=now_j;
                                                       count++;
                                                       oiled[now_i][now_j]=1;
                                                       baka++;
                                                    }
                                                }
                                            }
                                            if(baka>0){
                                                //nanamin(M,N,30);
                                        
                                               printf("a %d", count);
                                               for (int l = 0; l < count; l++) {
                                                  printf(" %d %d", has_oil[l][0], has_oil[l][1]);
                                                }
                                               printf("\n");
                                               fflush(stdout);
                                               scanf("%d", &resp);
                                               if (resp == 1)return 0;
                                            }
                                        

                                         //すべてあっていれば次
                                         if(improve>0){
                                            for(int p=0;p<d[xx];p++){
                                                 int now_i=fields[xx][p][0]+high;
                                                 int now_j=fields[xx][p][1]+wide;
                                              if(oiled[now_i][now_j]<0){
                                                 has_oil[count][0]=now_i;
                                                 has_oil[count][1]=now_j;
                                                 count++;
                                                 oiled[now_i][now_j]=1;
                                                }  
                                            }
                                            cheacked_d[xx]=1;
                                            improve=2;
                                            break;
                                         }
                                        // }else if(resp+kk<=d[xx]*0.3){
                                        //     improve=3;
                                        //     break;
                                
                                        //  //少ないrespが続くところは0と考える    
                                        // }else if(resp<=d[xx]*0.1){
                                        //     for(int p=0;p<d[xx];p++){
                                        //         if(oiled[fields[xx][p][0]][fields[xx][p][1]])continue;
                                        //         zero_cnt[fields[xx][p][0]][fields[xx][p][1]]++;
                                        //         if(zero_cnt[fields[xx][p][0]][fields[xx][p][1]]>3)cheacked[fields[xx][l][0]][fields[xx][l][1]]=0;
                                        //     }
                                        }
                               
                    }
                if(improve>=2)break;
            }
                           
        }
        for(int l=0;l<M;l++)cheacked_d[l]=0;
    
    }    

}
