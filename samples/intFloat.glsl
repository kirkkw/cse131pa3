void main(){
	int i;
	float f;

	i = f;
	f = i;
	f *= i;
	f /= i;
	f += i;
	f -= i;
	i*f;
	f*i;
	i/f;
	f/i;
	f+i;
	i+f;
	f-i;
	i-f;

        bool b;       
	b = (i = f);
	b = (f = i);
	b = (f *= i);
	b = (f /= i);
	b = (f += i);
	b = (f -= i);
	b = i*f;
	b = f*i;
	b = i/f;
	b = f/i;
	b = f+i;
	b = i+f;
	b = f-i;
	b = i-f;
}
