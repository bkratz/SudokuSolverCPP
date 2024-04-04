#include "SudokuSolverJNI.h"
#include <sudokusolver.h>

JNIEXPORT jintArray JNICALL Java_de_birgitkratz_sudokusolver_jni_SudokuSolverJNI_solveSudoku
        (JNIEnv *env, jobject obj, jobjectArray input) {

    // read input array sizes from JNI environment
    jsize outerArrayLength = env->GetArrayLength(input);
    auto inner = (jobjectArray)(env->GetObjectArrayElement(input, 0));
    jsize innerArrayLength = env->GetArrayLength(inner);

    // delete local reference
    env->DeleteLocalRef(inner);

    jsize arraySize = outerArrayLength * innerArrayLength;

    // input array for parameter "a" in SudokuSolver struct
    uint8_t structParameterAInput[arraySize];

    // fill it with data by reading from JNI environment
    for (int i=0; i < outerArrayLength; i++) {
        auto innerArray = (jintArray )env->GetObjectArrayElement(input, i);
        jint *innerArrayElements = env->GetIntArrayElements(innerArray, nullptr);
        for (int j=0; j < innerArrayLength; j++) {
            structParameterAInput[i * innerArrayLength + j] = innerArrayElements[j];
        }

        // releasing elements and delete local reference
        env->ReleaseIntArrayElements(innerArray, innerArrayElements, 0);
        env->DeleteLocalRef(innerArray);
    }

    // create and fill SudokuSolver struct
    Sudoku s = {structParameterAInput, 9, 3};

    // call the SudokuSolver
    solve(&s);

    // create the array holding the result, allocate memory
    // has to be of type 'jint', since a jintArray will be returned
    jint resultArrayElements[arraySize];

    // fill the result array
    for (int k=0; k < arraySize; k++) {
        resultArrayElements[k] = (jint) structParameterAInput[k];
    }

    // create a new result array on Java-Heap, allocate memory
    jintArray resultArray = env->NewIntArray(arraySize);

    // copy the result array Java-Heap
    env->SetIntArrayRegion(resultArray, 0, arraySize, resultArrayElements);

    // return result
    return resultArray;
}
