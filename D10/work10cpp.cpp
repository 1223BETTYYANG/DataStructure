#include<iostream>
#include<queue>


using namespace std;

class Node
{
public:
	int num;
	int back;
	Node* next;
	Node(int n)
	{
		back = 0;
		num = n;
		next = NULL;
	}
};

class Graph 
{
public:
	Graph(int n);
	void addEgde(int i, int j);
	int* findPath(int source, int destination);
	Node** listpoint;
	int pointsize;
	bool rFindPath(Node* s, int*& Path, int*& reach, int destination);
	void clear();

};

Graph::Graph(int n) 
{
	pointsize = n;
	listpoint = new Node * [pointsize];
	for (int i = 0; i <= n - 1; i++) {
		listpoint[i] = new Node(i + 1);
	}
}

void Graph::addEgde(int i, int j) 
{
	Node* add = new Node(j);
	Node* tmp = listpoint[i - 1];
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = add;
}

void Graph::clear() 
{
	for (int i = 0; i <= pointsize - 1; i++) {
		listpoint[i]->back = 0;
	}
}

bool Graph::rFindPath(Node* source, int*& Path, int*& reach, int destination) 
{
	reach[source->num] = 1;
	int result = 0;
	Node* tmp = new Node(-1);
	int* reverPath = new int[pointsize];
	for (int i = 0; i <= pointsize - 1; i++) {
		reverPath[i] = -1;
	}
	int length = 0;
	queue<Node*> q;
	q.push(source);
	while (!q.empty()) {
		Node* w = q.front();
		q.pop();
		Node* u = w->next;
		while (u != NULL) {
			if (reach[u->num] == 0) 
			{
				listpoint[u->num - 1]->back = w->num;
				q.push(listpoint[u->num - 1]);
				reach[u->num] = 1;
				if (u->num == destination) 
				{
					result = 1;
					break;
				}
			}
			u = u->next;
		}
		if (result == 1) 
		{
			break;
		}
	}
	tmp = listpoint[destination - 1];
	if (result == 1) 
	{
		int i = 0;
		while (tmp->back != 0) 
		{
			reverPath[i] = tmp->num;
			i++;
			tmp = listpoint[tmp->back - 1];
		}
		int j = 2;
		for (; i >= 1; i--) 
		{
			Path[j] = reverPath[i - 1];
			j++;
		}
	}
	clear();
	if (result == 1) {
		return true;
	}
	else 
	{
		return false;
	}
}

int* Graph::findPath(int source, int destination) {
	this->clear();
	int* Path = new int[pointsize + 1];
	for (int i = 0; i <= pointsize; i++) 
	{
		Path[i] = -1;
	}
	Path[1] = source;
	int* reach = new int[pointsize + 1];
	for (int i = 1; i <= pointsize; i++) {
		reach[i] = 0;
	}
	Node* begin = this->listpoint[source - 1];
	if (source == destination || rFindPath(begin, Path, reach, destination)) 
	{
		int steps = 1;
		while (Path[steps] != -1) {
			steps++;
		}
		Path[0] = steps - 2;
	}
	else 
	{
		delete Path;
		Path = NULL;
	}
	delete reach;
	return Path;
}
int main() {
	int mapsize = 6;
	Graph map(mapsize);
	map.addEgde(1, 2);
	map.addEgde(1, 3);
	map.addEgde(2, 3);
	map.addEgde(3, 4);
	map.addEgde(3, 6);
	map.addEgde(4, 5);
	map.addEgde(6, 5);
	
	int* resolve;
	resolve = map.findPath(1, 6);
	cout<<"-----findpath:1-6-----"<<endl;
	cout<<resolve[0]<<"footprints:";
	int j = 1;
	if (resolve != NULL) 
    {
		while (resolve[j] != -1) {
			if(resolve[j+1] == -1)
		{
			cout << resolve[j];
		}
		else
		{
			cout << resolve[j] << "->";
		}
			j++;
		}
		cout << endl;
	}
	else {
		cout << "No way!" << endl;
	}
	int* resolve1;
	resolve1 = map.findPath(1, 5);
	int i = 1;
	cout<<"-----findpath:1-5-----"<<endl;
	cout<<resolve1[0]<<"footprints:";
	while (resolve1[i] != -1) {
		if(resolve1[i+1] == -1)
		{
			cout << resolve1[i];
		}
		else
		{
			cout << resolve1[i] << "->";
		}
		i++;
	}
	cout << endl;

	return 0;
}
