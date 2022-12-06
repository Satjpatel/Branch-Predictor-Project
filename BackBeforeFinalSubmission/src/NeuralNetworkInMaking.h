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
void firstlayerNN (bool inputlayer [2], double outputlayer [3]) 
{ 
     //Defining the associated weights 
     double weights [2][3] = { {0.25, -0.2, 0.66},
                               {1.655, -0.5, 0.8} } ; 
    //outputlayer[3] = {0,0,0} ; 
    for (int i = 0 ; i < 2 ; i++) 
    { 
        for (int j = 0 ; j < 3 ; j++ )
        { 
            outputlayer[j] = outputlayer[j] + (inputlayer[i]*weights[i][j]) ;  
        }
    }

} 



void secondlayerNN (double secondlayer [3], double outputlayer [2])
{ 
        double weights [3][2] = { {1,5},{4,2},{-1,3} } ; 
        for (int i = 0 ; i < 3 ; i++) 
        { 
            for (int j = 0 ; j < 2 ; j++) 
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
    
    double outputlayer [3] = {0.0, 0.0,0.0} ; 
    firstlayerNN(layer1, outputlayer) ; 
   // cout<<outputlayer[0]<<" "<<outputlayer[1]<<" "<<outputlayer[2]<<" "<<endl ; 
    double outputlayer_d [2] = {0, 0} ; 
    secondlayerNN(outputlayer, outputlayer_d) ; 
   // cout<<outputlayer_d[0]<<" "<<outputlayer_d[1]<<endl ; 
    cout<<sigmoid(outputlayer_d[0])<<" "<<sigmoid(outputlayer_d[1])<<endl ; 
     //   cout<<relu(outputlayer_d[0])<<" "<<relu(outputlayer_d[1])<<endl ; 
    if(sigmoid(outputlayer_d[0]) > sigmoid(outputlayer_d[1]))
        return 1 ; 
    else 
        return 0 ; 
}