#include <iostream>
#include <fstream>
using namespace std;

#define COL_MAX 1000
#define ROW_MAX 1000

void setArray(int arr[][ROW_MAX], int row, int col)
{
	for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
			arr[i][j] = -1;

	int x, y, num = 1;
	int xmin = 0, ymin = 0, xmax = row-1, ymax = col-1;
	x = xmin;
	y = ymin;

	while(xmin < xmax || ymin < ymax) {
		while(y <= ymax) {
			arr[x][y] = num;
			y++;
			num++;
		}
		y--;
		x++;
		xmin++;
		while(x <= xmax) {
			arr[x][y] = num;
			x++;
			num++;
		}
		x--;
		y--;
		ymax--;
		while(y >= ymin) {
			arr[x][y] = num;
			y--;
			num++;
		}
		y++;
		x--;
		xmax--;
		while(x >= xmin) {
			arr[x][y] = num;
			x--;
			num++;
		}
		x++;
		y++;
		ymin++;
	}
}

void printArray(int arr[][COL_MAX], int row, int col)
{
	for(int i=0; i<row; i++) {
		for(int j=0; j<col; j++)
			cout << arr[i][j] << ' ';
		cout << endl;
	}
}

int main(void)
{
	ifstream nanoIn;
	nanoIn.open("nanobot.inp", ios::in);

	int row, col;
	nanoIn >> row >> col;

	int arr[ROW_MAX][COL_MAX];

	setArray(arr, row, col);

	int x, y;
	nanoIn >> x >> y;

	ofstream nanoOut;
	nanoOut.open("nanobot.out");
	nanoOut << arr[x-1][y-1] << endl;

	int num;
	nanoIn >> num;
	for(int i=0; i<row; i++)
		for(int j=0; j<col; j++)
			if(num == arr[i][j]) {
				nanoOut << i+1 << ' ' << j+1;
			}

	return 0;
}
