int fibo(int);

int x = 0;
int y = 0;

int main(){
  int z = x+y;
  z++;
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
