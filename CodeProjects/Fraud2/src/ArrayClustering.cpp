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

/**
 * @brief Deallocates the dynamic array of Clustering objects in the provided
 * ArrayClustering. It also sets the clustering pointer to nullptr, and the
 * capacity and size fields to 0.
 * @param arrayClustering The ArrayClustering to deallocate. Output parameter
 */
void ArrayClustering::DeallocateArrayClustering(ArrayClustering arrayClustering){
    delete[] arrayClustering.clustering; 
    arrayClustering.clustering = nullptr; 
    arrayClustering.capacity = 0; 
    arrayClustering.size = 0; 

}

/**
 * @brief Searches for a given Clustering object in the provided
 * ArrayClustering. The search is performed by comparing each Clustering object
 * in the array with the provided Clustering object using the
 * Clustering::isEquivalentTo() method.
 * @param arrayClustering The ArrayClustering where to search will be 
 * performed. Input parameter
 * @param clustering The Clustering object to search for. Input parameter
 * @return The position of the Clustering object in the array if found;
 * -1 otherwise.
 */
int ArrayClustering::FindArrayClustering(ArrayClustering arrayClustering, Clustering clustering) {
    int pos = -1; 
    for(int i = 0; i < arrayClustering.size; i++){ // Iterate through the array of Clustering objects
        if(arrayClustering.clustering[i].isEquivalentTo(clustering)){ // If the current Clustering object is equivalent to the provided Clustering object
            pos = i;  
        }
    }
    return pos;  

                                         