void *l_encoder;
void *r_encoder;
void encoderReset(void *a);
int encoderGet(void *a);
void shoot(int a);
void load(int a);
//void fire(int a);

void delay(int a);
void controldrive(int turn, int foreward);

void suck(int a);
int dstat;

void loadall(int a);
#define SIM 1
//whatever
#define MAX_SPEED 64
#define CONVEYER_SPEED 64


