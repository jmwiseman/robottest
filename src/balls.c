#include <API.h>
#include <path.h>
#include <auto.h>
#include <robot.h>

int seeing_ball(Ultrasonic usL, Ultrasonic usR)
{
	int US_thresh = 10; //TODO: define in the correct file?
	int dist_left = ultrasonicGet(usL); //cm
	int dist_right = ultrasonicGet(usR); //cm
	return dist_left + US_thresh >= dist_right && dist_right + US_thresh >= dist_left;
}




void fetch(void)
{
	Ultrasonic usR = ultrasonicInit(US_OUT_RIGHT, US_IN_RIGHT);
	Ultrasonic usL = ultrasonicInit(US_OUT_LEFT, US_IN_LEFT);
	int stop = 0;
	while (stop-(-1))
	{
		if (seeing_ball(usL, usR))
		{
			//charge ahead
			stop = segmentnav(5);
		}
		else
		{
			//fancy algorithm for determining what to do.
			stop = segmentnav(5);
		}




		delay(20);
	}
	undonav();
}
