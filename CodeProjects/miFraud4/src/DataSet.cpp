/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file DataSet.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 30 de julio de 2025, 10:00
 */

#include <string>
#include <iostream>
#include <cmath>
#include <stdexcept>

#include "DataSet.h"
#include "VectorLocation.h"
#include "VectorInt.h"

using namespace std;

const string DataSet::MAGIC_STRING_T="MP-FRAUD_DATASET-T-1.0";

std::string DataSet::toString() const {
    string result;
    
    result += _locations.toString();
    result += _labels.toString();
    if (_nLocations > 0) {
        for (int instance = 0; instance < getNumInstances(); instance++) {
            for (int location = 0; location < getNumLocations(); location++) {
                result += to_string(this->getValue(instance, location));
                if (location < getNumLocations() - 1) {
                    result += " ";
                }
            }
            result += "\n";
        }
    }
    return result;
}


DataSet::DataSet(int nInstances, int nLocations){
    //for ** do the nInstances
    //and * for the nLocations


    _values = new int*[nInstances];
    for(int i = 0; i < nInstances; i++){
        _values[i] = new int[nLocations];
        
        for(int j = 0; j < nLocations; j++){
            _values[i][j] = 0;
        }
    }

    /*
    //They are already started so i cannot use any of the constructors
    //Can use resize tho which i already have, so it's 0 sized by default bcuz of the default constructor
    _labels.resize(nInstances);
    _locations.resize(nLocations);
    //they are initialized with a capacity of 0 so nInstances is how much it should grow directly it cannot go lower than that
    //even tho .getCapacity - nWhatever it is a catastrophic idea to do it in this stuation 
    */

    _labels = VectorInt(nInstances);//use assignment which is better as we create the one we want and change all of it's values correctly
    _locations = VectorLocation(nLocations);

    
    _nInstances= nInstances;
    _nLocations = nLocations;
}


DataSet::DataSet(const DataSet &orig){
    
    int** temp = new int*[orig._nInstances];
    for(int i = 0; i < orig._nInstances; i++){
        temp[i] = new int[orig._nLocations];
        for(int j = 0; j < orig._nLocations; j++){
            temp[i][j] = orig._values[i][j];
        }
    }

    _values = temp;

    _nInstances=orig._nInstances;
    _nLocations=orig._nLocations;

    //we need to copy the labels and locations we have the = operator at our disposal
    _labels = orig._labels;
    _locations = orig._locations;
}

DataSet::~DataSet(){
    //need to delete the dyn memory of the columns before the rows
    
    for(int i = 0; i < _nInstances; i++){
        delete[] _values[i];
        //Don't get this line try to get it explained
    }
    delete[] _values;
}


DataSet& DataSet::operator=(const DataSet &orig){

    if(this != &orig){
        
        for(int i = 0; i < _nInstances; i++){
            delete[] _values[i];
        }
        delete[] _values;

        _values = new int*[orig._nInstances];
        for(int i = 0; i < orig._nInstances; i++){
            _values[i] = new int[orig._nLocations];
        }
        
        //After identical size creation assignment is needed
        for(int i = 0; i < orig._nInstances; i++){
            for(int j = 0; j < orig._nLocations; j++){
                _values[i][j] = orig._values[i][j];
            }
        }

        _nInstances = orig._nInstances;
        _nLocations = orig._nLocations;
        //use the already existing = when doable
        _labels = orig._labels;
        _locations = orig._locations;
    }
    return *(this);
}

int DataSet::getNumInstances() const{
    return _nInstances;
}

int DataSet::getNumLocations() const{
    return _nLocations;
}

int DataSet::getValue(int instanceIndex, int locationIndex) const{
    if(instanceIndex < 0 || instanceIndex >= _nInstances || locationIndex < 0 || locationIndex >= _nLocations){
        throw out_of_range(" not valid positions");
    }
    return _values[instanceIndex][locationIndex];
}

int DataSet::getLabel(int instanceIndex) const{
    if(instanceIndex < 0 || instanceIndex >= _nInstances){
        throw out_of_range(" not valid pos");
    }
    return _labels.at(instanceIndex);
}

const VectorLocation& DataSet::getVectorLocation() const{
    return _locations; //no *() because they're not pointers like with this theyre objects by themselves unless i wanna do *(&)
}


