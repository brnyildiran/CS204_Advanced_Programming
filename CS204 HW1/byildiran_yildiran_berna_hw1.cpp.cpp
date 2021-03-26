#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <istream>


using namespace std;

void searchArea(vector<vector< char>> & myMatrix, int xCor, int yCor)
{
	if(myMatrix[xCor][yCor] == 'x')
	{
		int a = xCor;
		int b = yCor;
		cout << xCor << " " << yCor << endl;

		do
		{
			if(myMatrix[xCor][yCor+1] == 'x')
			{

				yCor+=1;
				cout << xCor << " " << yCor << endl;
			}
			else if(myMatrix[xCor-1][yCor] == 'x')
			{

				xCor-=1;
				cout << xCor << " " << yCor << endl;
			}
			else if(myMatrix[xCor][yCor-1] == 'x')
			{
				yCor-=1;
				cout << xCor << " " << yCor << endl;
			}
			else if(myMatrix[xCor+1][yCor] == 'x')
			{
				xCor+=1;
				cout << xCor << " " << yCor << endl;
			}
			
		}while(a != xCor && b != yCor);

	}
	else
	{
		cout << "This cell is not occupied!" << endl;
		do
		{
			cout << "Please enter starting coordinates, first row X then column Y: ";
			cin >> xCor >> yCor;

			if(!cin)
			{
				cin.clear();
				cin.ignore(10000000000, '\n');
			}

		} while(((xCor < -1) && (xCor > myMatrix.size())) || ((yCor < -1) && (yCor > myMatrix[0].size())));
	}
}


bool matrixChecker(ifstream & inputMatrix, vector<vector< char>> & myMatrix, string filenameMatrix)
{
	bool status = true;
	string xoline, firstline;
	int charactercounter=0, linecounter=0, charactercounter2=0;
	char ch, ch2;

	while(getline(inputMatrix, xoline))
	{
		linecounter++;
		istringstream iss(xoline);
		while(iss >> ch)
		{
			charactercounter++;
			if (ch != 'x')
			{
				if(ch != 'o')
				{
					status = false;		 
					cout << filenameMatrix << " includes invalid char(s)" << endl;
				}
			}
		}	
	}
	inputMatrix.clear();
	inputMatrix.seekg(0);

	getline(inputMatrix,firstline);
	istringstream iss2(firstline);
	while(iss2 >> ch2)
	{
		charactercounter2++;
	}
	inputMatrix.clear();
	inputMatrix.seekg(0);

	if((linecounter*charactercounter2) != charactercounter)
	{
		cout << filenameMatrix << " is invalid matrix, does not contain same amount of char each row!" << endl;
		status = false;
	}
	return status;
}


void matrixPrinter(ifstream & inputMatrix, vector<vector< char>> & myMatrix)
{
	string xoline;
	int charactercounter=0, linecounter=0;
	unsigned int i, j;
	char ch;
	vector<char>temp;
	while(getline(inputMatrix, xoline))
	{
		linecounter++;	
		istringstream iss(xoline);
		while(iss >> ch)
		{
			charactercounter++;
			temp.push_back(ch);

		}
		myMatrix.push_back(temp);
		temp.clear();

	}
	for(i=0; i < myMatrix.size() ;i++) 
	{
		for(j=0; j < myMatrix[0].size(); j++)  
		{
			cout<<myMatrix[i][j] << "  ";
		}
		cout << endl;

	}
}

int main()
{
	ifstream inputMatrix;
	string filenameMatrix;
	unsigned int xCor, yCor, result;

	vector<vector<char>> myMatrix;
	vector<char>temp;
	vector<int>locations;

	cout << "Please enter file name: ";
	cin >> filenameMatrix;

	inputMatrix.open(filenameMatrix.c_str());

	while (inputMatrix.fail())
	{
		cout << "Cannot find a file named " << filenameMatrix << endl;
		cout << "Please enter file name: ";
		cin >> filenameMatrix;
		inputMatrix.open(filenameMatrix.c_str());
	}

	if(matrixChecker(inputMatrix, myMatrix, filenameMatrix) == false)
	{
		return 0;
	}
	else
	{
		cout << "Input Matrix: " << endl;
		matrixPrinter(inputMatrix, myMatrix);


		do
		{
			cout << "Please enter starting coordinates, first row X then column Y: ";
			cin >> xCor >> yCor;

			if(!cin)
			{
				cin.clear();
				cin.ignore(10000000000, '\n');
			}
			else if((xCor == -1) && (yCor == -1))
			{
				cout << "Terminating..." << endl;
				return 1;
			}
			else
			{
				searchArea(myMatrix, xCor, yCor);
			}
		} while(((xCor < -1) && (xCor > myMatrix.size())) || ((yCor < -1) && (yCor > myMatrix[0].size())));

	}
	return 1;
}