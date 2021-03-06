#include<iostream>
#include<cstdlib>
#include<numeric>
#include<sstream>
#include<cmath>


std::vector<int> GenerateRandeVec(int numOfNums, int min, int max);

int main(){
    //std::vector<int> vecVals = GenerateRandeVec(10,1,50);
    //for(auto x: vecVals)
    //    std::cout<<x<<"\n";
    //std::cout<<" "<<"\n\n";
    std::vector<int> evenVecVals;
    std::copy_if(vecVals.begin(),vecVals.end(),std::back_inserter(evenVecVals),[](int x){return (x % 2)==0;});		//using the function “copy_if” to select only “even values”
    for(auto x: evenVecVals)
        std::cout<<x<<"\n";
    std::for_each(vecVals.begin(), vecVals.end(),
        [&](int x){sum += x;});			//
    std::cout<< "Sum: " <<sum<<"\n";	//using a sum of all elements 
    return 0;
}

std::vector<int> GenerateRandeVec(int numOfNums, int min, int max){
    std::vector<int> vecValues;
    srand(time(NULL));
    int i = 0, randVal = 0;
    while(i < numOfNums){
        randVal = min + std::rand()%((max + 1) -min);
        vecValues.push_back(randVal);
        i++;
    }
    return vecValues;
}