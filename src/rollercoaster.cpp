#include<bits/stdc++.h>

#define MAXN 100000

using namespace std;

int n, maxdrop, x;
int coast[MAXN];
bool motor[MAXN];


int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	in >> n;
	for(int i=0; i<n; i++) in >> coast[i];
	for(int i=0; i<n-2; i++) if(coast[i+2]-coast[i+1]==coast[i+1]-coast[i] && coast[i+1]>coast[i]) motor[i]=1, motor[i+1]=1, motor[i+2]=1;
	maxdrop=coast[0];
	//for(int i=0; i<n; i++) cout << motor[i] << " ";
	//cout << endl;
	for(int i=0; i<n; i++){
		//cout << i << " ";
	    if(motor[i] && !motor[i+1]){
	    	//cout << "fine motori ";
	        if(coast[i+1]>=coast[i]) n=0;
	        else maxdrop=coast[i];
	        //cout << " maxdrop = " << maxdrop << endl;
	    }
	    else if(!motor[i] && i!=0){
	    	//cout << "non motore";
	        if(coast[i]>=coast[i-1] && coast[i]>coast[i+1] && coast[i]<maxdrop){
	        	maxdrop=coast[i];
	        	//cout << "sono in cima, maxdrop = " << maxdrop << endl;
	        }
	        else if(coast[i]>=maxdrop){
	            i--;
	            n=0;
	        }
	        //else cout << endl;
	    }
	    
		x=i;
	}
	out << x;
}