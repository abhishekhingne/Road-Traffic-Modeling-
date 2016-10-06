#include<vector>
#include<iostream>
#include"Car.h"

using namespace std;

Map::Map(vector<vector<vector<float> > > array, float ht, float wdth) {
	map = array;
	picHeight = ht;
        picWidth = wdth;
}

ostream& operator<<(ostream& os, Map& m ) {
	os<<"x_scale= "<<m.getX_scale()<<" Y_scale= "<<m.getY_scale()<<endl;
	int i,j;
	int nRow = m.map.size();
	int nCol = m.map[0].size();
	for (i = 0; i < nRow; i++) {
		for (j = 0; j < nCol; j++) {
			os << m.map[i][j][0] << " ";
		}
		os<<endl;
	}
	return os;
}

float Map::getY_scale() {
	int nRow = map.size();
	return (picHeight / nRow);
}

float Map::getX_scale() {
	int nCol = map[0].size();
	return (picWidth / nCol);
}

void Map::updatePosn(vector<Car> carArray) {
	if (carArray.size() > 0) {
		for(int i=0;i<carArray.size();i++) {
			for(int j=0;j<carArray[i].underPixle.size();j++){
				if (carArray[i].underPixle[j][1]  < map.size() && carArray[i].underPixle[j][1] > 0 
				&& carArray[i].underPixle[j][0] <  map[0].size() && carArray[i].underPixle[j][0] > 0 ) {
					map[carArray[i].underPixle[j][1]][carArray[i].underPixle[j][0]][0] = 8;
					map[carArray[i].underPixle[j][1]][carArray[i].underPixle[j][0]][1] = 8;
				}
			}			
		}
	}
}

void Map::sweep(vector<vector<vector<float> > > array) {
	map = array;	
}
