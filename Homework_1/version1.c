#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void rectangle_area(double length, double width) {
   	
	double area = length * width;
    	
	printf("Rectangle Area: %f\n", area);
}

void triangle_area(int base, int height) {
   	
	double area = 0.5 * base * height;
    
	printf("Triangle Area: %f\n", area);
}

int main() {

    	pid_t pid = fork();

    	if (pid < 0) {
			printf("Fork failed!\n");
        	return 1;
    	} else if (pid == 0) {
        	triangle_area(3, 4);
    	} else {
        	rectangle_area(50.5, 10);
    	}

    	return 0;
}

