cmd_test.o = gcc -Wp,-MD,./.test.o.d.tmp  -m64 -pthread  -march=native -DRTE_MACHINE_CPUFLAG_SSE -DRTE_MACHINE_CPUFLAG_SSE2 -DRTE_MACHINE_CPUFLAG_SSE3 -DRTE_MACHINE_CPUFLAG_SSSE3 -DRTE_MACHINE_CPUFLAG_SSE4_1 -DRTE_MACHINE_CPUFLAG_SSE4_2 -DRTE_MACHINE_CPUFLAG_AES -DRTE_MACHINE_CPUFLAG_PCLMULQDQ -DRTE_MACHINE_CPUFLAG_AVX -DRTE_MACHINE_CPUFLAG_RDRAND -DRTE_MACHINE_CPUFLAG_FSGSBASE -DRTE_MACHINE_CPUFLAG_F16C -DRTE_MACHINE_CPUFLAG_AVX2  -I/home/zgp/Documents/yujiamanong/CBB-Transmitter/build/include -I/home/zgp/Documents/yujiamanong/CBB-Transmitter/dpdk-stable-16.11.1/x86_64-native-linuxapp-gcc/include -include /home/zgp/Documents/yujiamanong/CBB-Transmitter/dpdk-stable-16.11.1/x86_64-native-linuxapp-gcc/include/rte_config.h -O1 -I/home/zgp/Documents/yujiamanong/CBB-Transmitter/BCCencode -I/home/zgp/Documents/yujiamanong/CBB-Transmitter/intrinsics_interface -I/home/zgp/Documents/yujiamanong/CBB-Transmitter/Process -I/home/zgp/Documents/yujiamanong/CBB-Transmitter/process_data -I/home/zgp/Documents/yujiamanong/CBB-Transmitter/process_data/process_datafunction -I/home/zgp/Documents/yujiamanong/CBB-Transmitter/typeDef -I/home/zgp/Documents/yujiamanong/CBB-Transmitter/VarINIT -D OPTIMIZATION -D AVX2 -D DPDK_FRAME    -o test.o -c /home/zgp/Documents/yujiamanong/CBB-Transmitter/test.c 
