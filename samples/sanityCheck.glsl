//precision highp float; // uncomment for reference compiler 
// Just some last minute sanity checks.



float ToFloat(int i) { return 1.0; }
int Integer(int i) { return i; }
bool Equals(int x, int y) { return x == y;}
void PrintError() {}
int ToInt(int i) { return Integer(i); }




void main(){
  int i = Integer(5);
  int j = Integer(i++);

  if(Equals(i, j) != Equals(j, i))
    PrintError();
  else {
    j = i;
  }

  int count;
  for(count = Integer(0); count <= i; ++count){
    bool local;
    if(ToFloat(count++) >= 1.0){
        bool local = true;
	continue;
    } else {
	bool local = false;
        break;
    }
  }

  vec3 local;

  mat2 m2;
  vec2 v2;
  m2 = m2 + m2 * m2 - m2 / m2;
  v2 = v2 + v2 * v2 - v2 / v2;
 


  float f = ToFloat(j);

  int n = Integer(Integer(Integer(1)));
  float f2 = ToFloat(Integer(n));


  return;
}


