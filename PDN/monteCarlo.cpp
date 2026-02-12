#include <stdio.h>
#include <random>
#include <omp.h>

using namespace std;

int main(){
    //printf("running code\n");// make sure code is running
    long n = 1000000000;//number of points 
    long inside = 0;//number of point inside the circle
    
    double x; double y; //variables for random point
# pragma omp parallel private(x, y) num_threads(10)
    {

        //setting up random number generator
        mt19937 gen(omp_get_thread_num());
        uniform_real_distribution<double> distrib(0.0, 1.0);

#   pragma omp for reduction(+: inside)
        for(int i = 0; i < n; i++){
            x = distrib(gen);
            y = distrib(gen);
            //if point is within 1 unit of the origin, count it 
            if(x*x + y*y <= 1){
                inside++;
            }
        }

    }

    double result = 4 * ((double) inside/ n);//pi estimation
    printf("insde: %ld\n", inside);
    printf("%f \n", result);
    return 0;
}
