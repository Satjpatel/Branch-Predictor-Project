// my_predictor.h
// This file contains a sample my_predictor class.
// It has a simple 32,768-entry gshare with a history length of 15 and a
// simple direct-mapped branch target buffer for indirect branch prediction.
#define gs_PHT_SIZE 8192	//2^13
#define gs_PHT_MASK	0x1FFF  //13 bit address mask


//bimodal
#define bi_PHT_SIZE	4096 	//2^12
#define bi_PHT_MASK 0xFFF   //13 bit address mask

//choice
#define choice_SIZE	4096
#define choice_MASK	0xFFF	
//bool gsPredict = false;


class my_update : public branch_update {
public:
	unsigned int index;
	branch_info bi;
};

class my_predictor : public branch_predictor {
public:
	// insfrastructure data types
	my_update u;
	branch_info bi; 

	int gs_PHT[gs_PHT_SIZE];
	int gs_HISTORY;					//the history shift register
	int gs_index;
	int bi_PHT[bi_PHT_SIZE];
	int bi_index;
	bool biPredict = false;
	int CHOICE[choice_SIZE];
	bool gsPredict = false;			//prediction from gShare



	my_predictor (void){ 
		//all values initiated to 0
		//init gShare
		for(int i = 0; i < gs_PHT_SIZE; i++)
			gs_PHT[i] = 0;
		gs_HISTORY = 0;

		//init bimodal and gshare
		for(int i = 0; i < bi_PHT_SIZE; i++){
			bi_PHT[i] = 0;
			CHOICE[i] = 0;
		}
	}


	branch_update *predict (branch_info & b) {
		gsPredict = false;
		biPredict = false;
		u.bi = b;
		unsigned int pc = b.address;
		//gShare
		gs_index = gs_HISTORY ^ (pc & gs_PHT_MASK);
		if(gs_PHT[gs_index] > 1)		//for values 10 and 11 return true
			gsPredict = true;

		//biModal
		bi_index = pc & bi_PHT_MASK;
		if(bi_PHT[bi_index] > 1)		//for values 10 and 11 return true
			biPredict = true;

		//CHOICE
		if(CHOICE[gs_HISTORY & choice_MASK] > 1)
			u.direction_prediction(gsPredict);
		else
			u.direction_prediction(biPredict);
		return &u;
	
	}
	void update (branch_update *u, bool taken, unsigned int target) {
		//u.bi = b;
		unsigned int pc = ((my_update*)u)->bi.address;
		int outcome = target;
		//train gShare
		//if(outcome == true && gs_PHT[gs_index] < 3)		//saturate towards T 
		if(outcome == true && gs_PHT[gs_index] < 3)
			gs_PHT[gs_index]++;
		if(outcome == false && gs_PHT[gs_index] > 0)	//saturate towards NT
			gs_PHT[gs_index]--;

		//train biModal
		if(outcome == true && bi_PHT[bi_index] < 3)		//saturate towards T
			bi_PHT[bi_index]++;
		if(outcome == false && bi_PHT[bi_index] > 0)	//saturate towards NT
			bi_PHT[bi_index]--;


		//Train CHOICE only when the two predictors differ
		if(biPredict != gsPredict){
			if(gsPredict == outcome && CHOICE[gs_HISTORY & choice_MASK] < 3){
				//train chooser to choose GLOBAL
				CHOICE[gs_HISTORY & choice_MASK]++;
			} 
			else if(biPredict == outcome && CHOICE[gs_HISTORY & choice_MASK] > 0){
				//train chooser to choose LOCAL
				CHOICE[gs_HISTORY & choice_MASK]--;
			}
		}

		//updating the HISTORY register
		gs_HISTORY = gs_HISTORY << 1;
		gs_HISTORY = gs_HISTORY | int(outcome);
		gs_HISTORY = gs_HISTORY & gs_PHT_MASK;
	}

};
