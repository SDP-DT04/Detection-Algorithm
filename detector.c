#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

/**
* Holds the acceleration and time data
*/ 
typedef struct
{
	double *t;
	double *accl;
	int len;
} Data;

/**
* Get the acceleration and time data from the input file
*/
Data get_data(int argc, char* argv[])
{
	Data data;	

	FILE* input;
	if (argc == 2)
	{
		input = fopen(argv[1], "r");
	}
	else
	{
		printf("Please specify input file.\n");
		return data;
	}

	double d;
	int count = 0; 
	while (!feof(input))
	{
		fscanf(input, "%lf,%lf\n", &d, &d);
		count++;
	}

	data.t = malloc(count * sizeof(double));
	data.accl = malloc(count * sizeof(double));
	data.len = count; 	

	fclose(input);
	input - fopen(argv[1], "r");

	for (int i=0; i<count;++i)
	{
		fscanf(input, "%lf,%lf\n", &data.t[i], &data.accl[i]); 
	}

	return data;
}

int main(int argc, char* argv[])
{
	short NUM_SAMPLES = 20; 
	unsigned char isSwimming = FALSE; 

	Data data = get_data(argc, argv);
	double avg = 0;
	double stdev = 0; 
	
	// start of the algorithm
	for (int i=0; i < data.len-NUM_SAMPLES; ++i)
	{
		for (int j=i; j<i+NUM_SAMPLES; j++)
		{
			avg += data.accl[j]; 
		}
		avg = avg / NUM_SAMPLES;

		for (int j=i; j<i+NUM_SAMPLES; j++)
		{
			stdev += (data.accl[j]-avg) * (data.accl[j]-avg); 
		} 
		stdev = stdev / NUM_SAMPLES; 
		stdev = sqrt(stdev); 
	
		//	printf("%lf\n", stdev); 
	
		double time = data.t[i+NUM_SAMPLES]; 	
	
		if (isSwimming == FALSE && stdev > 1)
		{
			printf("detected start time: %lf\n", time);
			isSwimming = TRUE;
		} 
		else if (isSwimming == TRUE && stdev < 0.6 && abs(avg - 9.8) < 0.0001)
		{
			printf("detected stop time: %lf\n", data.t[i+NUM_SAMPLES]); 
			printf("%lf\n", stdev); 
			break; 
		}
	}

	// free up memory
	free (data.t);
	free (data.accl);
	return 0;
}
