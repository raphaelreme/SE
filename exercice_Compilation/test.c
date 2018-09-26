uint32_t a;
void g();

__attribute__((naked)) void f() {
  for(uint_t i=0; i<=a; i++){
    g()
  }
}
