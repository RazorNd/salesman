#include "../salesmanLib/salesman.h"
#include "../salesmanLib/substitution.h"
#include "../salesmanLib/objectivefunction.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

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
    Salesman engine(n, 20);

    double lastAverage;
    int countAverageEqual = 0;

    for(int i = 1; i < 1000; i++)
    {
        double currentAverage = engine.averageResult();
        cout << "Step number " << i
             << " best solution: " << engine.makeStep()
             << " averege result: " << currentAverage << endl;

        if(currentAverage == lastAverage)
        {
            countAverageEqual++;
        }
        else
        {
            countAverageEqual = 0;
            lastAverage = currentAverage;
        }

        if(countAverageEqual >= 50)
        {
            break;
        }

        //this_thread::sleep_for(chrono::milliseconds(50));

    }

    cout << "Answer: " << engine.answer();

    return 0;
}

