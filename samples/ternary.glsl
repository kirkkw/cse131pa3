void main(){
  int i;
  
  i = true ? 1 : 2;     // valid  
  i = true ? 3.0 : 4.0; // invalid assign
  i = 5 ? 5 : 6;        // Test Not Bool
  
  i = NOTDECLARED ? 7 : 8;      // undeclared, test not boolean
  i = UNDECLARED ? 9.0 : 10.0; // undeclared, test not boolean, invalid assign

  i = true ? YES : false; // YES undeclared
  i = true ? true: NOPE;  // NOPE undeclared


  // Test order
  bool b = x ? y : z;  // x undeclared, testNotBool, y undeclared, z undeclared;
 
 
 
  int invalid = b? 1.0 : 2.0; // invalid assign

  int nested = (((b? false: true)? false : true)? true : false)? (b? 1: 2) : (b? 3 : 4);
}

