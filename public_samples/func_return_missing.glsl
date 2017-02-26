
// good
void foo() {
	int i;
}

// good
void bar() {
	int i;
	return;
}

// good
bool baz() {
	int i;
	return true;
}

// bad - missing return type
int fubar() {
	int i;
}

// bad - mismatch
int fubar() {
	return 5.0;
}
