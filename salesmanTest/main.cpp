#include "../salesmanLib/salesman.h"
#include "../salesmanLib/substitution.h"
#include "../salesmanLib/objectivefunction.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");

    int n;
    fin >> n;

    std::vector<int> arr(n * n);
    for(int i = 0; i < n * n; i++)
    {
        fin >> arr[i];
    }

    Substitution::setFuntion(ObjectiveFunction(std::move(arr)));
    Salesman engine(n, 100);

    for(int i = 1; i < 1000; i++)
    {
        cout << "Step number " << i << " best solution: " << engine.makeStep() << endl;
    }

    cout << "Answer: " << engine.answer();

    return 0;
}

