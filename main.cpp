//4-Connected Component Algorithm
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Property{
	
};

class connectedComponents{
	public:
	
	int numRows, numCols, minVal, maxVal, newMin, newMax, newLabel = 0;
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
	}
	
	//destructor
	~connectedComponents(){
		for(int i=0;i<numRows+2;i++){
			delete [] zeroFramedAry[i];
		}
		delete [] neighborAry;
		delete [] EQAry;
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
		
		for(int i=0;i<numRows+2;i++){
			for(int j=0;j<numCols+2;j++){
				cout<<zeroFramedAry[i][j]<<" ";
			}
			cout<<endl;
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
		/*
		for(int i=0;i<numRows+2;i++){
			for(int j=0;j<numCols+2;j++){
				cout<<zeroFramedAry[i][j];
			}
			cout<<endl;
		}
		in.close();
		*/
	}
	
	void loadNeighbors(int** zeroFramedAry, int neighborAry[], int r, int c){
		
		for(int i=0;i<4;i++){
			neighborAry[i] = 0;
		}
		
		if(zeroFramedAry[r-1][c]!=0){
			//cout<<" hit this please?"<<endl;
			for(int i=0;i<4;i++){
				if(neighborAry[i] == 0){
					neighborAry[i] = zeroFramedAry[r-1][c];
					//cout<<"Array: "<<zeroFramedAry[r-1][c];
				}
				//cout<<i<<" hit this "<<endl;
				break;
			}
		}
		if(zeroFramedAry[r][c-1]!=0){
			for(int i=0;i<4;i++){
				if(neighborAry[i] == 0){
					neighborAry[i] = zeroFramedAry[r][c-1];	
				}
				//cout<<i<<" hit here? "<<endl;
				break;
			}
		}
		/*
		for(int i=0;i<4;i++)
			 cout<<neighborAry[i]<<" ";
		cout<<endl;
		/*
		int currNum=0;
		switch(pass){
			case 1:
				for(int i=1;i<numRows+1;i++){
					for(int j=1;j<numCols+1;j++){
						neighborAry[0] = zeroFramedAry[i-1][j];
						neighborAry[1] = zeroFramedAry[i][j-1];
						
						if(neighborAry[0]==0 && neighborAry[1]==0){
							ConnectCC_Pass1(1, newLabel, zeroFramedAry, i, j);
						}
						
						for(int m=0;m<2;m++){
							if(neighborAry[m]!=0)
								currNum = neighborAry[m];
						}		
						for(int n=0;n<2;n++){
							if(neighborAry[n]!=0){
						
								if(neighborAry[n]!=currNum)
									ConnectCC_Pass1(3, newLabel, zeroFramedAry, i, j);
										
								else ConnectCC_Pass1(2, newLabel, zeroFramedAry, i, j);
							}
						}
						
						else if(neighborAry[0]!=neighborAry[1]){
							if(neighborAry[0]!=0)
								currNum = neighborAry[0];
							if(neighborAry[1]!=0)
								currNum = neighborAry[1];
							if(neighborAry[0]==0||neighborAry[1]==0)
								ConnectCC_Pass1(2, newLable, zeroFramedAry[i][j]);
						}
						
						//else ConnectCC_Pass1(3, newLable, zeroFramedAry[i][j]);
						
						
					
					}
				}
				cout<<"This is pass 1..."<<endl;
				break;
			
			case 2:
				cout<<"This is pass 2..."<<endl;
				break;
		}
		*/
	}
	
	void ConnectCC_Pass1(int** zeroFramedAry){
		
		for(int i=1;i<numRows+1;i++){
			for(int j=1;j<numCols+1;j++){
				if(zeroFramedAry[i][j]>0){
					
					loadNeighbors(zeroFramedAry,neighborAry,i,j);
					
					//Case 1
					if(neighborAry[0]==0 && neighborAry[1]==0){
						newLabel++;
						cout<<"newLabel: "<<newLabel<<endl;
						zeroFramedAry[i][j] = newLabel;
					}
				
					//Case 2
					else if(neighborAry[0]==0 && neighborAry[1]!=0){
						zeroFramedAry[i][j] = neighborAry[1];
					}
					else if(neighborAry[0]!=0 && neighborAry[1]==0){
						zeroFramedAry[i][j] = neighborAry[0];
					}
					else if(neighborAry[0]==neighborAry[1]){
						zeroFramedAry[i][j] = neighborAry[0];
					}
					
					//Case 3
					else if(neighborAry[0]!=neighborAry[1]){
						int minLabel = 0;
						minLabel = neighborAry[0];
						if (neighborAry[1]<neighborAry[0])
							minLabel = neighborAry[1];
						zeroFramedAry[i][j] = minLabel;
					}
				}
			}
		}
		
		cout<<"No Top or Left Neighbors: "<<newLabel<<endl;
		
		for(int i=0;i<numRows+2;i++){
			for(int j=0;j<numCols+2;j++){
				cout<<zeroFramedAry[i][j]<<" ";
			}
			cout<<endl;
		}
	}
};

int main(int argc, char* argv[]){
	ifstream input (argv[1]);
	string fileName = argv[1];
	//ofstream outFile1 (argv[2]);
	//ofstream outFile2 (argv[3]);
	//ofstream outFile3 (argv[4]);
	int numRows, numCols, minVal, maxVal, newMin, newMax;
	int newLabel = 0;
	int** zeroFramedAry;
	int neighborAry[4];
	int* EQAry;
	
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
		/*
		//initializing array
		for(int i=0;i<numRows+2;i++){
			for(int j=0;j<numCols+2;j++){
				zeroFramedAry[i][j] = 0;
			}
		}
		*/
		connectedComponents component(numRows, numCols, minVal, maxVal);
		component.loadImage(zeroFramedAry,fileName);
		component.zeroFrame(zeroFramedAry);
		//cout<<"This "<<newLabel<<endl;
		component.ConnectCC_Pass1(zeroFramedAry);
		//component.loadNeighbors(zeroFramedAry,neighborAry,newLabel,1);
		
		//cout<<"That "<<newLabel<<endl;
	}
	
	else cout<<"Couldn't retrieve data.";
	input.close();
	return 0;
}
