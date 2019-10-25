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
        dif += pow(abs(p.allies_finalizations - dataset[i].allies_finalizations), sigma);
        dif += pow(abs(p.enemies_finalizations - dataset[i].enemies_finalizations), sigma);
        dif += pow(abs(p.allies_ballpossession - dataset[i].allies_ballpossession), sigma);
        dif += pow(abs(p.enemies_ballpossession - dataset[i].enemies_ballpossession), sigma);
        dif += pow(abs(p.enemies_passes - dataset[i].enemies_passes), sigma);
        dif += pow(abs(p.allies_passes - dataset[i].allies_passes), sigma);
        for(int j = 0; j < qt_robosTime; j++){
            dif += pow(abs(p.allies_velocity[j] - dataset[i].allies_velocity[j]), sigma);
            dif += pow(abs(p.enemies_velocity[j] - dataset[i].enemies_velocity[j]), sigma);
        }
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
    cout << "Our ball possession: " << a.allies_ballpossession << endl;
    cout << "Their ball possession: " << a.enemies_ballpossession << endl;
    cout << "Our finalizations: " << a.allies_finalizations << endl;
    cout << "Their finalizations: " << a.enemies_finalizations << endl;
    cout << "Our passes: " << a.enemies_passes << endl;
    cout << "Their passes: " << a.allies_passes << endl;

    for(int j = 0; j < qt_robosTime; j++){
        cout << "Allie Robot " << j << " speed: " << a.allies_velocity[j] << endl;
    }
    for(int j = 0; j < qt_robosTime; j++){
        cout << "Enemie Robot " << j << " speed: " << a.enemies_velocity[j] << endl;
    }
    
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
        arr[i].allies_our_side = rng() % qt_robosTime; 
        arr[i].enemies_our_side = rng() % qt_robosTime;
        arr[i].allies_ballpossession = rng() % 100;
        arr[i].enemies_ballpossession = abs(100 - arr[i].allies_ballpossession);
        arr[i].allies_finalizations = rng() % 10;
        arr[i].enemies_finalizations = rng() % 10;
        arr[i].allies_passes = rng() % 30;
        arr[i].enemies_passes = rng() % 30;

        for(int j = 0; j < qt_robosTime; j++){
            arr[i].allies_velocity[j] = rng() % 10;
            arr[i].enemies_velocity[j] = rng() % 10;
        }
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
    randomPoint.allies_our_side = rng() % qt_robosTime; 
    randomPoint.enemies_our_side = rng() % qt_robosTime;
    randomPoint.allies_ballpossession = rng() % 100;
    randomPoint.enemies_ballpossession = abs(100 - randomPoint.allies_ballpossession);
    randomPoint.allies_finalizations = rng() % 10;
    randomPoint.enemies_finalizations = rng() % 10;
    randomPoint.allies_passes = rng() % 30;
    randomPoint.enemies_passes = rng() % 30;

    for(int j = 0; j < qt_robosTime; j++){
        randomPoint.allies_velocity[j] = rng() % 10;
        randomPoint.enemies_velocity[j] = rng() % 10;
    }

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