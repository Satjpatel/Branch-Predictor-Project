// Code for 2BC-Gshare Predictor 
// Include the necessary header files here


// The class definition for this particular function 
// The entire predictor can be broken down into 3 simple parts 
/* 
    1. Initializing Function -- Used at the start only, to make all the history bits zero 
    2. Prediction Function -- Takes the PC value and gives us the prediction (going to take or not)
    3. Update Function -- Takes in the PC value, our prediction and the real predition to update the history tables 

*/

class my_TwoBCGShare_P2 {
public: // Make sure everything you do is in public directory
    // You can add whatever parameters you want in these functions. 
    void TwoBCGShare_Init(); 


    bool TwoBCGShare_Predict();
    
    void TwoBCGShare_Update();

};
