

// my_predictor.h
// This file contains a sample my_predictor class.
// It has a simple 32,768-entry gshare with a history length of 15 and a
// simple direct-mapped branch target buffer for indirect branch prediction.
#include<inttypes.h>
#include "chooser.h"

CHOOSER *mypred = new CHOOSER();

class my_predictor : public branch_predictor {
public:

	branch_update u;
	branch_info bi;
	bool pred_taken;

	branch_update *predict (branch_info & b) {
		bi = b;
		uint32_t PC = bi.address;

		if (b.br_flags & BR_CONDITIONAL) {
			//	printf("I am in predict\n");
		    pred_taken = mypred->GetPrediction(PC);
		//
		//	printf("I am in predict pred_taken =%d\n",pred_taken);

        }
		 u.direction_prediction (pred_taken); // We get the final prediction here
         u.target_prediction (0);
		return &u;
	}

	void update (branch_update *u, bool taken, unsigned int target) {

		uint32_t pc = bi.address;
		if (bi.br_flags & BR_CONDITIONAL) {
			mypred->GetUpdate(pc, u, u->direction_prediction() , u->target_prediction()); // We get the updating information here
	}
    }
};
