#include <iostream>
using namespace std;
void recursiva(string *Mat, int l, int c)
{
	for(int i=0; i < l*c; i++)
	{
		if (i % l == 0)
			cout << "\n";
			cout << Mat[i] << " ";
	
		
	}
 	 cout << Mat [c*2 + 1];	
}

int main()
{
	string Mat[3][3] = {{"a","b", "c"}, {"a","b", "c"}, {"a","b", "c"}};
	
	
	recursiva(&Mat[0][0], 3, 3);
	
	return 0;
}