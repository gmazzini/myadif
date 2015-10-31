// myadif by GM 2015
// v0.1 basic build
// v0.2 change basic directory and conversion to upper case
// v0.3 introduction frequecy flag for contest
// v0.4  

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#define login "./log.txt"
#define logout "./log.adif"

int main(){
	FILE *fpin,*fpout;
	int i;
	char buf[100],mydate[100],mytime[100],mycall[100],myrst_sent[100],myrst_rcvd[100],myfreq[100];
	char *myproc,*auxi,*auxe;
	long lmyfreq;
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
		sscanf(buf,"%s %s %s %s %s %s",mydate,mytime,mycall,myfreq,myrst_sent,myrst_rcvd);
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
		if(myfreq[0]=='M'){
			auxi=myfreq+1;
			auxe=strchr(auxi,'_');
			*auxe='\0';
			fprintf(fpout,"<band:%lu>%sm\n",strlen(auxi)+1,auxi);
			if(*(auxe+1)=='C'){
				auxi=auxe+2;
				auxe=strchr(auxi,'_');
				*auxe='\0';
				fprintf(fpout,"<src_string:%lu>%s\n",strlen(auxi),auxi);
			}
		}
		else {
			lmyfreq=atol(myfreq);
			for(i=0;i<11;i++){
				if(lmyfreq>=startband[i]&&lmyfreq<=endband[i])break;
			}
			if(i==11){
				printf("unknown freq for call %s\n",mycall);
				exit(-1);
			}
			fprintf(fpout,"<band:%lu>%s\n",strlen(nameband[i]),nameband[i]);
			sprintf(buf,"%.3f",((double)lmyfreq)/1000);
			fprintf(fpout,"<freq:%lu>%s\n",strlen(buf),buf);
		}
		fprintf(fpout,"<eor>\n");
		fprintf(fpout,"\n");
	}
	
	fclose(fpin);
	fclose(fpout);
}
