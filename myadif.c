// myadif v0.1 by GM 2015

#include "stdio.h"
#define login "/Users/gmazzini/Downloads/log.txt"
#define logout "/Users/gmazzini/Downloads/log.adif"

int main(){
	FILE *fpin,*fpout;
	int i;
	long myfreq;
	char buf[100],mydate[100],mytime[100],mycall[100],myrst_sent[100],myrst_rcvd[100];
	long startband[11]={1830,3500,7000,10100,14000,18068,21000,24890,28000,50000,144000};
	long endband[11]={1850,3800,7200,10150,14350,18168,21450,24990,29700,51000,146000};
	char *nameband[11]={"160m","80m","40m","30m","20m","17m","15m","12m","10m","6m","2m"};
	
	// inizialization
	fpin=fopen(login,"rt");
	fpout=fopen(logout,"wt");
	
	// header
	fprintf(fpout,"<adif_ver:5>3.0.4\n");
	fprintf(fpout,"<programid:6>ik4lzh\n");
	fprintf(fpout,"<eoh>\n");
	fprintf(fpout,"\n");
	
	// log processing
	for(;;){
		if(fgets(buf,100,fpin)==NULL)break;
		sscanf(buf,"%s %s %s %ld %s %s",mydate,mytime,mycall,&myfreq,myrst_sent,myrst_rcvd);
		fprintf(fpout,"<qso_date:%d>%s\n",strlen(mydate),mydate);
		fprintf(fpout,"<time_on:%d>%s\n",strlen(mytime),mytime);
		fprintf(fpout,"<call:%d>%s\n",strlen(mycall),mycall);
		fprintf(fpout,"<qso_date:%d>%s\n",strlen(mydate),mydate);
		fprintf(fpout,"<rst_sent:%d>%s\n",strlen(myrst_sent),myrst_sent);
		fprintf(fpout,"<rst_rcvd:%d>%s\n",strlen(myrst_rcvd),myrst_rcvd);
		fprintf(fpout,"<mode:3>ssb\n");
		for(i=0;i<11;i++){
			if(myfreq>=startband[i]&&myfreq<=endband[i])break;
		}
		if(i==11){
			printf("unknown freq for call %s\n",mycall);
			exit(-1);
		}
		fprintf(fpout,"<band:%d>%s\n",strlen(nameband[i]),nameband[i]);
		sprintf(buf,"%8.4f",((double)myfreq)/1000);
		fprintf(fpout,"<freq:%d>%s\n",strlen(buf),buf);
		fprintf(fpout,"<eor>\n");
		fprintf(fpout,"\n");
	}
	
	fclose(fpin);
	fclose(fpout);
}
