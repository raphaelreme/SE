int fibo(int);


int main(){
 fibo(8);
}

int fibo(int n){
  if (n<0){
    return -1;
  }
  if (n<2){
    return n;
  }
  return fibo(n-1)+fibo(n-2);
}
