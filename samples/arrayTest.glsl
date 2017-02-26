void foo(int i, float f) { }
void fu(int i[2], float f[3]) { }

void main(){
   int i;
   int is[4];
   float f;
   float fs[5];

   fu(is, fs);
   fu(i, f);
   fu(is, f);
   fu(fs, is);

   foo(is, fs);
   foo(i, fs);
   foo(f, i);
   foo(i, f);
}
