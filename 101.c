#include <stdio.h>
#include <stdlib.h>

void printMatrix(int n,int **a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int isGraphical(int *a, int n) {
    int degrees[n];
    for(int i=0;i<n;i++){degrees[i]=a[i];}
    while (1) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (degrees[i] < degrees[j]) {
                    int temp = degrees[i];
                    degrees[i] = degrees[j];
                    degrees[j] = temp;
                }
            }
        }
        if (degrees[0] == 0) {
            return 1;
        }

        int d = degrees[0];
        degrees[0] = 0;

        for (int i = 1; i <= d; i++) {
            if (i >= n || degrees[i] <= 0) {
                return 0;
            }
            degrees[i]--;
        }
    }
}

int** createGraph(int *degrees, int n) {
    int **a,i,j,k,m,d;
    a=(int**)malloc(sizeof(int*)*n);
    for(i=0;i<n;i++){
        a[i]=(int *)malloc(sizeof(int)*n);
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a[i][j]=0;
        }
    }
    j=-1;
    while(1){
       // if(j>=n) return a;
        for(m=j+1;m<n;m++){
            if(degrees[m]>0){
                d=degrees[m];
                break;
            }
        }
        if(m==n){
            return a;
        }
        j=m;k=0;
        for(m=j+1;m<n && k<=d;m++){
            if(degrees[m]!=0){
                k++;
                a[m][j]=1;
                a[j][m]=1;
                degrees[m]--;
            }
        }
        
    }
        
}

int main() {
    int n;
    int **a;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    int *degrees;
    degrees=(int *)malloc(sizeof(int)*n);
    printf("Enter the degree sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &degrees[i]);
    }

    if (isGraphical(degrees, n)) {
        printf("The degree sequence is graphical.\n");
        a=createGraph(degrees, n);
        printMatrix(n,a);
    } else {
        printf("The degree sequence is not graphical.\n");
    }

    return 0;
}