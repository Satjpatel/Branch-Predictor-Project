#include "nn.hpp"
#include <iostream>
#include <cassert>
#include <typeinfo>
using namespace std;
/**
 * Function to test neural network
 * @returns none
 */
static void tr() {
    // Creating network with 3 layers for "iris.csv"
    machine_learning::neural_network::NeuralNetwork myNN =
        machine_learning::neural_network::NeuralNetwork({
            {3, "none"},  // First layer with 3 neurons and "none" as activation
            {6, "relu"},  // Second layer with 6 neurons and "relu" as activation
            {2, "sigmoid"}  // Third layer with 3 neurons and "sigmoid" as activation            
        });
    // Printing summary of model
    myNN.summary();
    // Training Model
    //myNN.fit_from_csv("iris.csv", true, 100, 0.3, false, 2, 32, true);
    myNN.fit_from_csv("trace_csvs/trace10.csv", true, 20, 0.3, false, 2, 32, true);
    myNN.fit_from_csv("trace_csvs/trace12.csv", true, 20, 0.3, false, 2, 32, true);
    myNN.fit_from_csv("trace_csvs/trace13.csv", true, 20, 0.3, false, 2, 32, true);
    myNN.fit_from_csv("trace_csvs/trace14.csv", true, 20, 0.3, false, 2, 32, true);
    myNN.fit_from_csv("trace_csvs/trace15.csv", true, 20, 0.3, false, 2, 32, true);
    myNN.save_model("myNN.model");
    // Testing predictions of models
    return;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    // Testing
    //tr();
    machine_learning::neural_network::NeuralNetwork myNN ;
    myNN.load_model("myNN.model");
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,1}})); // == 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,0,1}})); //== 1);
    cout << machine_learning::argmax(myNN.single_predict({{1,1,0}})); //== 0);
    cout << machine_learning::argmax(myNN.single_predict({{0,0,0}})); //== 0);
    // Create a function here which converts 0,1 to prediction 0 or predictor 1 and then get their current prediction adn then give that out
    // createa a function whichc just giuve 0 or 1
    return 0;
}
