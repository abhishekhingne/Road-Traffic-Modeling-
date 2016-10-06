#include<vector>
#include<iostream>
#include"Map.h"

using namespace std;

class Car {
	public:
		vector<float> currentPosn; //current car position co-ordinates
		vector<float> dest;	//destination co-ordinates of car
		float speed;	//spped in kmph
		vector<float> size;	//length by width 
		vector<vector<int> > underPixle; //pixle indices in map under car
	public:
		Car(vector<float> curtPos, vector<float> dst, float spd, vector<float> sze, Map map1);
		friend ostream& operator<<(ostream& os, Car& c );
		void Go(float delta_t, Map map1);
};
