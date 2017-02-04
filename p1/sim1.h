#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// the struct that holds all of the config file data
typedef struct config {
	char file_path[32];
	char cpu_scheduling[32];
	char quant_cyc[32];
	char mem_kb[32];
	char process_cyc[32];
	char io[32];
	char log_to[32];
	char log_fp[32];
} CFG;

// the struct that holds all of the metadata file data
typedef struct metadata {
	char ps1[200];
	char ps2[200];
	char ps3[200];
	char ps4[200];
	char ps5[200];
	char ps6[200];
	char ps7[200];
	char ps8[200];
	char ps9[200];
	char ps10[200];
	char ps11[200];
	char ps12[200];
} MD;

MD mdstore(char* file_name);
void read_md(MD metad);
CFG configStore(char* file_name);
void read_config(CFG config_data);
void empty(char *var);
