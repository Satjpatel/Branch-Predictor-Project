// Testing out the CSV stuff

#include <iostream>
#include <fstream> 

using namespace std ; 

int main () 
{ 
    class DataBlock { 
        public: 
        int PC ; 
        bool Hist1 ; 
        bool Hist2 ; 
        bool Predict ; 
        bool Correct ; 
    }    ; 

    DataBlock trace [4] ; 

    trace[0] = {4, 0 , 1, 1, 1} ; 
    trace[1] = {18, 1, 1, 1, 1} ; 
    trace[2] = {22, 1, 0, 0, 0} ; 
    trace[3] = {61, 0, 0, 0, 1} ; 
    

    ofstream fout ; 
    // Program Counter Value
    int PC [4] = { 4, 18, 22, 61} ;
    bool History1 [4] = { 0, 1, 1, 0} ; 
    bool History2 [4] = { 1, 1, 0, 0} ;
    bool Prediction [4] = {1 ,1 , 0, 0} ; 
    bool RealPrediction [4] = {1, 1, 0, 0} ; 

    fout.open("test.csv") ; 

   // fout<<PC[0]<<","<<PC[1]<<","<<PC[2]<<","<<PC[3] ; 
   for (int i = 0 ; i < 4 ; i++) 
   { 
    fout<<trace[i].PC<<","<<trace[i].Hist1<<","<<trace[i].Hist2<<","<<trace[i].Predict<<","<<trace[i].Correct<<"\n" ; 
   }

    //Doing the CSV shit now 
    fout.close() ; 

    return 0 ; 

}