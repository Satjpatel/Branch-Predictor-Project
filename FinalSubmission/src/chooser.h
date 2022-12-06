
#include "TwoBCGShare.h"
#include "nn.hpp" 
#include <cassert>
#include <typeinfo> 
#include <iostream> 
#include "TAGE.h"

bool NN_input [6] = { TAGE_NN, GSHARE_NN} ; 

// bool TAGE_Predict(uint32_t PC) ;
// bool TwoBCGShare_Predict (uint32_t PC) ; 

// void TAGE_Update(uint32_t pc, branch_update *u, bool taken, unsigned int target);
// void TwoBCGShare_Update(uint32_t pc, branch_update *u, bool taken, unsigned int target);

// To get the prediction from one or two
bool chooser_class(bool vect[]) {
    bool a;
    machine_learning::neural_network::NeuralNetwork myNN ;
    myNN.load_model("myNN.model");
    a = machine_learning::argmax(myNN.single_predict({{vect[0],vect[1],vect[2],vect[3],vect[4],vect[5]}}));
    return a;
}

class CHOOSER: public my_TAGE_P1, public my_TwoBCGShare_P2{

    public:

        bool GetPrediction(uint32_t PC); // Give you the prediction
        void GetUpdate(uint32_t pc, branch_update * u, bool taken, unsigned int target); // This will update the history of both predictors after prediction 

        // Constructor to initialize TAGE and TwoBCGSHARE
        CHOOSER(void){  // Constructor --> initializing all the values to zero

        TAGE_Init() ;

        TwoBCGShare_Init();

        }

};

//Give Kathan --> A array/structure --< { Our Prediction | History {From 1 to 4}}

bool CHOOSER::GetPrediction(uint32_t PC){
   // printf("I am in Getpredict\n");
if((chooser_class(NN_input))==0) 

    return TAGE_Predict(PC) ;
else 
    return TwoBCGShare_Predict (PC) ;
  
}

// The Update Function 

void CHOOSER::GetUpdate(uint32_t pc, branch_update *u, bool taken, unsigned int target){

    
    TAGE_Update(pc, u, taken, target);
    
    (pc, u, taken, target);
}

