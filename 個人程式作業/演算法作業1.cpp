#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#define INF 0x6FFFFFFF
using namespace std;

struct Node{
	double x, y;

	friend bool operator < (const Node &a, const Node &b){
		if(a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	}
};

Node* Point = NULL;
/**
 * Calculate the distance between two points.
 * @return   [double, the distance between a and b]
 */
double _distance(const Node a, const Node b)
{
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double smaller(double p, double q)
{
	return (p > q) ? q : p;
}
double twopoint(const Node a,const Node b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
/**
 * [Find the closest distance, divide & conquer]
 * @param  left  [search from where]
 * @param  right [to where]
 * @return       [double, the smallest distance in the whole set of points]
 */
float Closest_distance(int left, int right)
{
	double d = INF;
	double distance_tmp;

	if(left == right)
		return 0;
	if(right == left+1)
		return twopoint( Point[left], Point[right] );
	int mid = (left + right) / 2;

	d = smaller( Closest_distance(left,mid) , Closest_distance(mid,right) );

	for(int i=mid-1; i>=left && Point[mid].x - Point[i].x < d; i--){
		for(int j = mid+1; j<=right && Point[j].x - Point[mid].x < d && fabs( Point[i].y - Point[j].y) < d; j++){
			distance_tmp = _distance( Point[i], Point[j] );
			if(distance_tmp < d)
				d = distance_tmp;
		}
	}
	return d;
}

int main()
{
    int n;
    cin>>n;
    Point = new Node[n];
    for(int i=0; i<n ; i++){
    	cin>>Point[i].x>>Point[i].y;
    }
    sort(Point,Point+n);
    cout<<"¤Àªvªk"<<"O(nlgn)"<<endl;
    cout<<fixed<<setprecision(3)<<Closest_distance(0,n-1);
    return 0;
}
