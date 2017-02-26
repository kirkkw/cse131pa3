void main(){

  vec2 v2;
  vec3 v3;
  vec4 v4;
  mat2 m2;
  mat3 m3;
  mat4 m4;
  float f;
  int i;
  bool b;

  v2 = v3;
  v2 = m2;
  m2 = f;
  f = m2;
  f = v2;
  f = b;
  b = f;
  b = i;
  i = b;
  i = f;
  i = v2;
  i = m2;
  v2 = i;
  m2 = i;
  i += f;
  i += v2;
  i += m2;
  i += b;
  i -= b;
  f += v2;
  f += m2;
  f += b;
  b += i;
  b += f;
  b += v2;
  b += m2;
  m2 += v2;
  m2 += b;
  m2 += i;
  v2 += m2;
  v2 += b;
  v2 += i;
  v2 /= m2;
  m2 *= v2;
  m2 /= v2;
}
