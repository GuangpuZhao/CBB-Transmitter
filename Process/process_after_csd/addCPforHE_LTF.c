#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "../../headers/commonStructure.h"
#include "../../headers/globalVarINIT.h"
#include "../../headers/process.h"


void addCPforHELTF(complex32 **X_VHTLTF, complex32 **IDFT_X_VHTLTF){
    const int N_LTF = (!(N_STS&(N_STS-1)))?N_STS:(N_STS+1);
    const int CpLen = CpDuration*SampRate;
    const int SymbLen = SymbDuration*SampRate;
    int i,j;

    /*complex32 *tmp = (complex32 *)malloc((SymbLen+CpLen)*sizeof(complex32));
    MKSUREENMEM(tmp);
    memset(tmp,0,(SymbLen+CpLen)*sizeof(complex32));*/
    complex32 *src_addr;
    complex32 *dest_addr;
    for(i=0; i<N_STS; i++){
        for(j=0; j<N_LTF; j++){
            src_addr = IDFT_X_VHTLTF[i]+j*SymbLen+SymbLen-CpLen;
            dest_addr = X_VHTLTF[i]+j*(SymbLen+CpLen);
            memcpy(dest_addr, src_addr, CpLen*sizeof(complex32));

            src_addr = IDFT_X_VHTLTF[i]+j*SymbLen;
            dest_addr = X_VHTLTF[i]+j*(SymbLen+CpLen)+CpLen;
            memcpy(dest_addr, src_addr, SymbLen*sizeof(complex32));
        }
    }

}
