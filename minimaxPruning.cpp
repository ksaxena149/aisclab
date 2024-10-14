#include <iostream>
#include <vector>

using namespace std;

const int MAX = INT_MAX;
const int MIN = INT_MIN;

void printData(int val, int best, int alpha, int beta){
  cout<<"Val: "<<val<<", ";
  cout<<"Best: "<<best<<", ";
  cout<<"Alpha: "<<alpha<<", ";
  cout<<"Beta: "<<beta<<endl;
}

int minimax(int depth, int nodeIndex,
            bool maximizingPlayer,
            vector<int> &values, int alpha,
            int beta,
            int maxDepth)
{

  if (depth == maxDepth){
    return values[nodeIndex];
  }

  if (maximizingPlayer)
  {
    int best = MIN;

    for (int i = 0; i < 2; i++)
    {

      int val = minimax(depth + 1, nodeIndex * 2 + i, false, values, alpha, beta, maxDepth);
      cout<<"Depth: "<<depth<<endl;
      cout<<"Before Updating: "<<" ";
      printData(val, best, alpha, beta);
      best = max(best, val);
      alpha = max(alpha, best);
      cout<<"After Updating: "<<" ";
      printData(val, best, alpha, beta);
      if (beta <= alpha){
        cout<<"Beta <= Alpha... Pruning Here...";
        break;
      }
    }
    cout<<"Returning "<<best<<endl;
    return best;
  }
  else
  {
    int best = MAX;

    for (int i = 0; i < 2; i++)
    {
      int val = minimax(depth + 1, nodeIndex * 2 + i, true, values, alpha, beta, maxDepth);
      cout<<"Depth: "<<depth<<endl;
      cout<<"Before Updating: "<<" ";
      printData(val, best, alpha, beta);
      best = min(best, val);
      beta = min(beta, best);
      cout<<"After Updating: "<<" ";
      printData(val, best, alpha, beta);
      if (beta <= alpha){
        cout<<"Beta <= Alpha... Pruning Here...";
        break;
      }
    }
    cout<<"Returning "<<best<<endl;
    return best;
  }
}

int main()
{
  vector<int> values = {3, 5, 6, 9, 1, 2, 0, -1};
  int maxDepth = 3;
  int res = minimax(0, 0, true, values, MIN, MAX, maxDepth);
  cout << "The final value is: " << res;
  return 0;
}
