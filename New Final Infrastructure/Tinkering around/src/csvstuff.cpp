// Testing out the CSV stuff

#include <iostream>
#include <fstream> 

using namespace std ; 

// Creating a structure for getting the values for the CSV file needed for the NN network 
struct DataForNN
{
	int PC_Value;
	bool HistoryNminus1;
    bool HistoryNminus2;
	bool TAGE_ActualPrediction;
	bool TAGE_MyPrediction;
};




void CSV_input(DataForNN d, string test) 
{   
    ofstream p ; 
    p.open("test.csv", std::ios_base::app) ; 
	p<< d.PC_Value << "," << d.HistoryNminus1<<","<<d.HistoryNminus2 << "," << d.TAGE_MyPrediction << "," << d.TAGE_ActualPrediction << endl; 

}


int main()
{
	DataForNN arr[4]; 
	arr[0] = { 32, 1,1, 0,1 }; 
	arr[1] = { 22, 0,1, 1,0 };
	arr[2] = { 52, 1,0, 0,1 };
	arr[3] = { 62, 0,0, 1,0 };
 
	ofstream fout; 

	//fout.open("test.csv") ; 
	
	for (int i = 0; i < 4; i++)
	{
		CSV_input(arr[i], "test"); 

	}

	fout.close(); 
	return 0; 
}

//int main () 
//{ 
//    class DataBlock { 
//        public: 
//        int PC ; 
//        bool Hist1 ; 
//        bool Hist2 ; 
//        bool Predict ; 
//        bool Correct ; 
//    }    ; 
//
//    DataBlock trace [4] ; 
//
//    trace[0] = {4, 0 , 1, 1, 1} ; 
//    trace[1] = {18, 1, 1, 1, 1} ; 
//    trace[2] = {22, 1, 0, 0, 0} ; 
//    trace[3] = {61, 0, 0, 0, 1} ; 
//    
//
//    ofstream fout ; 
//    // Program Counter Value
//    int PC [4] = { 4, 18, 22, 61} ;
//    bool History1 [4] = { 0, 1, 1, 0} ; 
//    bool History2 [4] = { 1, 1, 0, 0} ;
//    bool Prediction [4] = {1 ,1 , 0, 0} ; 
//    bool RealPrediction [4] = {1, 1, 0, 0} ; 
//
//    fout.open("test.csv") ; 
//
//   // fout<<PC[0]<<","<<PC[1]<<","<<PC[2]<<","<<PC[3] ; 
//   for (int i = 0 ; i < 4 ; i++) 
//   { 
//    fout<<trace[i].PC<<","<<trace[i].Hist1<<","<<trace[i].Hist2<<","<<trace[i].Predict<<","<<trace[i].Correct<<"\n" ; 
//   }
//
//    //Doing the CSV shit now 
//    fout.close() ; 
//
//    return 0 ; 
//
//}