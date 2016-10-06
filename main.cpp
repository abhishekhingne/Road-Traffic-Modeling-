#include"Car.h"
#include<iostream>

using namespace std;

int main() {
	vector<vector<vector<float> > > array;
	array.resize(30);
	for (int i = 0; i < array.size(); i++) {
		array[i].resize(50);
		for (int j = 0; j < array[0].size(); j++) {
			array[i][j].resize(2);
			if ( i>=10 && i<=20 )
				array[i][j][0] = 1;
			else
				array[i][j][0] = 0;
			array[i][j][1] = 0;
		}
	}
	Map obj(array,30,50);
	
	
	 vector<float> currentPosn1(2,0); //current car position co-ordinates
	 currentPosn1[0] = 40; currentPosn1[1] = 15;
         vector<float> dest1(2,0);  //destination co-ordinates of car
	 dest1[0] = 20; dest1[1] = 0;
         float speed1 = 1;    //spped in kmph
         vector<float> size1(2,0);  //length by width of the vehicle in meters (represented by array of size 2)
	 size1[0] = 8; size1[1] = 4;
	Car obj2(currentPosn1, dest1,speed1, size1 , obj);
	vector<Car> cars;
	cars.push_back(obj2);
	vector <int> carOnMap(cars.size(),0);
	for (int t=0; t<50;t++) {
		for (int i=0;i<cars.size();i++) {
			obj.updatePosn(cars);
			cout<<obj<<endl;
			cars[i].Go(1,obj);
			//cout << cars[i] << endl;
			for(int j=0;j<cars[i].underPixle.size();j++) {
				if (!(cars[i].underPixle[j][1]  < obj.map.size() && cars[i].underPixle[j][1] > 0
	                        && cars[i].underPixle[j][0] <  obj.map[0].size() && cars[i].underPixle[j][0] > 0 ) ) {
					cars.erase(cars.begin()+i);
					break;	
				}
			}
			if (cars.size() == 0)
				break;
		}
		obj.sweep(array);
		if (cars.size() == 0)
			break;
	}
	//cout<<cars[0]<<endl;
	//cout<<obj<<endl;
	return 0;
}
