// Code for 2BC-Gshare Predictor 
// Include the necessary header files here


// The class definition for this particular function 
// The entire predictor can be broken down into 3 simple parts 
/* 
    1. Initializing Function -- Used at the start only, to make all the history bits zero 
    2. Prediction Function -- Takes the PC value and gives us the prediction (going to take or not)
    3. Update Function -- Takes in the PC value, our prediction and the real predition to update the history tables 

*/
#define gs_PHT_SIZE 8192	//2^13
#define gs_PHT_MASK	0x1FFF  //13 bit address mask


//bimodal
#define bi_PHT_SIZE	4096 	//2^12
#define bi_PHT_MASK 0xFFF   //13 bit address mask

//choice
#define choice_SIZE	4096
#define choice_MASK	0xFFF	
//bool gsPredict = false;

class my_TwoBCGShare_P2 {
public: // Make sure everything you do is in public directory
    // You can add whatever parameters you want in these functions. 
	bool TwoBCGShare_Predict(){}
    void TwoBCGShare_Update(){}
	//my_update u;
	branch_info bi;

	int gs_PHT[gs_PHT_SIZE];
	int gs_HISTORY;					//the history shift register
	int gs_index;
	int bi_PHT[bi_PHT_SIZE];
	int bi_index;
	bool biPredict = false;
	int CHOICE[choice_SIZE];
	bool gsPredict = false;			//prediction from gShare

    void TwoBCGShare_Init(){
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

};
