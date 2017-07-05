#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "../../headers/process_data.h"
#include "../../headers/globalVarINIT.h"
#include "../../headers/commonStructure.h"

void add_window(complex32 *in, complex32 *reg_in, complex32 *reg_out, complex32 *out){
     int N_TR=3;
     int N_TR_half=1;
     int SymLen=640;
     int CpLen=128;

     complex32 *in_temp=(complex32 *)malloc((SymLen+3)*sizeof(complex32));
     memcpy(in_temp, in+(SymLen-CpLen-N_TR_half-1), 2*sizeof(complex32));
     memcpy(in_temp+2, in, SymLen*sizeof(complex32));
     memcpy(in_temp+(2+SymLen), in+(CpLen), 1*sizeof(complex32));

     memcpy(reg_out, in_temp+SymLen+3-N_TR, N_TR*sizeof(complex32));
     memcpy(out, in_temp, SymLen*sizeof(complex32));

     //add Window
     int WT[3]={1200,4096,6992};
     int i;
     for(i=0;i<3;i++){
        int32 real=in_temp[i].real*WT[i]+reg_in[i].real*WT[2-i];
        int32 imag=in_temp[i].imag*WT[i]+reg_in[i].imag*WT[2-i];
        out[i].real=real>>dotscale;
        out[i].imag=imag>>dotscale;
     }
     free(in_temp);
}

void add_window_for_he(complex32 **X_VHTLTF, complex32 *trans_data, complex32 window_buf[N_TX][3], complex32 **out){
    int N_CBPS, N_SYM, ScrLength, valid_bits;
    GenInit(&N_CBPS, &N_SYM, &ScrLength, &valid_bits);
    int SymbLen = SymbDuration*SampRate;
    int CpLen = CpDuration*SampRate;
    int DftSize = SampRate/(Band/4)*subcar;
    int n_ltf=(!(N_TX&(N_TX-1)))?N_TX:(N_TX+1);
    //int Ntx=N_STS;
    int Len= N_SYM*(CpLen+DftSize)+(SymbLen+CpLen)*n_ltf;
    int n_sym=N_STS+N_SYM;
    int SymLen = Len/n_sym;

    complex32 *in[N_TX];
    int i;
    for(i=0;i<N_TX;i++){
        in[i]=(complex32 *)malloc(sizeof(complex32)*Len);
        MKSUREENMEM(in[i]);
        memcpy(in[i], X_VHTLTF[i], (SymbLen+CpLen)*n_ltf*sizeof(complex32));
        memcpy(in[i]+((SymbLen+CpLen)*n_ltf), trans_data+i*N_SYM*(CpLen+DftSize),  N_SYM*(CpLen+DftSize)*sizeof(complex32));
    }
    for(i=0;i<N_TX;i++){
        out[i]=(complex32 *)malloc(sizeof(complex32)*Len);
        MKSUREENMEM(out[i]);
        memset(out[i],0,sizeof(complex32)*Len);
    }

    complex32 *reg_in=(complex32 *)malloc(sizeof(complex32)*3);
    complex32 *reg_out=(complex32 *)malloc(sizeof(complex32)*3);
    int tx,sym;
    for(tx=0; tx<N_TX; tx++){
        memcpy(reg_in,window_buf[tx],sizeof(complex32)*3);
        for(sym=0; sym<n_sym; sym++){
            add_window(in[tx]+sym*SymLen, reg_in, reg_out, out[tx]+sym*SymLen);
            memcpy(reg_in, reg_out, 3*sizeof(complex32));
        }
    }

    for(i=0;i<N_TX;i++) free(in[i]);
    free(reg_in);
    free(reg_out);
}
