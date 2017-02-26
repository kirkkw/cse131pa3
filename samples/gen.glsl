int emptyMain(){
}

int conditionReturn(){
  if(true)
    return 1;
}

vec2 badReturn(){
  return 2;
}


int deeplyNestedReturn(int i){
  int integer = true;
  bool boolean = 5;

  for(i = 0; i<5; ++i){
	while(i != j || integer){
		switch(i){
			case 5: {
				if(i < 5 || boolean == false){}
				else {return 3;}
			}
		}
	}
  }
}


void redecl(){
        int k = 5;
        vec2 k;
        vec3 k = k.xyx;
        vec4 k = k.wxyz;
        k = 5;
}

int notDeclared(){
   return f();
}

int f(){
  return 5;
}