const VectorInt& DataSet::getVectorLabels() const{
    return _labels;
}


void DataSet::setValue(int instanceIndex, int locationIndex, int value){
    if(instanceIndex < 0 || instanceIndex >= _nInstances || locationIndex < 0 || locationIndex >= _nLocations){
        throw out_of_range(" not valid positions");
    }

    _values[instanceIndex][locationIndex] = value;
}


void DataSet::setLabel(int instanceIndex, int label){
    //not mentiones byt it must want an exception for an out of range instanceINDEX
    //IF NOT REMOVE ASAP
    //no checking cause at does it by itself and i was trying to do check < 0 which makes sense but at does that already 
    //And >= _nInstances which ain't it

    _labels.at(instanceIndex) = label;
}

void DataSet::initInstances(int value){
    for(int i = 0; i < _nInstances; i++){
        for(int j = 0; j < _nLocations; j++){
            _values[i][j] = value;
        }
    }
}

void DataSet::clear(){
    for(int i = 0; i < _nInstances; i++){
        delete[] _values[i];
    }
    delete[] _values;
    _values = nullptr; 
    //i have to clear it bcuz if i don't i simply have no way of knowing the rows and columns it had 
    //and because to remove the columns for each row i have to do a  delete[] _values[i];
    //if i lost the number of rows that is nInstances i have no way of knowing

    //use the included clears for easiness 
    _locations.clear();
    _labels.clear();
    _nInstances = _nLocations = 0;
}

void DataSet::save(const std::string& fileName){ //do ts one next
    ofstream outputter; //output file stream

    
    outputter.open(fileName); //i suppose that to output it must be inside miFraud3
    if (!outputter.is_open()) {
        throw std::ios_base::failure("couldn't open it");
    }
    
 

    outputter << MAGIC_STRING_T << endl;
    
    //Execute to string to print everything about the dataset
    outputter<< toString() << endl;
    if (outputter.fail()) {
        throw std::ios_base::failure("couldn't write");
    }
    outputter.close();
}


void DataSet::load(const std::string& fileName){

   
    clear();

    
    ifstream inputted(fileName);
    if (!inputted.is_open()) {
        throw std::ios_base::failure("Cannot open file: " + fileName);
    }
    
    
    string currLine;
    getline(inputted, currLine);
    if (currLine != MAGIC_STRING_T){
        clear(); 
        throw invalid_argument("no match of magic string");
    }
    
    //when a line is read inputted only "has available" the lines after the read one
    _locations.load(inputted);
    //because it reads the first line which is the num of locations it knows when to stop loading
    _nLocations = _locations.getSize();


    inputted >> _nInstances;
    if (_nInstances < 0 || _nLocations < 0) {
        clear();
        throw out_of_range("instances/locations cannot be negative");
    }
    
    
    for(int i = 0; i <_nInstances; i++){
        int tempLabel;
        inputted >> tempLabel; //The >> allows us to read things with spaces automatically changes to the next line after it finishes
        _labels.append(tempLabel);
    }
    

    _values = new int*[_nInstances];
    for(int i = 0; i < _nInstances; i++){
        _values[i] = new int[_nLocations];
    }

    for(int i = 0; i < _nInstances; i++){
        for(int j = 0; j < _nLocations; j++){
            inputted >> _values[i][j];
        }
    }
}


DataSet DataSet::getReducedDataSet(const Clustering& clustering) const{
    if(clustering.isDone() == false){
        throw invalid_argument("nothing was done w it");
    }

    if(clustering.getNumLocations() != _nLocations){
        throw invalid_argument("mismatch of loc num");
    }

    // The returned DataSet has K columns (number of clusters)
    DataSet toRet(_nInstances, clustering.getK());

    for(int i = 0; i < _nInstances; i++){ // For each instance (row)
        for(int j = 0; j < _nLocations; j++){ // For each original location (column)
            int cluster = clustering.clusterOf(j); // Get the cluster for this location
            toRet._values[i][cluster] += _values[i][j]; // Sum into the new cluster column
        }
    }


    //copy vector centroids and locations
    toRet._labels = VectorInt(_labels); //it modifies stuff but not
    toRet._locations = VectorLocation(clustering.getCentroids());


    
    return toRet;
}


