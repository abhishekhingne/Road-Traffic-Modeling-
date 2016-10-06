#include"Car.h"
#include"transforms.h"
#include<cmath>
#include<vector>

Car::Car(vector<float> curtPos, vector<float> dst, float spd, vector<float> sze, Map map1) {
                currentPosn = curtPos;
                dest = dst;
                speed = spd;
                size = sze;
		float diag = sqrt(pow(size[1],2) + pow(size[0],2));
		float theta;
		if (fabs(currentPosn[0]-dest[0]) < 0.001)
			theta = M_PI/2;
		else
			theta = atan(fabs(currentPosn[1]-dest[1])/fabs(currentPosn[0]-dest[0]));
		float X = cos(-theta)*currentPosn[0] - sin(-theta)*currentPosn[1];
		float Y = sin(-theta)*currentPosn[0] + cos(-theta)*currentPosn[1];
		vector<vector <float> > corners; corners.resize(4);
		for (int i=0; i<4; i++)
			corners[i].resize(2);
		corners[0][0] = corners[1][0] = X - size[0]/2;
		corners[0][1] = corners[3][1] = Y + size[1]/2;
		corners[1][1] = corners[2][1] = Y - size[1]/2;
		corners[2][0] = corners[3][0] = X + size[0]/2;
		vector<vector <float> > corners1 = corners;
		for (int i = 0; i < 4; i++) {
			corners1[i][0] = cos(theta)*corners[i][0] - sin(theta)*corners[i][1];
			corners1[i][1] = sin(theta)*corners[i][0] + cos(theta)*corners[i][1];
		}
		float x_scale = map1.getX_scale();
		float y_scale = map1.getY_scale();
		vector<vector < int> > cornersPixle; cornersPixle.resize(4);
		for (int i=0; i<4; i++)
                        cornersPixle[i].resize(2);
		for (int i = 0; i < 4; i++) {
			cornersPixle[i][0] = round(corners1[i][0] / x_scale);
			cornersPixle[i][1] = round(corners1[i][1] / y_scale);
		}
		vector<int> posnPixle; posnPixle.resize(2);
		posnPixle[0] = currentPosn[0]/x_scale;
		posnPixle[1] = currentPosn[1]/y_scale;
		int boxsize = ( ( round(size[0]/x_scale) + round(size[1]/y_scale) ) / 2 );
		vector<int> vect(2,0);
		int mapNrow = map1.map.size();
		int mapNcol = map1.map[0].size();
		int A,B,C,D;
		for (int i=max(0,(posnPixle[0]-boxsize)); i<min(mapNcol,(posnPixle[0]+boxsize)); i++) {
			for (int j=max(0,(posnPixle[1]-boxsize)); j<min(mapNrow,(posnPixle[1]+boxsize)); j++) {
				float angle = 0;
				for (int k=0;k<4;k++) {
					A = (i - cornersPixle[k][0]);
					B = (j - cornersPixle[k][1]);
					if (k==3) {
						C = (i - cornersPixle[0][0]);
						D = (j - cornersPixle[0][1]);
					}
					else {
						C = (i - cornersPixle[k+1][0]);
						D = (j - cornersPixle[k+1][1]);
					}
					if(sqrt( (pow(A,2)+pow(B,2)) * (pow(C,2)+pow(D,2)) )==0){
						vect[0] = i; vect[1] = j;
						underPixle.push_back(vect);
						break;
					}
					angle = angle + acos( (A*C+B*D) / sqrt( (pow(A,2)+pow(B,2)) * (pow(C,2)+pow(D,2)) ) );
				}
				if ( fabs(360-angle*180/M_PI) < 0.1 ) {
					vect[0] = i; vect[1] = j;
					underPixle.push_back(vect);
				}
			}
		}
}

void Car::Go(float delta_t, Map map1) {
	float v_x, v_y;
	if ( fabs(- currentPosn[0] + dest[0])  < 0.001) {
		if ((- currentPosn[1] + dest[1]) > 0)
			v_y = speed;
		else
			v_y = -speed;
		v_x = 0;
	}
	else {
		float C = (- currentPosn[1] + dest[1])/(- currentPosn[0] + dest[0]);
		v_x = speed / sqrt(pow(C,2) + 1);
		v_x = ( (- currentPosn[0] + dest[0]) > 0 ? 1 : (( (- currentPosn[0] + dest[0]) < 0) ? -1 : 0) )*v_x;
		v_y = C*v_x;
	}
	//cout<<v_x<<" "<<v_y<<endl;
	float x_new = v_x*delta_t + currentPosn[0];
	float y_new = v_y*delta_t + currentPosn[1];
        float x_scale = map1.getX_scale();
        float y_scale = map1.getY_scale();
	vector<float> v_old(2), v_new(2); 
	v_new[0] = x_new - currentPosn[0]; v_new[1] = y_new - currentPosn[1];
	v_old[0] = currentPosn[0] - dest[0]; v_old[1] = currentPosn[1] - dest[1];
	float rot_theta = getAngle(v_new , v_old);	
	vector<int> tr_dist; tr_dist.resize(2);
	tr_dist[0] = round( (x_new - currentPosn[0])/x_scale );
	tr_dist[1] = round(  (y_new - currentPosn[1])/y_scale );
	vector<int> posnPixle; posnPixle.resize(2);
	posnPixle[0] = round(currentPosn[0]/x_scale);
        posnPixle[1] = round(currentPosn[1]/y_scale);
	//cout << "rotation: " << rot_theta << " posnPixle:  " << posnPixle[0] <<","<<posnPixle[1] << " tr_dist: "<< tr_dist[0] <<","<< tr_dist[1] <<endl;
	for (int i=0;i<underPixle.size();i++) {
		underPixle[i] = rotation(underPixle[i], rot_theta, posnPixle);
		underPixle[i] = translation(underPixle[i], tr_dist);
	}
	currentPosn[0] = x_new;
	currentPosn[1] = y_new;
}

ostream& operator<<(ostream& os, Car& c ) {
	os <<"Current Position: "<<"x= "<< c.currentPosn[0] <<" m, "<<"y= "<< c.currentPosn[1]<<" m " <<endl;
	os <<"Destination Position: "<<"x= "<<c.dest[0] << " m, "<<"y= "<< c.dest[1]<< " m "<<endl;
	os <<"Vehicle speed: "<<c.speed<<" KMPH" <<endl;
	os <<"Car size: "<<"length= "<<c.size[0] <<" m, " <<"width= "<< c.size[1] << " m "<<endl;;
	os << "Car Pixles: "<<endl;
	for (int i=0; i < c.underPixle.size(); i++)
		os << c.underPixle[i][0] << ", " << c.underPixle[i][1] <<endl;
	return os;
}
