#include "TAGE.h"
#include "TwoBCGShare.h"


class CHOOSER: public my_TAGE_P1, public my_TwoBCGShare_P2{

    public:

        bool GetPrediction(uint32_t PC); // Give you the prediction
        void GetUpdate(branch_update * u, bool taken, unsigned int target); // This will update the history of both predictors after prediction 

        // Constructor to initialize TAGE and TwoBCGSHARE
        CHOOSER(void){  // Constructor --> initializing all the values to zero

        TAGE_Init() ;

        TwoBCGShare_Init();

        }

};

//Give Kathan --> A array/structure --< { Our Prediction | History {From 1 to 4}}

bool GetPrediction(uint32_t PC){

// Accorting to Neural Network, you can add whatever code you wanna add 
/*
    Eg: 
    if(Class0) 
       return TAGE_Predict() ; 
    else
       return 2BCGShare_Predict() ; 
*/

    //TagePredict();
    //GsharePredict();
    return 0;
}

// The Update Function 

void GetUpdate(branch_update * u, bool taken, unsigned int target){

    
    //TageUpdate();
    //GshareUpdate();
}

