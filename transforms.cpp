#include"transforms.h"
#include<vector>
#include<cmath>
#include<iostream>

using namespace std;

vector<int> rotation(vector<int> input, float angle, vector<int> center) {
	vector<int> output(2,0);
	output[0] = input[0] - center[0];
        output[1] = input[1] - center[1];
	output[0] = cos(angle)*output[0] - sin(angle)*output[1];
        output[1] = sin(angle)*output[0] + cos(angle)*output[1];
	output = translation(output, center);
	return output;
}

vector<int> translation(vector<int> input,  vector<int> translate) {
	vector<int> output(2,0);
	output[0] = input[0] + translate[0];
	output[1] = input[1] + translate[1];
	return output;
}

float getAngle(vector<float> v_new , vector<float> v_old) {
	float mag_term = sqrt(pow(v_new[0],2) + pow(v_new[1],2)) * sqrt(pow(v_old[0],2) + pow(v_old[1],2));
	float dot_term = ( v_new[0]*v_old[0] + v_new[1]*v_old[1] );
	if (dot_term < 0.001)
		return 0;
	float angle = acos(dot_term / mag_term);
	if ( (v_new[0]*v_old[1] - v_new[1]*v_old[0]) >= 0)
		return (angle);
	else
		return (-angle);
}
