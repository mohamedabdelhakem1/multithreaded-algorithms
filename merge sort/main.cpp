#include <bits/stdc++.h>
#include <pthread.h>
const size_t N = 100000000;
int arr[N];
long long main_tid;
using namespace std;
struct arr_args {
    int l,r;
};
void merge_halves(int l,int m,int r) {
    int n1 = m-l+1;
    int n2 = r-m;
    int left[n1];
    int right[n2];
    for(int i = 0 ; i < n1; i++) {
        left[i] = arr[l+i];
    }
    for(int i = 0 ; i < n2; i++) {
        right[i] = arr[m+1+i];
    }
    int i = 0,j =0, k =l;
    while(i < n1 &&  j < n2) {
        if(left[i] > right[j]) {
            arr[k++] = right[j++];
        } else {
            arr[k++] = left[i++];
        }
    }
    while(i <n1) {
        arr[k++] = left[i++];
    }
    while(j <n2) {
        arr[k++] = right[j++];
    }
}
void * mergeSort(void * args) {
    struct arr_args * a = (struct arr_args *) args;
    int r = a->r;
    int l = a->l;
    if(l < r) {
        int m = (l+r)/2;
        struct arr_args *left = (struct arr_args *)malloc(sizeof (struct arr_args));
        left->l = l;
        left->r = m;
        pthread_t t_left;
        if(pthread_create(&t_left,NULL,mergeSort,(void *)left)) {
            cout<<"can not create thread"<<endl;
        }

        struct arr_args *right = (struct arr_args *)malloc(sizeof (struct arr_args));
        right->l = m+1;
        right->r = r;
        pthread_t t_right;
        if(pthread_create(&t_right,NULL,mergeSort,(void *)right)) {
            cout<<"can not create thread"<<endl;
        }

        pthread_join(t_left,NULL);
        pthread_join(t_right,NULL);
        merge_halves(l,m,r);
    }
    if(main_tid != pthread_self()) {
        pthread_exit(NULL);
    }
}
int main() {
    main_tid = pthread_self();
    int n;
    freopen("input.txt" ,"r" , stdin);
    cin>>n;
    for(int i = 0 ; i < n ; i++)
        cin>>arr[i];

    struct arr_args * a = (struct arr_args *)malloc(sizeof (struct arr_args));
    a->l = 0;
    a->r = n-1;
    mergeSort(a);
//    pthread_t t_main;
//    pthread_create(&t_main,NULL,mergeSort, a);
//    pthread_join(t_main,NULL);

    for(int i = 0 ; i < n ; i++)
        cout<<arr[i]<<endl;;
    return 0;
}
