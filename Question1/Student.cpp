
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
#include <iostream>
#include <fstream>

class Student 
{
    private:
    int scores[3];

    public:
    void input()
    {
        ofstream myfile;
        myfile.open ("C:\\Code\\TravSim\\scores.txt");
  
        for (int i = 0; i < 3; i++) 
        {
            cin >> scores[i]; //takes 3 score per line
            cout << scores[i]; // displays the score as you type for visibiltiy
            myfile << "hello";
        }
        myfile.close();
    }
    int calculateTotalScore() 
    {
        int count = 0;
        for (int i = 0; i < 3; i++) 
        {
            count += scores[i];
        }
        return count;
    }
};
int main() 
{
    int n; // number of students
    cin >> n; // please put the number of student you want access
    Student *studentArray = new Student[n]; 
    
    for(int i = 0; i < n; i++)
    {
        studentArray[i].input();
    }
    
    int Alex_score = studentArray[0].calculateTotalScore(); // Alex's score is the first one in the array 

    // determine how many students scored higher than Alex
    int count = 0; 
    for(int i = 1; i < n; i++)
    {
        int totalscore = studentArray[i].calculateTotalScore();
        if(totalscore > Alex_score)
        {
            count++;
        }
    }

    // print result
    cout << count;
    
    return 0;
}