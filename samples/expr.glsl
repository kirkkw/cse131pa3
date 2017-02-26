int globalVar = 5;

int f(int x) { return (x+1)*2;}


void main(int argc, vec2 argv){
    int x = 5; bool b = false;
    float y = b || b;
    y = b + 5.0;
    float z = 2;
    y += z - 5.0;
    y *= -z;
    y = -z / 5.0;
    y = +z * 5.0;
    ++y;
    --y;
    y++;
    y--;
    
    {
        int q = x + 5;
        int p = x * 5;
        int r = q / p;
        r += p;
        r -=p;
        r *=p;
        r /= (--p + 1);
        
        if(r){
          r = y;
        }
    }
    
    int g = f(y);
    int f = 2*f(f(f(x))) + 1;
}


