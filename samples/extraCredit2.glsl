void main() {
    vec2 a;
    mat2 b;
    b = a * b;

    vec3 c;
    mat3 d;
    d = d * c;

    vec4 e;
    mat4 f;
    f = e * f;

    vec2 flArith = a * 2.5;
    vec3 invalid = c * f;

    int g = 1 * 4.0;
}