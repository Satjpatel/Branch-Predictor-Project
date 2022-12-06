#include "math.h" 
#include <iostream>
using namespace std ; 

// Making the sigmoid function 
double sigmoid (double input) 
{ 
    double output ; 
    output =  1 / (1 + exp(-input)); 
    return output ; 
}

// Making the Relu Function 
double relu (double input) 
{ 
  if (input > 0)
    return input ; 
 else 
    return 0 ; 

}

// The first layer -- Layer 1 finally fucking done!
void firstlayerNN (bool inputlayer [6], double outputlayer [10]) 
{ 
     //Defining the associated weights 
     double weights [6][10] = 
                               {{ 1.03771, 1.05141, -2.53826, 0.967054, 1.23107, -0.544472, -0.613356, 3.45243, 1.03331, 0.431325} , 
                              {-0.715414, -1.30371, -1.48959, -0.491139, 0.774393, 0.273992, -0.0906533, 0.547265, -0.390901, -0.331363 },
                              {-1.8012, 0.612633, -2.73455, -0.76156, 0.662468, 0.917697, 0.577668, 0.544088, -0.401883, 0.198642}, 
                              {0.0429792, -1.21022, -0.611571, -0.202868, -1.92372, -0.424857, 0.119608, -1.97287, 0.313581, -0.86368 } ,
                              {-0.142333, -0.46296, -0.152657, 0.147016, -2.77401, 0.050679, 0.841656, -4.94449, 0.460228 , -1.679 },
                              {0.108511, -1.59118, -0.201753, -0.985442, -2.41751, 0.483254, 0.142548, -2.86905, 0.14229, -0.00877508 }} ;  
    //outputlayer[3] = {0,0,0} ; 
    for (int i = 0 ; i < 6 ; i++) 
    { 
        for (int j = 0 ; j < 10 ; j++ )
        { 
            outputlayer[j] = outputlayer[j] + (inputlayer[i]*weights[i][j]) ;  
        }
    }

} 



void secondlayerNN (double secondlayer [10], double outputlayer [1])
{ 
        double weights [10][1] = {0.0990072, 
            -2.19366,
            2.75566,
            -3.25397,
            1.35886 , 
            1.78648,
            -1.18538,
            -0.201101,
            4.83047,
            0.738846 } ; 
        for (int i = 0 ; i < 10 ; i++) 
        { 
            for (int j = 0 ; j < 1 ; j++) 
            { 
                outputlayer[j] = outputlayer[j] + (secondlayer[i]*weights[i][j]) ; 
            }
        }
}

// The first layer
// double firstlayerNN (double input [2], double weights [2][3]) 
// { 

// } 

bool NN_output(bool layer1[2]) 
{ // int layer1[2] = {0,1} ; 
   //double weigths [2][3] = { {3, -0.5, 2.0}, 
                                //    {3, -0.5, 2.0},} ; 
    //cout<<weigths[1][1]<<endl<<weigths[1][0]<<endl ; 
    
    double middlelayer_in [10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} ; 
    firstlayerNN(layer1, middlelayer_in) ; 
    
    double middlelayer [10] ;
    for (int i = 0 ; i < 10 ; i++){ 
        middlelayer[i] = relu(middlelayer_in[i]) ; 
    }


    double outputlayer_d [1] = {0} ; 
    secondlayerNN(middlelayer, outputlayer_d) ; 

    double outputlayer [1] ; 
    for (int j = 0 ; j < 1 ; j++) 
    { 
        outputlayer[j] = sigmoid(outputlayer_d[j]); 
    }

   // cout<<sigmoid(outputlayer_d[0])<<" "<<sigmoid(outputlayer_d[1])<<endl ; 
     //   cout<<relu(outputlayer_d[0])<<" "<<relu(outputlayer_d[1])<<endl ; 
    if(outputlayer[0]>0.9)
        return 0 ; 
    else 
        return 1 ; 
}

//Second price auction --> Third Price Auction 