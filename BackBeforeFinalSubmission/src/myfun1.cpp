#include "nn.hpp"
#include <iostream>
#include <cassert>
#include <typeinfo>
using namespace std;



std::vector< int > chooser(vector<vector<int>>& vect) {
    std::vector< int > arr;
    machine_learning::neural_network::NeuralNetwork myNN ;
    myNN.load_model("myNN.model");
    for (int i = 0; i<vect.size(); ++i) {
            arr.push_back(machine_learning::argmax(myNN.single_predict({{vect[i][0],vect[i][1],vect[i][2]}})));
    }
    return arr;
}

int main(){
    std::vector< std::vector<int> > my_array = {{0,1,1}, {1,0,0}, {1,1,1},{0,1,1}, {1,0,0}, {1,1,1},{0,1,1}, {1,0,0}, {1,1,1},{0,1,1}, {1,0,0}, {1,1,1}};
    std::vector< int > arr = chooser(my_array);
    //cout << machine_learning::argmax(myNN.single_predict({{x[0][0],x[0][1],x[0][2]}}));
    // arr.push_back(machine_learning::argmax(myNN.single_predict({{x[0][0],x[0][1],x[0][2]}})));
    // cout << arr[0];
    for (int i = 0; i<arr.size(); ++i) {
            cout << arr[i];
    }
}