// Harvey said this should produce no errors.
void fn() {
	int x;
	if (true)
		int x = 0;
	else
		int x = 1;
}
