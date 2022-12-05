//size definitions
#define gs_PHT_SIZE 8192	//2^13
#define gs_PHT_MASK	0x1FFF  //13 bit address mask


//bimodal
#define bi_PHT_SIZE	4096 	//2^12
#define bi_PHT_MASK 0xFFF   //13 bit address mask

//Meta chooser
#define choice_SIZE	4096
#define choice_MASK	0xFFF	

class my_TwoBCGShare_P2 {
public: // Make sure everything you do is in public directory
    // You can add whatever parameters you want in these functions. 
	branch_info bi;
	//Declare tables 
	int gs_PHT[gs_PHT_SIZE];
	int gs_HISTORY;					//the history shift register
	int gs_index;
	int bi_PHT[bi_PHT_SIZE];
	int bi_index;
	bool biPredict = false;
	int CHOICE[choice_SIZE];
	bool gsPredict = false;			//prediction from gShare

    void TwoBCGShare_Init(){
        //Initialize with all values to 0
		//gshare
		for(int i = 0; i < gs_PHT_SIZE; i++)
			gs_PHT[i] = 0;
		gs_HISTORY = 0;

		//bimodal
		for(int i = 0; i < bi_PHT_SIZE; i++){
			bi_PHT[i] = 0;
			CHOICE[i] = 0;
		}
    }
	bool TwoBCGShare_Predict(branch_info & b){
		gsPredict = false;
		biPredict = false;
		u.bi = b;
		unsigned int pc = b.address;
		//gshare index using xor
		gs_index = gs_HISTORY ^ (pc & gs_PHT_MASK);
		//return true if values are greater than 1 (10 and 11)
		if(gs_PHT[gs_index] > 1)		
			gsPredict = true;

		//biModal index using pc
		bi_index = pc & bi_PHT_MASK;
		if(bi_PHT[bi_index] > 1)
			biPredict = true;

		// if chooser is 10 or 11 then choose gshare, else choose bimodal prediction 
		if(CHOICE[gs_HISTORY & choice_MASK] > 1){
			u.direction_prediction(gsPredict);
		}
		else{
			u.direction_prediction(biPredict);
		}
		return &u;


	}
    void TwoBCGShare_Update(branch_update *u, bool taken, unsigned int target){
		unsigned int pc = ((my_update*)u)->bi.address;
		bool predDir = u->direction_prediction();
		bool outcome = (taken == predDir);
		bool outcomeB = (biPredict==taken);
		bool outcomeG = (gsPredict==taken);
		//train gshare
		//Increment or decrement saturated counter depending on if prediction was correct or not 
		if(outcome == true && gs_PHT[gs_index] < 3){	
			gs_PHT[gs_index]++;
		}
		if(outcome == false && gs_PHT[gs_index] > 0){
			gs_PHT[gs_index]--;
		}

		//train biModal
		//Increment or decrement saturated counter depending on if prediction was correct or not 
		if(outcome == true && bi_PHT[bi_index] < 3){		
			bi_PHT[bi_index]++;
		}
		if(outcome == false && bi_PHT[bi_index] > 0){	
			bi_PHT[bi_index]--;
		}


		//Train chooser only when the two predictions are different
		if(biPredict != gsPredict){
			if(outcomeG == true && CHOICE[gs_HISTORY & choice_MASK] < 3){
				//train chooser to choose gshare
				CHOICE[gs_HISTORY & choice_MASK]++;
			} 
			else if(outcomeB == true && CHOICE[gs_HISTORY & choice_MASK] > 0){
				//train chooser to choose bimodal
				CHOICE[gs_HISTORY & choice_MASK]--;
			}
		}

		//update history register
		gs_HISTORY = gs_HISTORY << 1;
		gs_HISTORY = gs_HISTORY | int(outcome);
		gs_HISTORY = gs_HISTORY & gs_PHT_MASK;
		


	}

};
