//4-Connected Component Algorithm
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Property{
	
};

class connectedComponents{
	public:
	
	int numRows, numCols, minVal, maxVal, newMin, newMax, newLabel = 0, EQSize;
	int **zeroFramedAry;
	int *EQAry;
	int neighborAry[4];	
		
	//constructor
	connectedComponents(int numRows, int numCols, int minVal, int maxVal){
		
		this->numRows = numRows;
		this->numCols = numCols;
		this->minVal = minVal;
		this->maxVal = maxVal;
		newMin = maxVal;
		newMax = minVal;
		
		zeroFramedAry = new int*[numRows+2];
		for(int i = 0;i < numRows+2; i++)
			zeroFramedAry[i] = new int[numCols+2];
			
		for(int i=0;i<4;i++){
			neighborAry[i] = 0;
		}
		EQSize = (numRows*numCols)/2;
		EQAry = new int[EQSize];
		for(int i=0;i<EQSize;i++){
			EQAry[i] = i;
		}
		
	}
	
	//methods
	void zeroFrame(int** zeroFramedAry){
		
		for(int i=0;i<numRows+2;i++){
			for(int j=0;j<numCols+2;j++){
				zeroFramedAry[0][j] = 0;
				zeroFramedAry[numRows+1][j] = 0;
				zeroFramedAry[i][0] = 0;
				zeroFramedAry[i][numCols+1] = 0;
			}
		}
	}
	
	void loadImage(int** zeroFramedAry, string input){
	
		ifstream in;
		in.open(input.c_str());
		in>>numRows>>numCols>>minVal>>maxVal;
		
		for(int i=0;i<numRows;i++){
			for(int j=0;j<numCols;j++){
				in>>zeroFramedAry[i+1][j+1];
			}
		}
	}
	
	void loadNeighbors(int** zeroFramedAry, int neighborAry[], int r, int c){
		
		for(int i=0;i<4;i++){
			neighborAry[i] = 0;
		}
		
		neighborAry[0] = zeroFramedAry[r-1][c];
		neighborAry[1] = zeroFramedAry[r][c-1];
		neighborAry[2] = zeroFramedAry[r][c+1];
		neighborAry[3] = zeroFramedAry[r+1][c];
		
	}
	
	void updateEQAry(int*& EQAry, int a, int b, int minLabel){
		if(a>minLabel)EQAry[a] = minLabel;
		if(b>minLabel)EQAry[b] = minLabel;
		
	}
	
	void manageEQAry(){
		int trueLabel = 0, index = 1;
		while(!index>newLabel){
			if(EQAry[index] == index){
				trueLabel++;
				EQAry[index] = trueLabel;
			}		
			else EQAry[index] = EQAry[EQAry[index]];
			index++;
		}
	}

	void ConnectCC_Pass1(int** zeroFramedAry){
		
		for(int i=1;i<numRows+1;i++){
			for(int j=1;j<numCols+1;j++){
				if(zeroFramedAry[i][j]>0){
					
					loadNeighbors(zeroFramedAry,neighborAry,i,j);
					
					//Case 1
					if(neighborAry[0]==0 && neighborAry[1]==0){
						newLabel++;
						zeroFramedAry[i][j] = newLabel;
					}
					
					//Case 3
					else if(neighborAry[0]!=0 && neighborAry[1]!=0 && neighborAry[0]!=neighborAry[1]){
						int minLabel = 0;
						minLabel = neighborAry[0];
						if(neighborAry[1]<neighborAry[0]) 
							minLabel = neighborAry[1];
						zeroFramedAry[i][j] = minLabel;
						updateEQAry(EQAry,neighborAry[0],neighborAry[1],minLabel);
					}
					
					//Case 2
					else{
						if(neighborAry[0]!=0)
							zeroFramedAry[i][j] = neighborAry[0];
						else zeroFramedAry[i][j] = neighborAry[1];
					}
				}
			}
		}
	}
	
	void ConnectCC_Pass2(int** zeroFramedAry){
		
		for(int i=numRows+1;i>0;i--){
			for(int j=numCols+1;j>0;j--){
				if(zeroFramedAry[i][j]>0){
					
					loadNeighbors(zeroFramedAry,neighborAry,i,j);
					
					//Case 1
					if(neighborAry[2]==0 && neighborAry[3]==0);
					
					//Case 2
					else{
						int minLabel = 0;
						minLabel = zeroFramedAry[i][j];
						if(neighborAry[2]<minLabel && neighborAry[2]!=0)
							minLabel = neighborAry[2];
						if(neighborAry[3]<minLabel && neighborAry[3]!=0)
							minLabel = neighborAry[3];
						zeroFramedAry[i][j] = minLabel;
						if(neighborAry[2]!=0 && neighborAry[3]!=0 && neighborAry[2]!=neighborAry[3]);
						updateEQAry(EQAry,neighborAry[2],neighborAry[3],minLabel);
					}
				}
			}
		}
	}
	
	void ConnectCC_Pass3(int** zeroFramedAry){
		
	}
	
	void prettyPrint(int** zeroFramedAry, ofstream& file, int pass){
		file<<"This is the result of pass #"<<pass<<":"<<endl;
		for(int i=0;i<numRows+2;i++){
			for(int j=0;j<numCols+2;j++){
				if(zeroFramedAry[i][j]<10)
					file<<zeroFramedAry[i][j]<<"  ";
				else file<<zeroFramedAry[i][j]<<" ";
			}
			file<<endl;
		}
		file<<endl<<endl<<"This is the EQArray: "<<endl;
		
		int counter=10;
		int tempEQSize=EQSize;
		while(tempEQSize/10!=0){
			counter=counter*10;
			tempEQSize=tempEQSize/10;
		}
		
		for(int i=0;i<EQSize;i++){
			int temp=EQAry[i];

			if(i%25==0){
				file<<EQAry[i];
				file<<endl;
			}
			else{
				file<<EQAry[i];
				while(temp<counter){
					file<<" ";
					temp=temp*10;	
				}
				file<<" ";
			}
		}
	}
};

int main(int argc, char* argv[]){
	ifstream input (argv[1]);
	string fileName = argv[1];
	ofstream outFile1 (argv[2]);
	ofstream outFile2 (argv[3]);
	ofstream outFile3 (argv[4]);
	int numRows, numCols, minVal, maxVal, newMin, newMax;
	int newLabel = 0;
	int** zeroFramedAry;
	int neighborAry[4];
	
	if(input.is_open()){
		input>>numRows>>numCols>>minVal>>maxVal;
		newMin = maxVal;
		newMax = minVal;
		
		//setting up array
		zeroFramedAry = new int*[numRows+2];
		for(int i = 0;i < numRows+2; i++){
			zeroFramedAry[i] = new int[numCols+2];
		}
		
		for(int i=0;i<4;i++){
			neighborAry[i] = 0;
		}
		
		connectedComponents component(numRows, numCols, minVal, maxVal);
		component.loadImage(zeroFramedAry,fileName);
		component.zeroFrame(zeroFramedAry);
		component.ConnectCC_Pass1(zeroFramedAry);
		component.prettyPrint(zeroFramedAry, outFile1, 1);
		component.ConnectCC_Pass2(zeroFramedAry);
		component.prettyPrint(zeroFramedAry, outFile2, 2);
		component.manageEQAry();
		component.ConnectCC_Pass3(zeroFramedAry);
		component.prettyPrint(zeroFramedAry, outFile3, 3);
	}
	
	else cout<<"Couldn't retrieve data.";
	input.close();
	return 0;
}
