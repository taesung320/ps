#include<iostream>
#include<string>
#include<vector>
#include<utility>
using namespace std;
typedef pair<int,int> p;
vector<string> arr;
int R,C,cnt=1;
p scv;
vector<vector<int>> goal;
vector<bool> gl;
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1};
int c2d(char c){
	return (c=='U'?0:(c=='D'?1:(c=='L'?2:(c=='R'?3:4))));
}
string isComplete(){
	for(int i=1;i<gl.size();i++){
		if(gl[i]==false) return "incomplete";
	}
	return "complete";
}
bool moveBox(int x,int y,int d){
	int nx=x+dx[d];
	int ny=y+dy[d];
	char np=arr[nx][ny];
	bool canMove=((np=='.'||np=='+'));
	if(canMove){
		if(arr[x][y]=='B'){
			arr[x][y]='+';
			gl[goal[x][y]]=false;
		}else{
			arr[x][y]='.';
		}
		if(np=='+'){
			arr[nx][ny]='B';
			gl[goal[nx][ny]]=true;
		}else{
			arr[nx][ny]='b';
		}
	}
	return canMove;
}
void moveScv(int dr){
	int cx=scv.first;
	int cy=scv.second;
	int nx=cx+dx[dr];
	int ny=cy+dy[dr];
	char np=arr[nx][ny];
	bool canMove=((np=='.'||np=='+')||((np=='b'||np=='B')&&moveBox(nx,ny,dr)));
	if(canMove==true){
		arr[cx][cy]=(arr[cx][cy]=='W'?'+':'.');
		arr[nx][ny]=(arr[nx][ny]=='+'?'W':'w');
		scv={nx,ny};
	}
}
void printArr(){
	cout<<"Game "<<cnt<<": "<<isComplete()<<"\n";
	for(int i=0;i<R;i++){
		for(int j=0;j<C;j++){
			cout<<arr[i][j];
		}
		cout<<"\n";
	}
	cnt++;
}
int main(){
	while(true){
		cin>>R>>C;
		if(!(R||C)) return 0 ;
		arr.clear();
		gl.clear();
		gl.push_back(0);
		vector<vector<int>> temp(R);
		for(int i=0;i<R;i++)
			temp[i].resize(C);
		for(int i=0;i<R;i++){
			string s;
			cin>>s;
			arr.push_back(s);
			for(int j=0;j<C;j++){
				if(arr[i][j]=='w'||arr[i][j]=='W'){
					scv={i,j};
					if(arr[i][j]=='W')
					{
						temp[i][j]=gl.size();
						gl.push_back(false);
					}
				}else if(arr[i][j]=='+'){
					temp[i][j]=gl.size();
					gl.push_back(false);
				}else if(arr[i][j]=='B'){
					temp[i][j]=gl.size();
					gl.push_back(true);
				}
			}
		}
		goal=temp;
		string cmnd;
		cin>>cmnd;
		for(int i=0;i<cmnd.size();i++){
			moveScv(c2d(cmnd[i]));
			if(isComplete()=="complete"){
				break;
			}
		}
		printArr();
	}
}