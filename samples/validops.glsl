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
  
  i += i;
  i -= i;
  i *= i;
  i /= i;
  i = i + i;
  i = i - i;
  i = i * i;
  i = i / i;

  f += f;
  f -= f;
  f *= f;
  f /= f;
  f = f + f;
  f = f - f;
  f = f * f;
  f = f / f;

  b = b && b;
  b = b || b;


  v2 += v2;
  v2 -= v2;
  v2 *= v2;
  v2 /= v2;
  v2 = v2 + v2;
  v2 = v2 - v2;
  v2 = v2 * v2;
  v2 = v2 / v2;

  v3 += v3;
  v3 -= v3;
  v3 *= v3;
  v3 /= v3;
  v3 = v3 + v3;
  v3 = v3 - v3;
  v3 = v3 * v3;
  v3 = v3 / v3;
  
  v4 += v4;
  v4 -= v4;
  v4 *= v4;
  v4 /= v4;
  v4 = v4 + v4;
  v4 = v4 - v4;
  v4 = v4 * v4;
  v4 = v4 / v4;


  m2 += m2;
  m2 -= m2;
  m2 *= m2;
  m2 /= m2;
  m2 = m2 + m2;
  m2 = m2 - m2;
  m2 = m2 * m2;
  m2 = m2 / m2;

  m3 += m3;
  m3 -= m3;
  m3 *= m3;
  m3 /= m3;
  m3 = m3 + m3;
  m3 = m3 - m3;
  m3 = m3 * m3;
  m3 = m3 / m3;
  
  m4 += m4;
  m4 -= m4;
  m4 *= m4;
  m4 /= m4;
  m4 = m4 + m4;
  m4 = m4 - m4;
  m4 = m4 * m4;
  m4 = m4 / m4;

/*Not tested*/
//  f = v2[0];
//  f = v3[0];
//  f = v4[0];
  f = v2.x;
  f = v3.x;
  f = v4.x;
  
  v2 = m2[0];
  v3 = m3[0];
  v4 = m4[0];
  
  +i;
  ++i;
  i++;
  i--;
  --i;
  -i;

  +f;
  ++f;
  f++;
  f--;
  --f;
  -f;
  
  +v2;
  ++v2;
  v2++;
  v2--;
  --v2;
  -v2;

  +v3;
  ++v3;
  v3++;
  v3--;
  --v3;
  -v3;
    
  +v4;
  ++v4;
  v4++;
  v4--;
  --v4;
  -v4;

  
  +m2;
  ++m2;
  m2++;
  m2--;
  --m2;
  -m2;

  +m3;
  ++m3;
  m3++;
  m3--;
  --m3;
  -m3;
    
  +m4;
  ++m4;
  m4++;
  m4--;
  --m4;
  -m4;

}
