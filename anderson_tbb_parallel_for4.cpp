#include <iostream>

#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

using namespace tbb;

struct Average {
    const float* input;
    float* output;
    void operator()( const blocked_range<int>& range ) const {
        for( int i=range.begin(); i!=range.end(); ++i ) {
            output[i] = (input[i-1]+input[i]+input[i+1])*(0.77);
        }
    }
};

// Note: Reads input[0..n] and writes output[1..n-1]. 
void ParallelAverage( float* output, const float* input, size_t n ) {
    Average avg;
    avg.input = input;
    avg.output = output;
    parallel_for( blocked_range<int>( 1, n ), avg );
    }

int main() {

	float output[100];
	float input[100];

	for (int i=0; i <100; i++)
		input[i] = i;

	ParallelAverage(output, input, 100);

	for (int i=0; i <100; i++)
                std::cout << output[i] << "\n";


}