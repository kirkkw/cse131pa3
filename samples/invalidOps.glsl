void main(){
  vec2 v2;
  vec3 v3;
  vec4 v4;
  mat2 m2;
  mat3 m3;
  mat4 m4;

  v2 *= m3;
  v2 *= v3;
  m4 *= v2 * m4;
  m4 *= v2; 
  m4 = m2;
  m4 *= m2;
  v2 = v3;
  v2 *= v3;
  m3 *= v2;
  m2 /= v2;
  v2 += m2;
  m2 += v2;

}
