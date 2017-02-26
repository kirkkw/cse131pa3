/*
#version 150   // Uncomment when running through reference compiler.
precision highp float;
*/


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
  
  mat4 g = m4 + 1.0;
  mat4 h = m4 * 2.0;
  mat4 j = m4 / 2.0;
  mat4 k = m4 - 2.0;
  mat4 g2 = 1.0 + m4;
  mat4 h2 = 2.0 * m4;
  mat4 j2 = 2.0 / m4;
  mat4 k2 = 2.0 - m4;
  
  
  vec2 v = v2 + 1.0;
  vec3 vv = v3 + 1.0; 
  vec4 vvv = v4 + 1.0; 
  vec2 bv = 1.0 + v2;
  vec3 bvv = 1.0 + v3; 
  vec4 bvvv = 1.0 + v4;
  
  
  vec2 sv = v2 - 1.0;
  vec3 svv = v3 - 1.0; 
  vec4 svvv = v4 - 1.0; 
  vec2 sbv = 1.0 - v2;
  vec3 sbvv = 1.0 - v3; 
  vec4 sbvvv = 1.0 - v4;
  
  
  vec2 mv = v2 * 1.0;
  vec3 mvv = v3 * 1.0; 
  vec4 mvvv = v4 * 1.0; 
  vec2 mbv = 1.0 * v2;
  vec3 mbvv = 1.0 * v3; 
  vec4 mbvvv = 1.0 * v4;
  
  vec2 dv = v2 / 1.0;
  vec3 dvv = v3 / 1.0; 
  vec4 dvvv = v4 / 1.0; 
  vec2 dbv = 1.0 / v2;
  vec3 dbvv = 1.0 / v3; 
  vec4 dbvvv = 1.0 / v4;
  
  vec2 mm = m2 * v2;
  vec3 mm2 = m3 * v3;
  vec4 mm3 = m4 * v4;
  vec2 mm4 = v2 * m2;
  vec3 mm5 = v3 * m3;
  vec4 mm6 = v4 * m4;  

  v2 = (v2 = v2);
  m2 = (m2 = m2);
  m4 = (m4 = m4);
  
  
  v2 = (v2 -= f);
  v3 = (v3 -= f);
  v4 = (v4 -= f);
  
  v2 = (v2 *= f);
  v3 = (v3 *= f);
  v4 = (v4 *= f);
  
  v2 = (v2 /= f);
  v3 = (v3 /= f);
  v4 = (v4 /= f);
  
  v2 = (v2 += f);
  v3 = (v3 += f);
  v4 = (v4 += f);
  
  m2 = (m2 += f);
  m3 = (m3 += f);
  m4 = (m4 += f);
  
  v2 = (v2 *= m2);
  v3 = (v3 *= m3);
  v4 = (v4 *= m4);
  
  v4 /= 1.0 - (2.0/(m4 * ((v4 * m4) + f * 2.0)));

}



