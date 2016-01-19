#include "path.h" 
#include "robot.h"
#include "main.h"
#include "auto.h"
#include "API.h"
int currentsegment=-1;
void p_status() {
	static int callcount=0;
	static int a;
	callcount+=1;
	if(callcount>10) {
		printf("status: REMAIN: L:%d\t R:%d\n\r",CUR_DIST_L, CUR_DIST_R);
		callcount=0;
	}

}

int segmentvalid(){
	if(segments[currentsegment].state<0 ||segments[currentsegment].dir<0){
		printf("Path segment %d faild validation test\n",currentsegment);
		return 0;
	}
	return 1;
}//the only function in this file where a 1 is good, it is scoped here only

void resetsegments(){
	currentsegment=-1;
	int i=0;
	for(i=0;i<=MAX_SEGMENTS;i++){
		segments[i].lsteps=0;
		segments[i].rsteps=0;
		segments[i].state=SEG_STATE_INIT;
		segments[i].dir=SEG_INIT;
	}
}
int newsegment(){
	printf("allocating new path segment...\n\r");
	if(currentsegment>=MAX_SEGMENTS-1){
		printf("Out of path segments\n");
		return 1;
	}
	if(currentsegment>=0){
		if(!segmentvalid()){
			printf("path segment%d corrupt\n",currentsegment);
			return 1;
		}
		segments[currentsegment].state=SEG_STATE_COUNTED;

	}
	tseg.lsteps=encoderGet(l_encoder);
	tseg.rsteps=encoderGet(r_encoder);
	encoderReset(l_encoder);
	encoderReset(r_encoder);

	currentsegment=currentsegment+1;
	segments[currentsegment].lsteps=0;
	segments[currentsegment].rsteps=0;
	segments[currentsegment].state=SEG_STATE_INIT;
	segments[currentsegment].dir=SEG_INIT;
	return 0;
}
void segmove(int dir) {
	switch(dir){
		case SEG_FORWARD: drive_straight();break;
		case SEG_LEFT_BANK: bank_left();break;
		case SEG_RIGHT_BANK: bank_right();break;
		case SEG_LEFT_PIVOT: turn_left();break;
		case SEG_RIGHT_PIVOT: turn_right();break;
		default: printf("invalid physical direction %d\n",dir);break;
	}
}
int segmentnav(int dir){
	printf("navigating\n\r");
	if(currentsegment<0){
		if(newsegment())
			return 1;
		tseg.dir=dir;
	}
	if(!segmentvalid())
		return 1;
	if(tseg.dir!=dir || tseg.dir==SEG_INIT){
		newsegment();
		tseg.dir=dir;
	}
	switch(dir){
		case SEG_FORWARD:tseg.ldir=1;tseg.rdir=1;break;
		case SEG_LEFT_BANK: tseg.ldir=0;tseg.rdir=1;break;
		case SEG_RIGHT_BANK: tseg.ldir=1;tseg.rdir=0;break;
		case SEG_LEFT_PIVOT: tseg.ldir=-1;tseg.rdir=1;break;
		case SEG_RIGHT_PIVOT: tseg.ldir=1;tseg.rdir=-1;break;
		default: printf("invalid physical direction %d\n",dir);break;
	}
	segmove(dir);
	return 0;
}
int undonav() {
	printf("reversing all navigation\n");
	while(currentsegment>=0) {
		printf("Starting segment:%d\n\r",currentsegment);
		while( 
				(CUR_DIST_L >=0 ) &&
				(CUR_DIST_R >=0 )
				){
			p_status();
			printf("p");
			int d=0;
			if (tseg.dir%1)
				d=tseg.dir-1;
			else
				d=tseg.dir+1;
			segmove(d);
			delay(10);
		}
		printf("done with semgnet%d",currentsegment);
		encoderReset(l_encoder);
		encoderReset(r_encoder);
		currentsegment=currentsegment-1;

		delay(20);
	}
	return 0;
}
