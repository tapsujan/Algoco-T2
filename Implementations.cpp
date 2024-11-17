#include <bits/stdc++.h>
#include <format> 
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;
using namespace std::chrono;

// +10 for each next dataset
#define INDEX_OFFSET 0
#define FILE_PATH "dataset/datasetA"
#define FILE_EXTENTION ".txt"
//this value must be at least 9, to test all cases in set dataset
#define ITERATIONS 100

// - IMPLEMENTATIONS

// int levenshtein dp oriented solution, T is solutions matrix
// THIS CODE IS BASED FROM https://gist.github.com/josejuan/2875084

int levenshtein(const string &s1, const string &s2)
{
   int N1 = s1.size();
   int N2 = s2.size();
   int i, j;
   vector<int> T(N2+1);

   for ( i = 0; i <= N2; i++ )
      T[i] = i;

   for ( i = 0; i < N1; i++ ) 
   {
      T[0] = i+1;
      int corner = i;
      for ( j = 0; j < N2; j++ ) 
      {
         int upper = T[j+1];
         if ( s1[i] == s2[j] )
            T[j+1] = corner;
         else
            T[j+1] = min(T[j], min(upper, corner)) + 1;
         corner = upper;
      }
   }
   return T[N2];
}

// int levenshteinRecursive this is the brute force implemetantion
// THIS CODE IS BASED FROM https://www.geeksforgeeks.org/introduction-to-levenshtein-distance/

int levenshteinRecursive(const string& str1, const string& str2, int m, int n)
{
    // str1 is empty
    if (m == 0) {
        return n;
    }
    // str2 is empty
    if (n == 0) {
        return m;
    }
    if (str1[m - 1] == str2[n - 1]) {
        return levenshteinRecursive(str1, str2, m - 1, n - 1);
    }
    // Tail recursion
    return 1 + min
    (
        // Insert
        levenshteinRecursive(str1, str2, m, n - 1),
        min
        (
            // Remove
            levenshteinRecursive(str1, str2, m - 1, n),
            // Replace
            levenshteinRecursive(str1, str2, m - 1, n - 1)
        )
    );
}

// Driver program to test above functions
int main()
{
    int dp_sum = 0;
    int bf_sum = 0;
    for (int i = 0; i < ITERATIONS; i++)
    {
        pair<string, string> aux;
        string s1, s2;

        //  - Load Dataset -
        //
        ifstream file;
        string fileName = FILE_PATH + to_string(ITERATIONS%9+INDEX_OFFSET) + FILE_EXTENTION;
        file.open(fileName);
        if(!file.is_open())
        {
            cout << "ERROR OPENING FILE" << endl;
            return 0;
        }
        file >> s1 >> s2;
        aux = {s1, s2};
        file.close();
        //

        auto start1 = high_resolution_clock::now();

        //  - Function Call -
        //
        levenshteinRecursive(s1, s2, i, i);
        //

        auto stop1 = high_resolution_clock::now();
    
        auto duration1 = duration_cast<microseconds>(stop1 - start1);
        bf_sum += duration1.count();

        auto start = high_resolution_clock::now();

        //  - Function Call -
        //
        levenshtein(s1, s2);
        //

        auto stop = high_resolution_clock::now();
    
        auto duration = duration_cast<microseconds>(stop - start);
        dp_sum += duration.count();
    }

    cout << "Average time taken by levenshtein function: " << dp_sum/ITERATIONS << " microseconds" << endl;
    cout << "Average time taken by levenshteinRecursive function: " << bf_sum/ITERATIONS << " microseconds" << endl;
    return 0;
}