// myadif by GM 2015
// v0.1 basic build
// v0.2 change basic directonry and conversion to upper case

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#define login "/Users/gmazzini/hamradio/log.txt"
#define logout "/Users/gmazzini/hamradio/log.adif"

int main(){
	FILE *fpin,*fpout;
	int i;
	long myfreq;
	char buf[100],mydate[100],mytime[100],mycall[100],myrst_sent[100],myrst_rcvd[100];
	char *myproc;
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
		for(i=strlen(buf)-1;i>=0;i--)buf[i]=toupper(buf[i]);
		sscanf(buf,"%s %s %s %ld %s %s",mydate,mytime,mycall,&myfreq,myrst_sent,myrst_rcvd);
		fprintf(fpout,"<qso_date:%lu>%s\n",strlen(mydate),mydate);
		fprintf(fpout,"<time_on:%lu>%s\n",strlen(mytime),mytime);
		myproc=strchr(mycall,33);
		if(myproc!=NULL){
			*myproc='\0';
			switch(*(myproc+1)){
				case 'S':
				fprintf(fpout,"<qsl_sent:1>Y\n");
				break;
				case 'R':
				fprintf(fpout,"<qsl_rcvd:1>Y\n");
				break;
				case 'B':
				fprintf(fpout,"<qsl_sent:1>Y\n");
				fprintf(fpout,"<qsl_rcvd:1>Y\n");
				break;
				default:
				printf("unknown status for call %s\n",mycall);
				exit(-1);
			}
		}
		fprintf(fpout,"<call:%lu>%s\n",strlen(mycall),mycall);
		fprintf(fpout,"<rst_sent:%lu>%s\n",strlen(myrst_sent),myrst_sent);
		fprintf(fpout,"<rst_rcvd:%lu>%s\n",strlen(myrst_rcvd),myrst_rcvd);
		fprintf(fpout,"<mode:3>ssb\n");
		for(i=0;i<11;i++){
			if(myfreq>=startband[i]&&myfreq<=endband[i])break;
		}
		if(i==11){
			printf("unknown freq for call %s\n",mycall);
			exit(-1);
		}
		fprintf(fpout,"<band:%lu>%s\n",strlen(nameband[i]),nameband[i]);
		sprintf(buf,"%.3f",((double)myfreq)/1000);
		fprintf(fpout,"<freq:%lu>%s\n",strlen(buf),buf);
		fprintf(fpout,"<eor>\n");
		fprintf(fpout,"\n");
	}
	
	fclose(fpin);
	fclose(fpout);
}
