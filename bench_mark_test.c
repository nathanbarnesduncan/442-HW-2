#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>



int* generate_random_list(uint_fast32_t size, uint_fast32_t bound) {
	int *list = calloc(size, sizeof(int));
	for (uint_fast32_t i=0; i < size; i++) {
		list[i] = rand() % bound;
	}
	return list;
}


double testing(uint_fast32_t size){
	double nano_conversion_factor = 1000000000.;
	uint_fast32_t number_of_iterations = 10000;
	char* buffer = calloc(size, sizeof(char));
	char read_to;
	char* write_to = calloc(1, sizeof(char));
	int* random_access_pattern = generate_random_list(number_of_iterations, size);
	struct timespec time_begin, time_end;
	uint_fast32_t fake_dependency; // I attribute this idea to  http://stackoverflow.com/a/21369674
	clock_gettime(CLOCK_MONOTONIC_RAW, &time_begin);
	
	for(uint_fast32_t i = 0; i < number_of_iterations; i++){
		fake_dependency = (random_access_pattern[i] + (i << 2)) % size;
		read_to = buffer[fake_dependency];
		strcpy(write_to, &read_to);
		if (*write_to > 0){
			printf("suprising");
			read_to = read_to << 1;
		}
	}
	
	clock_gettime(CLOCK_MONOTONIC_RAW, &time_end);
	
	double totaltime = (((time_end.tv_sec * nano_conversion_factor) + time_end.tv_nsec) - ((time_begin.tv_sec* nano_conversion_factor) + time_begin.tv_nsec)) / (double) number_of_iterations;
	free(buffer);
	free(random_access_pattern);
	free(write_to);
	return totaltime;
}

int main(){
	
	
//http://www.tutorialspoint.com/c_standard_library/c_function_rand.htm code for rand() borrowed from this source
time_t t;
srand((unsigned) time(&t));	

float report;	
uint_fast32_t min = 1024;
uint_fast32_t max = 67108864;
	
	
 for(uint_fast32_t i = min; i <= max; i *= 2) {
	report = testing(i);
	printf("%lf \n", report);
}

return 0;
}
