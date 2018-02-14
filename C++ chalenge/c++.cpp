#include<bits/stdc++.h>
using namespace std;
pair<int,int> GetFarthestPoint(pair<int,int> curr,const vector<string> &input,vector<vector<int> > &visited)
{
	//for bfs
	int numrows = input.size();
	int numcols = input[0].size();
	queue<pair<int,int> > q;
	visited[curr.first][curr.second] = 1;
	q.push(curr);
	while(q.size())
	{
		curr = q.front();
		q.pop();
		for(int i=-1;i<=1;i++)
			for(int j=-1;j<=1;j++)
			{
				if(abs(i+j)!=1) continue;
				if((curr.first+i)<numrows && (curr.first+i)>=0 && (curr.second+j)<numcols && (curr.second+j)>=0 && visited[curr.first+i][curr.second+j] == 0 && input[curr.first+i][curr.second+j] == '.')
				{
					visited[curr.first+i][curr.second+j] = 1;
					q.push(make_pair(curr.first+i,curr.second+j));
				}
			}
	}
	return curr;
}
vector<string> GetInput()
{
	vector<string> input;
	char filename[] = "input.txt";
	ifstream in(filename);
	for(string s;getline(in,s);)
	{
		input.push_back(s);
	}
	return input;
}
vector<pair<int,int> > GetStartDots(const vector<string> &input)
{
	int numrows = input.size();
	int numcols = input[0].size();
	vector<pair<int,int> > startDots;
	vector<vector<int> > visited(numrows,vector<int> (numcols,0));
	for(int i=0;i<numrows;i++)
		for(int j=0;j<numcols;j++)
			if(input[i][j] == '.' && visited[i][j] == 0)
			{
				startDots.push_back(GetFarthestPoint(make_pair(i,j),input,visited));
			}
	return startDots;
}
int GetFarthestPointDistance(pair<int,int> curr,const vector<string> &input,vector<vector<int> > &visited)
{
	//for bfs
	int numrows = input.size();
	int numcols = input[0].size();
	int maxDistance = 1;
	pair<int,int> separator(-1,-1);//to indicate increase in distance
	queue<pair<int,int> > q;
	visited[curr.first][curr.second] = 1;
	q.push(curr);
	q.push(separator);
	while(q.size())
	{
		curr = q.front();
		q.pop();
		if(curr == separator)
		{
			if(q.empty())
				return maxDistance;
			else
			{
				maxDistance++;
				q.push(separator);
			}
		}
		for(int i=-1;i<=1;i++)
			for(int j=-1;j<=1;j++)
			{
				if(abs(i+j)!=1) continue;
				if((curr.first+i)<numrows && (curr.first+i)>=0 && (curr.second+j)<numcols && (curr.second+j)>=0 && visited[curr.first+i][curr.second+j] == 0 && input[curr.first+i][curr.second+j] == '.')
				{
					visited[curr.first+i][curr.second+j] = 1;
					q.push(make_pair(curr.first+i,curr.second+j));
				}
			}
	}
	return maxDistance;
}
void getFinalStartPoint(const vector<string> &input, const vector<pair<int,int> > &startDots, pair<int,int> &finalStartPoint,int &maxDistance)
{
	int numrows = input.size();
	int numcols = input[0].size();
	maxDistance = 0;
	vector<vector<int> > visited(numrows,vector<int> (numcols,0));
	for(int i=0;i<startDots.size();i++)
	{
		int currentDistance = GetFarthestPointDistance(startDots[i],input,visited);
		if(currentDistance>maxDistance)
		{
			maxDistance = currentDistance;
			finalStartPoint = startDots[i];
		}
	}
}
void dfs(vector<string> &input, const int &numrows, const int &numcols, int maxDistance, pair<int,int> curr, vector<vector<int> > &visited, vector<vector<int> > &mark, bool &shouldMark,int mydist = 1)
{
	visited[curr.first][curr.second] = 1;
	if(maxDistance == mydist)
	{
		mark[curr.first][curr.second] = mydist-1;
		shouldMark = true;
		return;
	}
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)
		{
			if(abs(i+j)!=1) continue;
			if((curr.first+i)<numrows && (curr.first+i)>=0 && (curr.second+j)<numcols && (curr.second+j)>=0 && visited[curr.first+i][curr.second+j] == 0 && input[curr.first+i][curr.second+j] == '.')
			{
				dfs(input,numrows,numcols,maxDistance,make_pair(curr.first+i,curr.second+j),visited,mark,shouldMark,mydist+1);
				if(shouldMark)
				{
					mark[curr.first][curr.second] = mydist-1;
					return;
				}
			}
		}
}
void markPath(vector<string> &input,pair<int,int> finalStartPoint,int maxDistance)
{
	int numrows = input.size();
	int numcols = input[0].size();
	vector<vector<int> > visited(numrows,vector<int> (numcols,0));
	vector<vector<int> > mark(numrows,vector<int> (numcols,-1));
	bool shouldMark = false;
	dfs(input,numrows,numcols,maxDistance,finalStartPoint,visited,mark,shouldMark);
	char filename[] = "output.txt";
	ofstream outFile(filename);
	outFile<<maxDistance<<'\n';
	for(int i=0;i<numrows;i++)
	{
		for(int j=0;j<numcols;j++)
		{
			if(mark[i][j]==-1)
			{
				outFile<<input[i][j];
			}
			else
				outFile<<mark[i][j];
		}
		outFile<<'\n';
	}
}
int main()
{
	vector<string> input = GetInput();
	vector<pair<int,int> > startDots = GetStartDots(input);
	pair<int,int> finalStartPoint(-1,-1);
	int maxDistance;
	getFinalStartPoint(input,startDots,finalStartPoint,maxDistance);
	cout<<maxDistance<<endl;	
	// cout<<finalStartPoint.first<<" "<<finalStartPoint.second<<endl;
	markPath(input,finalStartPoint,maxDistance);
}