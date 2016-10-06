#include<vector>
#include<iostream>
class Car;
using namespace std;

class Map {
	public:
		vector<vector<vector<float> > > map;
		float picHeight;
		float picWidth;
	public:
		Map(vector<vector<vector<float> > > array, float ht, float wdth);
		friend ostream& operator<<(ostream& os, Map& m );

		float getX_scale();
		float getY_scale();

		void updatePosn(vector<Car> carArray);
		void sweep(vector<vector<vector<float> > > array);
};
