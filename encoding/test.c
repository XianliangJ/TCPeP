#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "structures.h"
#include "galois_field.h"
#include "matrix.h"

#define true 1==1
#define false 1==0

int galoisTest(){
    uint8_t a,b,c;
    int isOk = true;
    
    // Addition :
    a = 0x01; b = 0x0A; c = 0x0B;
    if((gadd(a,b) != c)){
        printf("Galois addition failed\n");
        isOk = false;
    }
    
    // Multiplication :
    if((gmul(a,b) != b) || (gmul(0x02, 0x02)!=0x04)){
        printf("Galois multiplication failed\n");
        isOk = false;
    }
    
    // Division :
    if((gdiv(b,a) != b) || (gdiv(0x02, 0x02)!=0x01)){
        printf("Galois division failed\n");
        isOk = false;
    }
    
    return isOk;
}

int matrixTest(){
    int isOk = true;
    matrix* a, *b, *identity, *result;
    
    // Create & Destroy Matrices
    a = getRandomMatrix(1000,1000);
    b = getRandomMatrix(1000,1000);
    mfree(a);
    mfree(b);
    
    
    // Gaussian elimination
    a = getRandomMatrix(4, 4);
    identity = getIdentityMatrix(4);
    b = mgauss(*a);
    result = mmul(*a, *b);
    
    if(!mEqual(*identity, *result)){
        printf("matrix gauss or multiplication failed\n");
        isOk = false;
    }
    
    mfree(a);mfree(b);mfree(identity);mfree(result);
    
    return isOk;
}


int main(int argc, char **argv){    
    if(galoisTest() && matrixTest()){
        printf("All test passed.\n");
        return 0;
    } else {
        printf("Testing failed.\n");
        return -1;
    }
}