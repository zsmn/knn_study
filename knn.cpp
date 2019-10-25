#include<bits/stdc++.h>
using namespace std;

#define qt_robosTime 8

enum scales
{
    HIGH_DEFENSE = -3,
    MEDIUM_DEFENSE = -2,
    LOW_DEFENSE = -1,
    LOW_ATTACK = 1,
    MEDIUM_ATTACK = 2,
    HIGH_ATTACK = 3
};

typedef struct{
    double enemies_our_side;
    double allies_our_side;
    double enemies_finalizations;
    double allies_finalizations;
    double enemies_ballpossession;
    double allies_ballpossession;
    double enemies_velocity[qt_robosTime];
    double allies_velocity[qt_robosTime];
    double enemies_passes;
    double allies_passes;

    double distance; // for knn
    int agressive_scale;
} Point;

bool cmp(Point a, Point b){
    return (a.distance < b.distance);
}

int classify(Point dataset[], int n, int k, Point p){
    double sigma = 2.0;
    // calculate distance from p to all dataset
    for(int i = 0; i < n; i++){
        int dif = 0;
        dif += pow(abs(p.enemies_our_side - dataset[i].enemies_our_side), sigma);
        dif += pow(abs(p.allies_our_side - dataset[i].allies_our_side), sigma);
        dif += pow(abs(p.our_finalizations - dataset[i].our_finalizations), sigma);
        dif += pow(abs(p.their_finalizations - dataset[i].their_finalizations), sigma);
        dif += pow(abs(p.our_ball_possession - dataset[i].our_ball_possession), sigma);
        dif += pow(abs(p.their_ball_possession - dataset[i].their_ball_possession), sigma);
        dataset[i].distance = pow(dif, 1.0/sigma); // mintowski distance
    }

    sort(dataset, dataset + n, cmp); // sort based in distance

    int freq[7] = {0}; // we have 6 groups (in enum)
    int best = 0; // looking for the best scale

    for(int i = 0; i < k; i++){ // look for the first k elements after sort
        freq[dataset[i].agressive_scale + 3]++; // +3 because offset (low defense starts with -3)
        if(freq[dataset[i].agressive_scale + 3] > best){
            best = dataset[i].agressive_scale; // if have a best scale, set it on best variable
        }
    }

    return best; // return best classification
}

void printAttributes(Point a, bool isDataset){
    cout << "Allies our side: " << a.allies_our_side << endl;
    cout << "Enemies our side: " << a.enemies_our_side << endl;
    cout << "Our ball possession: " << a.our_ball_possession << endl;
    cout << "Their ball possession: " << a.their_ball_possession << endl;
    cout << "Our finalizations: " << a.our_finalizations << endl;
    cout << "Their finalizations: " << a.their_finalizations << endl;
    if(isDataset){
        cout << "Distance: " << a.distance << endl;
        cout << "Scale: " << a.agressive_scale << endl;
    }
    cout << endl;
}

int main(){
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); // rand gen

    int n = 6; // Number of data points 
    int k = 3; // parameter k (k firsts will be analyzed)
    Point arr[n]; 

    // generating randomic points
    for(int i = 0; i < n; i++){
        arr[i].allies_our_side = rng() % 6;
        arr[i].enemies_our_side = rng() % 6;
        arr[i].our_ball_possession = rng() % 100;
        arr[i].their_ball_possession = abs(100 - arr[i].our_ball_possession);
        arr[i].our_finalizations = rng() % 10;
        arr[i].their_finalizations = rng() % 10;
    }

    // setting the scales to test
    arr[0].agressive_scale = LOW_DEFENSE;
    arr[1].agressive_scale = MEDIUM_DEFENSE;
    arr[2].agressive_scale = HIGH_DEFENSE;
    arr[3].agressive_scale = LOW_ATTACK;
    arr[4].agressive_scale = MEDIUM_ATTACK;
    arr[5].agressive_scale = HIGH_ATTACK;

    // generating a random configuration to test
    Point randomPoint;
    randomPoint.allies_our_side = rng() % 6;
    randomPoint.enemies_our_side = rng() % 6;
    randomPoint.our_ball_possession = rng() % 100;
    randomPoint.their_ball_possession = abs(100 -randomPoint.our_ball_possession);
    randomPoint.our_finalizations = rng() % 10;
    randomPoint.their_finalizations = rng() % 10;

    int classification = classify(arr, n, k, randomPoint);

    // printing for debug
    for(int i = 0; i < n; i++){
        cout << "Dataset id " << i << endl;
        printAttributes(arr[i], true);
    }

    cout << "Random point" << endl;
    printAttributes(randomPoint, false);

    cout << "Classified for: " << classification << endl;
}