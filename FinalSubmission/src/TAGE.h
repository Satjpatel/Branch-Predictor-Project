// Code for TAGE Predictor 
// Including the necessary header files here
// TAGE Header File
#include <cstdlib>
#include <time.h>
#include <bitset>

// Constants being used here
#define BIMODAL_CTR_MAX  3
#define BIMODAL_CTR_INIT 2
#define TAGPRED_CTR_MAX  7
#define TAGPRED_CTR_INIT 0
#define BIMODALLOG   14
#define NUMTAGTABLES 4
#define TAGPREDLOG 12
#define TAKEN 1
#define NOT_TAKEN 0

// Structures used here
/* 
    TagEntry --> Each element in the prediction table
    CompressedHist --> History Implementation 
*/

// Each entry in the tag Pred Table
struct TagEntry 
{
    int ctr;
    unsigned int tag;
    int usefulBits;
};

// Folded History implementation ... from ghr (geometric length) -> compressed(target)
struct CompressedHist
{
    unsigned int geomLength;
    unsigned int targetLength;
    unsigned int compHist;
      
    void updateCompHist(std::bitset<131> ghr)
    {
        int mask = (1 << targetLength) - 1;
        int mask1 = ghr[geomLength] << (geomLength % targetLength);
        int mask2 = (1 << targetLength);
            compHist  = (compHist << 1) + ghr[0];
            compHist ^= ((compHist & mask2) >> targetLength);
            compHist ^= mask1;
            compHist &= mask;  
         
    }    
};


// Functions used here
/* 
    SatIncrement() --> Saturation Counter Incrementer 
    SatDecrement() --> Saturation Counter Decrementer     
*/

int SatIncrement(int state, int max){
	if (state<max && state >=0){
	    state = state +1;
		return state;
	}else if(state <0){
	    return 0;
	}else{
	    return max;
	}
}

int SatDecrement(int state){
	if (state>0){
	    state = state-1;
		return state;
	}else{
	    return 0;
	}
}


// The class definition for this particular function 
// The entire predictor can be broken down into 3 simple parts 
/* 
    1. Initializing Function -- Used at the start only, to make all the history bits zero 
    2. Prediction Function -- Takes the PC value and gives us the prediction (going to take or not)
    3. Update Function -- Takes in the PC value, our prediction and the real predition to update the history tables 

*/

class my_TAGE_P1 {
public:
	bool TAGE_Predict();
	void TAGE_Update();

    // insfrastructure data types
	my_update u;
	branch_info bi;
	
	// Variable declarations
	 std::bitset<131> GHR;           // global history register
	 // 16 bit path history
	 int PHR;
	 // Bimodal
	 unsigned int  historyLength; // history length
	 //Tagged Predictors
	 TagEntry *tagPred[NUMTAGTABLES];
	 unsigned int numTagPredEntries;
	 unsigned int tagPredLog;
	 unsigned int geometric[NUMTAGTABLES];
	 //Compressed Buffers
	 CompressedHist indexComp[NUMTAGTABLES];
	 CompressedHist tagComp[2][NUMTAGTABLES]; 
	 
	 // Predictions need to be global
	 bool primePred;
	 bool altPred;
	 int primeBank;
	 int altBank;
	 // index had to be made global else recalculate for update
	 unsigned int indexTagPred[NUMTAGTABLES];
	 unsigned int tag[NUMTAGTABLES];
	 unsigned int clock;
	 int clock_flip;
	 unsigned int altBetterCount;
	
	// -------
	
	// Bimodal table
	unsigned int bimodalLog  = BIMODALLOG;
  	unsigned int numBimodalEntries   = (1<< bimodalLog); // entries in pht 
    unsigned int *bimodal = new unsigned int[numBimodalEntries];  // pattern history table

    // Initializer Function 
   	void TAGE_Init() {
        for(unsigned int ii=0; ii< numBimodalEntries; ii++){
		    bimodal[ii]=BIMODAL_CTR_INIT;
		}
		
	   // Next to initiating the taggedPredictors
		tagPredLog = TAGPREDLOG;
		numTagPredEntries = (1 << tagPredLog);         
		
		for(unsigned int ii = 0; ii < NUMTAGTABLES ; ii++)
		{
		   tagPred[ii] = new TagEntry[numTagPredEntries];
		}
		for(unsigned int ii = 0; ii < NUMTAGTABLES; ii++)
		{
		    for(unsigned int j =0; j < numTagPredEntries; j++)
		    {
		        tagPred[ii][j].ctr = 0;
		        tagPred[ii][j].tag = 0;
		        tagPred[ii][j].usefulBits = 0;
		    }
		  
		}
		
		geometric[0] = 130;
		geometric[1] = 44;
		geometric[2] = 15;
		geometric[3] = 5;
		for(int i = 0; i < NUMTAGTABLES; i++)
		{
		    indexComp[i].compHist = 0;
		    indexComp[i].geomLength = geometric[i]; 
		    indexComp[i].targetLength = TAGPREDLOG;
		}
		
		for(int j = 0; j < 2 ; j++)
		{
		    for(int i=0; i < NUMTAGTABLES; i++)
		    {
		        tagComp[j][i].compHist = 0;
		        tagComp[j][i].geomLength = geometric[i];
		        if(j == 0)
		        {
		            if(i < 2)
		            tagComp[j][i].targetLength = 9 ;
		            else
		            tagComp[j][i].targetLength = 9 ;    
		        }
		        else
		        {
		            if(i < 2)
		            tagComp[j][i].targetLength = 8 ;
		            else
		            tagComp[j][i].targetLength = 8 ;
		        }
		    }   
		}  
		  
		// Preditions banks and prediction values 
		primePred = -1;
		altPred = -1;
		primeBank = NUMTAGTABLES;
		altBank = NUMTAGTABLES;
		   
		for(int i=0; i < NUMTAGTABLES; i++)
		{    
		     indexTagPred[i] = 0;
		}
		for(int i=0; i < NUMTAGTABLES; i++)
		{    
		     tag[i] = 0;
		}
		clock = 0;
		clock_flip = 1;
		PHR = 0;
		GHR.reset();
		altBetterCount = 8;
    }

	
};