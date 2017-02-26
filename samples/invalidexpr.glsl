
void main()
{

  int i = 1;
  float f = 1.0;
  bool b = true;
  vec2 v2;
  vec3 v3;
  vec4 v4;
  mat2 m2;
  mat3 m3;
  mat4 m4;

  ++b;
  +b;
  b++;
  b--;
  -b;
  --b;
 


  b = ( (true && 5) || (5 && 2.0) );
  b = ( (true || 5) && (v2 || 2) );
  b = ( (true && 0.5) || (0.5 && 2) );
  b = ( (true || 0.5) && (0.5 || 2) );

  
  b = b + i;
  b = b*i;
  b = b/i;
  b = b*i;
  b = i - b;
  b = b + f;
  b = b*f;
  b = b/f;
  b = b*f;
  b = f - b;
  b = b + v2;
  b = b*v2;
  b = b/v2;
  b = b*v2;
  b = v2 - b;
  
   
  

  m2 + m3 + m4;
  m2 * m3 * m4;

  m2 = m4/m2;
  m2 = m2/v2;
  m2 = m2/b;
  m2 = m2*b;

}
