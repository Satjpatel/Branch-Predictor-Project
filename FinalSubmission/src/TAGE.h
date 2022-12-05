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

    // --------------------- Initializing Function 
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

	// --------- End of Initializing Function

	// ------------ Predict Function 
	bool TAGE_Predict(branch_info & b) 
	{
		u.bi = b;
		unsigned int PC = b.address;
		bool basePrediction;
	  unsigned int bimodalIndex   = (PC) % (numBimodalEntries);
	  unsigned int bimodalCounter = bimodal[bimodalIndex];
	  
	  if(bimodalCounter > BIMODAL_CTR_MAX/2){
		basePrediction =  1; 
	  }else{
		basePrediction =  0; 
	  }
	  
		  // Hash to get tag includes info about bank, pc and global history compressed
		
		// formula given in PPM paper 
		// pc[9:0] xor CSR1 xor (CSR2 << 1)
		for(int i = 0; i < NUMTAGTABLES; i++)
		{ 
		   tag[i] = PC ^ tagComp[0][i].compHist ^ (tagComp[1][i].compHist << 1);
		   /// These need to be masked
		 // 9 bit tags for T0 and T1 // 8 bit tags for T2 and T3
		}
		tag[0] &= ((1<<9)-1);
		tag[1] &= ((1<<9)-1);
		tag[2] &= ((1<<9)-1);
		tag[3] &= ((1<<9)-1);
		// Tags now ready
		
	  // How to get index for each bank ??
	  // bank 1
		// Hash of PC, PC >> index length important , GHR geometric, path info
		unsigned int index_mask = ((1<<TAGPREDLOG) - 1);
		
			   
		   
		   indexTagPred[0] = PC ^ (PC >> TAGPREDLOG) ^ indexComp[0].compHist ^ PHR ^ (PHR >> TAGPREDLOG);
		   indexTagPred[1] = PC ^ (PC >> (TAGPREDLOG - 1)) ^ indexComp[1].compHist ^ (PHR );
		   indexTagPred[2] = PC ^ (PC >> (TAGPREDLOG - 2)) ^ indexComp[2].compHist ^ (PHR & 31);
		   indexTagPred[3] = PC ^ (PC >> (TAGPREDLOG - 3)) ^ indexComp[3].compHist ^ (PHR & 7);  
		   for(int i = 0; i < NUMTAGTABLES; i++)
		   {
				indexTagPred[i] = indexTagPred[i] & index_mask;
			   
		   }
		   
			// get two predictions prime and alt (alternate)
		   primePred = -1;
		   altPred = -1;
		   primeBank = NUMTAGTABLES;
		   altBank = NUMTAGTABLES;
		   
		   /// See if any tag matches
		   // T0 with longest history so if hit that awesome
			
		   for(int iterator = 0; iterator < NUMTAGTABLES; iterator++)
		   {
			   
			   
				if(tagPred[iterator][indexTagPred[iterator]].tag == tag[iterator])
				{
				    primeBank = iterator;
				    break;
				}  
		   }      
				for(int iterator = primeBank + 1; iterator < NUMTAGTABLES; iterator++)
				{
				    if(tagPred[iterator][indexTagPred[iterator]].tag == tag[iterator])
				    {
				        altBank = iterator;
				        break;
				    }  
				}    
				
		   
		   
		if(primeBank < NUMTAGTABLES)
		{        
		   if(altBank == NUMTAGTABLES)
		   {
			   altPred = basePrediction;
		   }
		   else
		   {
			   if(tagPred[altBank][indexTagPred[altBank]].ctr >= TAGPRED_CTR_MAX/2)
				    altPred = TAKEN;
				else 
				    altPred = NOT_TAKEN;
		   }
			
			if((tagPred[primeBank][indexTagPred[primeBank]].ctr  != 3) ||(tagPred[primeBank][indexTagPred[primeBank]].ctr != 4 ) || (tagPred[primeBank][indexTagPred[primeBank]].usefulBits != 0) || (altBetterCount < 8))
			{
				if(tagPred[primeBank][indexTagPred[primeBank]].ctr >= TAGPRED_CTR_MAX/2)
				    primePred = TAKEN;
				else 
				    primePred = NOT_TAKEN;
				u.direction_prediction(primePred);
				return &u;
			}
			else
			{
				u.direction_prediction(altPred);
				return &u;
			}
		}
		else
		{
			altPred = basePrediction;
			u.direction_prediction(altPred);
			return &u;
		}
		return &u;
	}





	// ---------- End of Predict Function 

	// ------------------- Update Function 
	void TAGE_Update(branch_update *u, bool resolveDir, unsigned int branchTarget) {

				

		unsigned int PC = ((my_update*)u)->bi.address;
		
		bool predDir = u->direction_prediction();
		// --------------- Getting Data --------------------------------//
		
		//	nn_data.PC_Value = PC ; // PC Value Done ----------------------------------------------------
		nn_data.TAGE_MyPrediction = predDir ; // My Prediction value gotten ---------------------------------
		nn_data.TAGE_ActualPrediction = resolveDir ; //Actual Prediction ----------------------------
		
		// ----------------------------- New Code Added ----------------------------------// 
		CSV_input(nn_data) ; 
		// Resetting the values
		nn_data = { 0, 0 , 0} ; 
		// Please reset it to zero


		bool strong_old_present = false;
		bool new_entry = 0;    
		if (primeBank < NUMTAGTABLES)
		{
			// As per update policy
			// 1st update the useful counter
			if ((predDir != altPred))
			{
			
			if (predDir == resolveDir)
			{

			tagPred[primeBank][indexTagPred[primeBank]].usefulBits = SatIncrement(tagPred[primeBank][indexTagPred[primeBank]].usefulBits, BIMODAL_CTR_MAX);

			}
			else
			{
			tagPred[primeBank][indexTagPred[primeBank]].usefulBits = SatDecrement(tagPred[primeBank][indexTagPred[primeBank]].usefulBits);
			}

		}    
		 // 2nd update the counters which provided the prediction  
			if(resolveDir)
			{
				tagPred[primeBank][indexTagPred[primeBank]].ctr = SatIncrement(tagPred[primeBank][indexTagPred[primeBank]].ctr, TAGPRED_CTR_MAX);
			}
			else
			{
				tagPred[primeBank][indexTagPred[primeBank]].ctr = SatDecrement(tagPred[primeBank][indexTagPred[primeBank]].ctr);
			}
		}
		else
		{
			unsigned int bimodalIndex   = (PC) % (numBimodalEntries);
			if(resolveDir)
			{
				bimodal[bimodalIndex] = SatIncrement(bimodal[bimodalIndex], BIMODAL_CTR_MAX);
			}
			else
			{
				bimodal[bimodalIndex] = SatDecrement(bimodal[bimodalIndex]);
			}
		}
		// Check if the current Entry which gave the prediction is a newly allocated entry or not.
		if (primeBank < NUMTAGTABLES)
		{
			
			if((tagPred[primeBank][indexTagPred[primeBank]].usefulBits == 0) &&((tagPred[primeBank][indexTagPred[primeBank]].ctr  == 3) || (tagPred[primeBank][indexTagPred[primeBank]].ctr  == 4)))
				{
				    new_entry = true;

			if (primePred != altPred)
			  {
				if (altPred == resolveDir)
				  {
	// Alternate prediction more useful is a counter to be of 4 bits
				if (altBetterCount < 15)
				{  
				                altBetterCount++;
				            }    
				  }

				else if (altBetterCount > 0)
				{
				            altBetterCount--;
				        }
				    }
			}
		}


	// Proceeding to allocation of the entry.
		if((!new_entry) || (new_entry && (primePred != resolveDir)))
		{    
		if (((predDir != resolveDir) & (primeBank > 0)))
		  {
				        
			for (int i = 0; i < primeBank; i++)
			  {
				if (tagPred[i][indexTagPred[i]].usefulBits == 0);
				strong_old_present = true;

			  }
	// If no entry useful than decrease useful bits of all entries but do not allocate
			if (strong_old_present == false)
			{
			for (int i = primeBank - 1; i >= 0; i--)
			{
				tagPred[i][indexTagPred[i]].usefulBits--;
				    }
				}
			else
			  {

				    srand(time(NULL));
				    int randNo = rand() % 100;
				    int count = 0;
				    int bank_store[NUMTAGTABLES - 1] = {-1, -1, -1};
				    int matchBank = 0;
				    for (int i = 0; i < primeBank; i++)
				    {
				        if (tagPred[i][indexTagPred[i]].usefulBits == 0)
				        {
				            count++;
				            bank_store[i] = i;
				        }
				    }  
				    if(count == 1)
				    {
				        matchBank = bank_store[0];
				    }
				    else if(count > 1)
				    {
				         if(randNo > 33 && randNo <= 99)
				        {
				            matchBank = bank_store[(count-1)];
				        }
				        else
				        {
				            matchBank = bank_store[(count-2)];
				        }   
				    }


			for (int i = matchBank; i > -1; i--)
			{
				if ((tagPred[i][indexTagPred[i]].usefulBits == 0))
				  {
				            if(resolveDir)
				            {    
				                tagPred[i][indexTagPred[i]].ctr = 4;
				            }
				            else
				            {
				                tagPred[i][indexTagPred[i]].ctr = 3;
				            }    
				                tagPred[i][indexTagPred[i]].tag = tag[i];
				                tagPred[i][indexTagPred[i]].usefulBits = 0;
				break; // Only 1 entry allocated
				 }
				    }

			}

		}
		}    

		clock++;
		if(clock == (256*1024))
			{
				// reset clock
				clock = 0;
				if(clock_flip == 1)
				{
				    // this is the 1st time
				    clock_flip = 0;
				}
				else
				{
				    clock_flip = 1;
				}
			if(clock_flip == 1)
				{// MSB turn
				    for (int jj = 0; jj < NUMTAGTABLES; jj++)
				    {    
				        for (unsigned int ii = 0; ii < numTagPredEntries; ii++)
				        {
				            tagPred[jj][ii].usefulBits = tagPred[jj][ii].usefulBits & 1;
				        }
				    }
				}    
				else
				{// LSB turn
				    for (int jj = 0; jj < NUMTAGTABLES; jj++)
				       {    
				           for (unsigned int ii = 0; ii < numTagPredEntries; ii++)
				           {
				               tagPred[jj][ii].usefulBits = tagPred[jj][ii].usefulBits & 2;
				           }
				       }

			}

		}

		
	  // update the GHR
	  GHR = (GHR << 1);

	  if(resolveDir == TAKEN){
		GHR.set(0,1); 
	  }

		for (int i = 0; i < NUMTAGTABLES; i++)
		{
				    
				indexComp[i].updateCompHist(GHR);
				tagComp[0][i].updateCompHist(GHR);
				tagComp[1][i].updateCompHist(GHR);
				
		}
	  // PHR update is simple, jus take the last bit ??
		// Always Limited to 16 bits as per paper.
		PHR = (PHR << 1); 
		if(PC & 1)
		{
			PHR = PHR + 1;
		}
		PHR = (PHR & ((1 << 16) - 1));
	}

	// End of Update Function 


};