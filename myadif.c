// myadif v0.1 by GM 2015

#include "stdio.h"
#define login "/Users/gmazzini/Downloads/log.txt"
#define logout "/Users/gmazzini/Downloads/log.adif"

int main(){
	FILE *fpin,*fpout;
	// inizialization
	fpin=fopen(login,"rt");
	fpout=fopen(logout,"wt");
	// header
	fprintf(fpout,"<adif_ver:5>3.0.4\n");
	fprintf(fpout,"<programid:6>ik4lzh\n");
	fprintf(fpout,"<eoh>\n");
	fprintf(fpout,"\n");
	
	
	fclose(fpin);
	fclose(fpout);
	
}
