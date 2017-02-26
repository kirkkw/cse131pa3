int foo(int x, int y){
        return x + y;
}


void main(){
        int x = 0;
        int y = 1;
        int z = 2;
        
        z = foo();
        z = foo(x);
        z = foo(x,y,z);
        z = foo(x, true);
        
        
        int i = foo(x,y);
        bool b = foo(x,y);
}
