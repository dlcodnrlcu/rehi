#include <iostream>
#include <fstream>
#include <string>
#include <template>
using namespace std;

class Longitude {
private:
	double Latitude, _Longitude;
	int R1, G1, B1, R2, G2, B2, Code;
	int stu_number = 68;
	double** arr = new double* [18];
public:
	Longitude(Longitude& l) {
		R1 = l.R1;
		R2 = l.R2;
		G1 = l.G1;
		G2 = l.G2;
		B1 = l.B1;
		B2 = l.B2;
		Code = l.Code;
		stu_number = l.stu_number;
	}
	Longitude(fstream& gpsFile, fstream& RGBFile, int value) {
		stu_number = value;
		for (int i = 0; i < 18; i++) {
			arr[i] = new double[9];
		}
		int i = 0;
		string line;
		getline(gpsFile, line);
		getline(RGBFile, line);

		while ((gpsFile>> Latitude >> _Longitude >> R1 >> G1 >> B1)&& (RGBFile >> R2 >> G2 >> B2 >> Code)){
			arr[i][0] = Latitude;
			arr[i][1] = _Longitude;
			arr[i][2] = R1;
			arr[i][3] = G1;
			arr[i][4] = B1;
			arr[i][5] = R2;
			arr[i][6] = G2;
			arr[i][7] = B2;
			arr[i][8] = Code;
			i += 1;
		}
	}
	~Longitude() {
		for (int i = 0; i < 18; i++) {
			delete[] arr[i];
		}
		delete[] arr;
	}
	void calCode(ofstream& resultFile) {
		int resultLine = 0;
		int currentLine = 0;
		int gpsLineCounter = 0;
		double leastD = 9999999999;

		while (gpsLineCounter < 18) {
			resultLine = 0;
			currentLine = 0;
			while(currentLine < 18) {
				bool flag;
				double d;
				R1 = arr[gpsLineCounter][2];
				G1 = arr[gpsLineCounter][3];
				B1 = arr[gpsLineCounter][4];
				R2 = arr[currentLine][5];
				G2 = arr[currentLine][6];
				B2 = arr[currentLine][7];
				d = pow((R1 - R2), 2) + pow((G1 - G2), 2) + pow((B1 - B2), 2);
				cout << "d : " << d << endl;
				flag = (d < leastD) ? true : false;

				if (flag == true) {
					leastD = d;
					resultLine = currentLine;
					currentLine += 1;
				}
				else {
					currentLine += 1;
				}
			}
			
			resultFile << arr[gpsLineCounter][0] << " " << arr[gpsLineCounter][1]
			<< " " << arr[resultLine][8] << endl;
			gpsLineCounter += 1;
		}
	}
};

int main() {
	cout << "1:GPSResult\n2:Longitude Code\n3:Show GPS\n4:Distance\n5:Exit\n:";
	int select;
	cin >> select;

	fstream f1{ "GPS.txt" };
	fstream f2{ "RGBCode_Table.txt" };
	Longitude p(f1, f2, 68);
	
	while (select != 6) {
		if (select == 1) {
			ofstream file;
			file.open("GPSResult.txt");			
			p.calCode(file);
			file.close();
		}
		if (select == 2) {
			
		}
		if (select == 3) {
			string line;
			ifstream file;
			file.open("GPSResult.txt");
			while (getline(file, line)) {
				cout << line << endl;
			}
		}
		if (select == 4) {
			Longitude q(p);
		}

		if (select == 5) {

		}
		cout << "1:GPSResult\n2:Longitude Code\n3:Show GPS\n4:Show GPS2\n5:Distance\n6:Exit\n:";
		cin >> select;
	}
}