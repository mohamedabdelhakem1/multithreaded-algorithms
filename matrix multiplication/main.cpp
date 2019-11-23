#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;
const size_t N = 10000;
int mat1[N][N];
int mat2[N][N];
int res[N][N];
struct mat_args {
    int i,j,size;
};

struct row_args {
    int i,col,size;
};

void printResult(int n1,int m2) {
    for(int  i = 0 ; i < n1 ; i++) {
        for(int j = 0 ; j< m2 ; j++) {
            cout<<res[i][j]<<" ";
        }
        cout<<endl;
    }
}

/**
row variation
*/
void *matRowMultiply(void* args) {
    struct row_args* a = (struct row_args *)args;
    int i = a->i;
    int size = a->size;
    int col = a->col;
    for(int j = 0 ; j < col ; j++) {
        int sum = 0;
        for(int k = 0 ; k < size ; k++) {
            sum += ( mat1[i][k] *  mat2[k][j]);
        }
        res[i][j] = sum;
    }
    pthread_exit(NULL);
}
void matMultiplyThreadingByRow(int n1,int m1,int n2,int m2) {
    pthread_t t_array[n1];
    for(int  i = 0 ; i < n1 ; i++) {
        struct row_args *new_args = (struct row_args*) malloc(sizeof(row_args));
        new_args->i = i;
        new_args->col = m2;
        new_args->size = m1;
        pthread_create(&t_array[i],NULL,matRowMultiply, (void *)new_args);
    }
    for(int  i = 0 ; i < n1 ; i++) {
        pthread_join(t_array[i],NULL);
    }
    printResult(n1,m2);
}
/**
 element variation
*/

void *matElementMultiply(void* args) {
    struct mat_args* a = (struct mat_args *)args;
    int i = a->i;
    int j = a->j;
    int size = a->size;
    int sum = 0;
    for(int k = 0 ; k < size ; k++) {
        sum += ( mat1[i][k] *  mat2[k][j]);
    }
    res[i][j] = sum;
    pthread_exit(NULL);
}
void matMultiplyThreadingByElement(int n1,int m1,int n2,int m2) {
    pthread_t t_array[n1][m2];
    for(int  i = 0 ; i < n1 ; i++) {
        for(int j = 0 ; j< m2 ; j++) {
            struct mat_args *new_args = (struct mat_args*) malloc(sizeof(mat_args));
            new_args->i = i;
            new_args->j = j;
            new_args->size = m1;
            int  c = pthread_create(&t_array[i][j],NULL,matElementMultiply, (void *)new_args);
            if(c) {
                cout<<"can not create child thread"<<endl;
            }
        }
    }
    for(int  i = 0 ; i < n1 ; i++) {
        for(int j = 0 ; j< m2 ; j++) {
            pthread_join(t_array[i][j],NULL);
        }
    }
    printResult(n1,m2);
}


int main() {
    freopen("input.txt" , "r" ,stdin);
    int n1,m1,n2,m2;
    cin>>n1>>m1;
    for(int i = 0 ; i< n1 ; i++) {
        for(int j = 0 ; j< m1 ; j++) {
            cin>>mat1[i][j];
        }
    }
    cin>>n2>>m2;
    for(int i = 0 ; i< n2 ; i++) {
        for(int j = 0 ; j< m2 ; j++) {
            cin>>mat2[i][j];
        }
    }
    freopen("output.txt" ,"w",stdout);
    if(m1 != n2){
        cout<<"not compatible matrices"<<endl;
        return 0;
    }
    clock_t start = clock();
    matMultiplyThreadingByElement(n1,m1,n2,m2);
    clock_t end = clock();
    cout<<"element :" <<(end-start) <<endl;

    start = clock();
    matMultiplyThreadingByRow(n1,m1,n2,m2);
    end = clock();
    cout<<"row :"<<(end-start) <<endl;

    return 0;
}
