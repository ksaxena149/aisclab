#include <iostream>
#include <vector>
using namespace std;

void generateSquare(int n)
{
  vector<vector<int>> magicSquare(n, vector<int>(n, 0));

  int i = n / 2, j = n - 1;

  for (int num = 1; num <= n * n;)
  {
    if (i == -1 && j == n)
    {
      j = n - 2;
      i = 0;
    }
    else
    {
      if (j == n)
        j = 0;
      if (i < 0)
        i = n - 1;
    }
    if (magicSquare[i][j])
    {
      j -= 2;
      i++;
    }
    else
    {
      magicSquare[i][j] = num++;
      j++;
      i--;
    }
  }

  cout << "The Magic Square for n=" << n << ":\nSum of each row or column: "
       << n * (n * n + 1) / 2 << "\n\n";

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      cout <<  magicSquare[i][j] << " ";
    }
    cout << endl;
  }
}

int main()
{
  int n;
  cout<<"Enter the value of n: ";
  cin>>n;
  generateSquare(n);
  return 0;
}