int DataSet::nearestInstance(const VectorInt &instance,const bool selected[]) const{

    if (instance.getSize() != _nLocations){
        throw invalid_argument("diff size");
    }

    int smallestPos = -1;
    double smallestTot = 0.0, current = 0.0;
    
    bool firstDone = false;
    for(int i = 0; i < _nInstances; i++){
        if(!selected[i]){
            if (!firstDone){
                firstDone=true;
                smallestPos = i;
                smallestTot = 0.0;
                for (int j = 0; j < _nLocations; j++){
                    double diff = instance.at(j) - _values[i][j];
                    smallestTot += diff * diff;
                }
            } else {


                current = 0.0;
                for (int j = 0; j < _nLocations; j++){
                    double diff = instance.at(j) - _values[i][j];
                    current += diff * diff;
                }
                if (current < smallestTot){
                    smallestTot = current;
                    smallestPos=i;
                }
            }
        }       
    }
    return smallestPos;
}

//i think it's like this not sure tho
const int& DataSet::operator()(int instanceIndex, int locationIndex) const{

    return _values[instanceIndex][locationIndex];
}

int& DataSet::operator()(int instanceIndex, int locationIndex){
    
    return _values[instanceIndex][locationIndex];
}

std::ostream& operator<<(std::ostream &os, const DataSet& dataset){

    os << dataset.toString(); 
    return os;
}


std::istream& operator>>(std::istream& is, DataSet &dataset){
    dataset.clear();
    try {
        dataset._locations.load(is);
        dataset._nLocations = dataset._locations.getSize();

        is >> dataset._nInstances;
        if (dataset._nInstances < 0 || dataset._nLocations < 0) {
            throw out_of_range("instances/locations cannot be negative");
        }

        dataset._labels.clear();
        for (int i = 0; i < dataset._nInstances; i++) {
            int tempLabel;
            is >> tempLabel;
            dataset._labels.append(tempLabel);
        }

        dataset._values = new int*[dataset._nInstances];
        for (int i = 0; i < dataset._nInstances; i++) {
            dataset._values[i] = new int[dataset._nLocations];
        }

        for (int i = 0; i < dataset._nInstances; i++) {
            for (int j = 0; j < dataset._nLocations; j++) {
                is >> dataset._values[i][j];
            }
        }
    } catch (...) {
        dataset.clear();
        throw;
    }

    return is;

}


void classify(const DataSet& datasetModel, DataSet &datasetToClassify, int K1, int K2, bool doReductionDimensionality){

    if (datasetModel.getNumLocations() != datasetToClassify.getNumLocations()){
        throw invalid_argument("diff locs");
    }
    if (doReductionDimensionality && K1 <= 0){
        throw invalid_argument("k1 menor q 0");
    }
    if (K2 < 1){
        throw invalid_argument("K2 menor q 1");
    }
    if (K2 > datasetModel.getNumInstances()){
        throw invalid_argument("K2 mayor q num instancias");
    }

    DataSet modelData(datasetModel);
    DataSet toClassifyData(datasetToClassify);

    if (doReductionDimensionality){
        Clustering clusterer;
        clusterer.set(modelData.getVectorLocation(), K1);
        clusterer.run();

        modelData = modelData.getReducedDataSet(clusterer);
        toClassifyData = toClassifyData.getReducedDataSet(clusterer);
    }

    for (int row = 0; row < toClassifyData.getNumInstances(); row++){
        int v0 = 0;
        int v1 = 0;



        VectorInt instanceVec(toClassifyData.getNumLocations());
        for (int col = 0; col < toClassifyData.getNumLocations(); col++){
            instanceVec.at(col) = toClassifyData.getValue(row, col);
        }

        bool* selected = new bool[modelData.getNumInstances()];
        for (int i = 0; i < modelData.getNumInstances(); i++){
            selected[i] = false;
        }



        
        for (int k = 0; k < K2; k++){
            int nearest = modelData.nearestInstance(instanceVec, selected);
            if (nearest == -1){
                k=K2;
                continue;
            }
            selected[nearest] = true;
            if (modelData.getLabel(nearest) == 1){
                v1++;
            } else {
                v0++;
            }
        }

        delete[] selected;

        if (v0 >= v1){
            datasetToClassify.setLabel(row, 0);
        } else {
            datasetToClassify.setLabel(row, 1);
        }
    }

}