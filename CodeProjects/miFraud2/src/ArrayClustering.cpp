/*
 * Metodología de la Programación
 * Curso 2025/2026
 */

/**
 * @file ArrayClustering.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 22 de octubre de 2025, 11:57
 */

#include "ArrayClustering.h"



using namespace std;


void InitializeArrayClustering(ArrayClustering arrayClustering,const int capacity){
    
    if(capacity <= 0){
        throw out_of_range("capacity less than 0");
    }

    arrayClustering.clustering = new Clustering[capacity];
    arrayClustering.size = 0;
    arrayClustering.capacity = 0;
}


void DeallocateArrayClustering(ArrayClustering arrayClustering){
    delete[] arrayClustering.clustering; 
    arrayClustering.clustering = nullptr; 
    arrayClustering.capacity = 0; 
    arrayClustering.size = 0; 

}


//should i put const at the end of the funcitionws if they are not class functions
int FindArrayClustering(const ArrayClustering arrayClustering,const Clustering clustering) {
    int pos = -1; 
    for(int i = 0; i < arrayClustering.size; i++){ 
        if(arrayClustering.clustering[i].isEquivalentTo(clustering)){ 
            pos = i;  
        }
    }
    return pos;  
}



void AppendArrayClustering(ArrayClustering arrayClustering, Clustering clustering){

    if(!FindArrayClustering(arrayClustering, clustering)){
        if(arrayClustering.capacity < arrayClustering.size + 1){
            int oldCap = arrayClustering.capacity;
            Clustering* newone = new Clustering[arrayClustering.capacity + ARRAY_CLUSTERING_CAPACITY_INCREMENT];
            

            for(int i = 0; i < oldCap; i++){
                newone[i] = arrayClustering.clustering[i];
            }
            
            arrayClustering.capacity += ARRAY_CLUSTERING_CAPACITY_INCREMENT;
            delete[] arrayClustering.clustering;
            arrayClustering.clustering = newone;
            newone = nullptr;
        } else {
            //Cause it's 0 based we put the new one at exactly size
            arrayClustering.clustering[arrayClustering.size] = clustering; 
            arrayClustering.size++;
        }
    }
}


void SortArrayClustering(ArrayClustering ArrayClustering){
    
}