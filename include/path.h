
#define SEG_STATE_INIT 0
#define SEG_STATE_COUNTING 1
#define SEG_STATE_COUNTED 2
#define SEG_STATE_UNDOING 3
#define SEG_STATE_UNDONE 4
#define MAX_SEGMENTS 100
//100*((4*4)+~8)~=2.4k which is probably ok since we have 64k of ram
//PROS probably takes up quite a bit with things like process tables and uart buffers but I'm sure it's less then half

typedef struct {
	int lsteps;
	int rsteps;
	int state;
	int dir;
} segment;
segment segments[MAX_SEGMENTS];
//currentsegment does not belong here

void resetsegments();
int segmentnav(int dir); //SEG_DIR for continue 0 for undo
#define SEG_INIT -1
#define SEG_UNDO 0
#define SEG_FORWARD 1
#define SEG_LEFT_BANK 2
#define SEG_RIGHT_BANK 3
#define SEG_LEFT_PIVOT 4
#define SEG_RIGHT_PIVOT 5
int undonav();//return to the beginning of a recorded path (blocking)
#define tseg segments[currentsegment]
