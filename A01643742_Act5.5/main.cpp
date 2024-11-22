/*
 * Solution for Programming Exercises AA
 * Authors: Santos Arellano
 * Date: 21 November 2024
 * 
 * File: main.cpp
 * Description: Implementation of solutions for two algorithmic problems:
 * 1. Telecom Towers - Finding minimum towers to destroy to avoid interference
 * 2. Sheep Fence - Finding minimum perimeter fence for containing sheep
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <set>

using namespace std;

// Representa un punto en el plano
struct Point {
    int x, y, index;

    Point(int x = 0, int y = 0, int idx = 0) : x(x), y(y), index(idx) {}

    double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// ** Problema 1: Mínimo de torres a destruir **

// Determina si dos torres están demasiado cerca
bool isTooClose(const Point& p1, const Point& p2, double maxDist) {
    return p1.distanceTo(p2) <= maxDist;
}

// Calcula el número mínimo de torres a destruir para evitar interferencia
int minTowersToDestroy(vector<Point>& points, double maxDist) {
    int n = points.size();
    vector<bool> destroyed(n, false);

    int towersDestroyed = 0;
    for (int i = 0; i < n; ++i) {
        if (destroyed[i]) continue;
        for (int j = i + 1; j < n; ++j) {
            if (!destroyed[j] && isTooClose(points[i], points[j], maxDist)) {
                destroyed[j] = true; // Marcar torre como destruida
                ++towersDestroyed;
            }
        }
    }

    return towersDestroyed;
}

// ** Problema 2: Cerca mínima **

// Determina la orientación de tres puntos
int orientation(Point p, Point q, Point r) {
    long long val = (long long)(q.y - p.y) * (r.x - q.x) - 
                    (long long)(q.x - p.x) * (r.y - q.y);
    return (val == 0) ? 0 : (val > 0 ? 1 : 2);
}

// Convex Hull usando Graham Scan
vector<Point> grahamScan(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return points;

    // Encontrar el punto más bajo y más a la izquierda
    auto it = min_element(points.begin(), points.end());
    swap(points[0], *it);

    Point p0 = points[0];

    // Ordenar por ángulo polar respecto a p0
    sort(points.begin() + 1, points.end(), [&](Point& p1, Point& p2) {
        int o = orientation(p0, p1, p2);
        if (o == 0) return p1.distanceTo(p0) < p2.distanceTo(p0);
        return o == 2;
    });

    vector<Point> hull = {points[0], points[1]};
    for (int i = 2; i < n; ++i) {
        while (hull.size() > 1 && 
               orientation(hull[hull.size() - 2], hull.back(), points[i]) != 2) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    return hull;
}

// Calcula el perímetro de un Convex Hull
double calculatePerimeter(const vector<Point>& hull) {
    if (hull.size() < 2) return 0.0;

    double perimeter = 0.0;
    for (size_t i = 0; i < hull.size(); ++i) {
        perimeter += hull[i].distanceTo(hull[(i + 1) % hull.size()]);
    }
    return perimeter;
}

// ** Función principal **
int main() {
    int t; // Número de casos de prueba
    cin >> t;

    while (t--) {
        int n;
        double maxDist;
        cin >> n >> maxDist;

        vector<Point> points;
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            points.emplace_back(x, y, i + 1);
        }

        // ** Problema 1: Calcular el mínimo de torres a destruir **
        int destroyed = minTowersToDestroy(points, maxDist);
        cout << "Minimum towers destroyed: " << destroyed << endl;

        // ** Problema 2: Calcular el perímetro de la cerca mínima **
        vector<Point> unique_points(points.begin(), points.end());
        sort(unique_points.begin(), unique_points.end());
        unique_points.erase(unique(unique_points.begin(), unique_points.end()), unique_points.end());

        vector<Point> hull = grahamScan(unique_points);
        double perimeter = calculatePerimeter(hull);

        cout << fixed << setprecision(2) << "Minimum Fence Perimeter: " << perimeter << endl;
    }

    return 0;
}
