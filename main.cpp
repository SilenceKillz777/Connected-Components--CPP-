//4-Connected Component Algorithm
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Property{
	int label;
	int numPixels;
	int minRow, minCol, maxRow, maxCol;
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
		while(!(index>newLabel)){
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
	
	int ConnectCC_Pass3(int** zeroFramedAry){
		int numObjects = 0, newMin = 0, newMax = 0;
		for(int i=1;i<numRows+1;i++){
			for(int j=1;j<numCols+1;j++){
				zeroFramedAry[i][j] = EQAry[zeroFramedAry[i][j]];
				if(zeroFramedAry[i][j]>numObjects)
					numObjects = zeroFramedAry[i][j];
				if(zeroFramedAry[i][j]>newMax)
					newMax = zeroFramedAry[i][j];
			}
		}

		for(int i=1;i<numRows+1;i++){
			for(int j=1;j<numCols+1;j++){
				if(zeroFramedAry[i][j]){
				}
			}
		}
		return numObjects;
	}
	
	//print EQAry method
	void printEQAry(ofstream& file, int pass){
		file<<"This is the EQArray for pass #"<<pass<<":"<<endl;
		
		int counter=10;
		for(int i=0;i<newLabel;i++){
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
		file<<endl;
	}
	
	//overloaded print EQAry method specifically for after manageEQAry method
	void printEQAry(ofstream& file, string pass){
		file<<"This is the EQArray after manageEQAry method: "<<endl;
		
		int counter=10;
		for(int i=0;i<newLabel;i++){
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
		file<<endl<<endl ;
	}
	
	//pretty print image and EQAry for each pass
	void prettyPrint(int** zeroFramedAry, ofstream& file, int pass){
		file<<"This is the result of pass #"<<pass<<":"<<endl;
		for(int i=0;i<numRows+2;i++){
			for(int j=0;j<numCols+2;j++){
				if(zeroFramedAry[i][j]<10 && zeroFramedAry[i][j]!=0)
					file<<zeroFramedAry[i][j]<<"  ";
				else if(zeroFramedAry[i][j]<10 && zeroFramedAry[i][j]==0)
					file<<"   ";
				else file<<zeroFramedAry[i][j]<<" ";
			}
			file<<endl;
		}
		printEQAry(file, pass);
		file<<endl;
	}
	
	//print image on argv[3]
	void printImage(int** zeroFramedAry, ofstream& file){
		//cout<<newMin<<" "<<newMax;
		file<<numRows<<" "<<numCols<<" "<<newMin<<" "<<newMax<<endl;
		for(int i=0;i<numRows+2;i++){
			for(int j=0;j<numCols+2;j++){
				if(zeroFramedAry[i][j]<10)
					file<<zeroFramedAry[i][j]<<"  ";
				else file<<zeroFramedAry[i][j]<<" ";
			}
			file<<endl;
		}
	}
	
	//counts number of pixels with same label
	int countLabel(int label, int** zeroFramedAry){
		int count = 0;
		for(int i=1;i<numRows+1;i++){
			for(int j=1;j<numCols+1;j++){
				if(zeroFramedAry[i][j]==label)
					count++;
			}
		}
		return count;
	}
	
	//find top-left and bottom-right coordinates of bounding box
	void findBoundingBox(int& minRow, int& minCol, int& maxRow, int& maxCol, int label, int** zeroFramedAry){
		int count = 0;
		//finds first instance of label to initialize
		for(int row=1;row<numRows+1;row++){
			for(int col=1;col<numCols+1;col++){
				if(zeroFramedAry[row][col] == label){
					minCol = col;
					maxCol = col;
				}
			}	
		}
		//using first instance to update bounds
		for(int row=1;row<numRows+1;row++){
			for(int col=1;col<numCols+1;col++){
				if(count == 0 && zeroFramedAry[row][col] == label){
					minRow = row;
					maxRow = row;	
					count++;
				}
				if(zeroFramedAry[row][col] == label)
					maxRow = row;
				
				if(zeroFramedAry[row][col] == label && col<minCol)
					minCol = col;
				if(zeroFramedAry[row][col] == label && col>maxCol)
					maxCol = col;
			}
		}
	}
	
	//populating struct by label number
	void loadStruct(Property CC[], int** zeroFramedAry, int size){
		int numPixels = 0;
		for(int i=0;i<size;i++){
			int minRow = 0, minCol = 0, maxRow = 0, maxCol = 0;
			CC[i].label = i+1;
			numPixels = countLabel(i+1,zeroFramedAry);
			CC[i].numPixels = numPixels;
			findBoundingBox(minRow, minCol, maxRow, maxCol, i+1, zeroFramedAry);
			CC[i].minRow = minRow;
			CC[i].minCol = minCol;
			CC[i].maxRow = maxRow;
			CC[i].maxCol = maxCol;
		}		cout<<newMin<<" "<<newMax;

	}
	
	//printing Struct into argv[4]
	void printStruct(Property CC[], int size, ofstream& file){
		file<<numRows<<" "<<numCols<<" "<<minVal<<" "<<maxVal<<endl;
		file<<size<<endl;
		for(int i=0;i<size;i++){
			file<<CC[i].label<<endl;
			file<<CC[i].numPixels<<endl;
			file<<CC[i].minRow<<" "<<CC[i].minCol<<endl;
			file<<CC[i].maxRow<<" "<<CC[i].maxCol<<endl<<endl;
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
	int var = 0;
	
	if(input.is_open()){
		input>>numRows>>numCols>>minVal>>maxVal;
		newMin = maxVal;
		newMax = minVal;
		
		//setting up arrays
		zeroFramedAry = new int*[numRows+2];
		for(int i = 0;i < numRows+2; i++){
			zeroFramedAry[i] = new int[numCols+2];
		}
		
		for(int i=0;i<4;i++){
			neighborAry[i] = 0;
		}
		
		//function calls
		connectedComponents component(numRows, numCols, minVal, maxVal);
		component.loadImage(zeroFramedAry,fileName);
		component.zeroFrame(zeroFramedAry);
		component.ConnectCC_Pass1(zeroFramedAry);
		component.prettyPrint(zeroFramedAry, outFile1, 1);
		component.ConnectCC_Pass2(zeroFramedAry);
		component.prettyPrint(zeroFramedAry, outFile1, 2);
		component.manageEQAry();
		var = component.ConnectCC_Pass3(zeroFramedAry);
		Property CC[var];
		component.loadStruct(CC, zeroFramedAry, var);
		component.printStruct(CC, var, outFile3);
		component.printEQAry(outFile1, "manageEQAry");
		component.prettyPrint(zeroFramedAry, outFile1, 3);
		component.printImage(zeroFramedAry, outFile2);
	}
	
	else cout<<"Couldn't retrieve data.";
	input.close();
	return 0;
}
