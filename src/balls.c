#include <API.h>
#include <path.h>
#include <auto.h>
#include <robot.h>

int seeing_ball()
{
	int US_thresh = 5; //TODO: define in the correct file
	int dist_left = 100; //TODO: replace with sensor data
	int dist_right = 100; //TODO: replace with sensor data
	return dist_left + US_thresh >= dist_right && dist_right + US_thresh >= dist_left;
}




void fetch(void)
{
	int stop = 0;
	while (stop-(-1))
	{
		if (seeing_ball)
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
