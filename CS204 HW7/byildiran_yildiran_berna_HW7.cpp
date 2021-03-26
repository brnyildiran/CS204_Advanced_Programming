#include<iostream>
#include<string>
using namespace std;
/*
*****************************************************
Encryption Code by Berna Yildiran
---------------------------------
Request text and key from the user.
Encrypt text with respect to key.
*****************************************************
*/

/*Function for swapping elements in the given location
  myChar: Character of the plaintext
  p1, p2: Locations of the Bits, which will swapped w/ each other
  n: Amount of Bits to be swapped, starting from p1 and p2
*/
unsigned int swapBits(unsigned int myChar, unsigned int p1, unsigned int p2, unsigned int n)  
{  
	//Move all bits of first set to rightmost side 
	unsigned int set1 = (myChar >> p1) & ((1U << n) - 1);  

	//Move all bits of second set to rightmost side 
	unsigned int set2 = (myChar >> p2) & ((1U << n) - 1);  

	//Xor the two sets 
	unsigned int Xor = (set1 ^ set2);  

	//Put the Xor bits back to their original positions 
	Xor = (Xor << p1) | (Xor << p2);  

	//Xor the 'Xor' with the original number so that the two sets are swapped
	unsigned int result = myChar ^ Xor;  

	return result;  
}  

//Permute Function
unsigned char swapindex( unsigned char myPreChar)
{
	unsigned char A, B, C, D, E, F, G;

	A = myPreChar;
	B = swapBits(int(A), 7, 5,1);
	C = swapBits(int(B), 7, 4,1);
	D = swapBits(int(C), 7, 6,1);
	E = swapBits(int(D), 3, 1,1);
	F = swapBits(int(E), 3, 0,1);
	G = swapBits(int(F), 3, 2,1);
	return G;
}

int main()
{
	string key, plaintext;
	unsigned char Post_Permuted_Char, A;
	unsigned int i, j;

	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;
	cout << "Please enter the encryption key: ";
	getline(cin,key);

	cout << "Please enter the plaintext to be encrypted: ";
	while(getline(cin,plaintext))
	{
		cout << "Ciphertext: ";
		for( i = 0; i < plaintext.length() ; i++)
		{
			Post_Permuted_Char = swapindex(plaintext[i]); //Get chars one by one and do necessary processes
			A = Post_Permuted_Char ^ key[i % key.length()]; //XOR'ing with the key, after permuting
			cout << hex << int(A); //Encrypted plaintext with respect to key
		}

		/*
		//ALTERNATIVE CODE FOR MATCHING plaintext WITH key
		for( i = 0, j=0; i < plaintext.length() && j <= key.length() ; i++, j++)
		{
		Post_Permuted_Char = swapindex(plaintext[i]); 
		if(j != key.length())
		A = Post_Permuted_Char ^ key[j]; 
		else if(j == key.length())
		j=0;

		cout << hex << int(A);
		}*/

		cout << endl;
		cout << "Please enter the plaintext to be encrypted: ";
	}
	return 0;
}