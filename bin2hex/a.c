#include <stdio.h>
#include <math.h>

#define LEN     256
#define BLEN    32
#define CLEN    8

int main(){
    int i,j,k,m,n,sum;
    int data[BLEN/CLEN]={0};
    int data_p[LEN][BLEN]={0};
    int datap[LEN][BLEN/CLEN]={0};
    
    for(i=0;i<LEN;i++){
        // data=i;
        // data_p[i][0]=data%2/1;
        // data_p[i][1]=data%4/2;
        // data_p[i][2]=data%8/4;
        // data_p[i][3]=data%16/8;
        // data_p[i][4]=data%32/16;
        // ...
#if 0
        for(j=0;j<BLEN;j++){
            // data_p[i][j]=i%((int)pow(2.0, (double)(j+1)))/((int)pow(2.0, (double)(j)));
            data_p[i][j]=(i&(1<<j))>>j;
            // if(data_p[i][j]==0)
            //     data_p[i][j]=-1;
            printf("data_p[%d][%d]=%d\n",i, j, data_p[i][j]);
            // if(data_p[i][j]==-1)
            //     data_p[i][j]=0;
            // data+=data_p[i][j]*(int)pow(2.0,(double)j);
            data+=data_p[i][j]<<j;
        }
#else
        for(j=0;j<CLEN;j++){
            data_p[i][j]=data_p[i][j+8]=data_p[i][j+16]=data_p[i][j+24]=(i&(1<<j))>>j;
            printf("data_p[%d][%d]=%d\n",i, j, data_p[i][j]);

            for(k=0;k<BLEN/CLEN;k++){
                data[k]+=data_p[i][j+8*k]<<j;
            }
        }
#endif
        for(k=0;k<BLEN/CLEN;k++){
            datap[i][k]=data[k];
            data[k]=0;
            // datap[i]=data_p[i][0]*1+data_p[i][1]*2+data_p[i][2]*4+data_p[i][3]*8+...
            printf("datap[%d][%d]=%d\n",i,k, datap[i][k]);
        }
        sum=0;
        // datap[i][0]=1;datap[i][2]=0;datap[i][1]=2;
        for(m=0;m<BLEN/CLEN-1;m++)
            for(n=m+1;n<BLEN/CLEN;n++){
                if(datap[i][m]==datap[i][n])
                    sum++;
            }
        printf("sum%d=%d\n",i,sum);

    }

    return 0;
}
