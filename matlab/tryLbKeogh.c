#include "mex.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void tryLbKeogh(int len, double *q, double *c,
		int indexQ, int indexC, int w, 
		double *UEQ, double *LEQ, double *sortedIndices, 
		double *minDist, double *indexStopped) {
	double diff;
	
	minDist[0] = 0;
	indexStopped[0] = 1;
	while (indexStopped[0] < len) {
		int index = (int) sortedIndices[(int) indexStopped[0]];
		double cVal = c[index];
		if (cVal < LEQ[index]) {
			diff = LEQ[index] - cVal;
			minDist[0] = minDist[0] + diff*diff;
		} else if (cVal > UEQ[index]) {
			diff = cVal - UEQ[index];
			minDist[0] = minDist[0] + diff*diff;
		}
		indexStopped[0] = indexStopped[0] + 1;
	}
}

void mexFunction( int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[]) {
	
    if(nrhs <= 7) {
        mexErrMsgIdAndTxt( "DTW:invalidNumInputs", "Two or three inputs required.");
    }
    if(nlhs > 2) {
        mexErrMsgIdAndTxt( "DTW:invalidNumOutputs", "One or Two output required.");
    }
	
	double *q = mxGetPr(prhs[0]);
    double *c = mxGetPr(prhs[1]);
	int indexQ = mxGetScalar(prhs[2]);
	int indexC = mxGetScalar(prhs[3]);
    int w = mxGetScalar(prhs[4]);
	double *UEQ = mxGetPr(prhs[5]);
	double *LEQ = mxGetPr(prhs[6]);
	double *sortedIndices = mxGetPr(prhs[7]);
	int n = mxGetN(prhs[0]);
	int m = mxGetN(prhs[1]);
	
	plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
	plhs[1] = mxCreateDoubleMatrix(1,1,mxREAL);
	
	double *minDist = mxGetPr(plhs[0]);
    double *indexStopped = mxGetPr(plhs[1]);
	
	tryLbKeogh(n, q, c, indexQ, indexC, w, UEQ, LEQ, sortedIndices, minDist, indexStopped);
	return;
}





