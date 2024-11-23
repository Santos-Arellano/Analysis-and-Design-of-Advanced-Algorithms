/**
 * @file main.cpp
 * @brief Solución al problema de construcción de cerca mínima para ovejas usando Convex Hull
 * @author Santos Arellano A01643742
 * @date 21 Noviembre 2024
 * 
 * Este programa resuelve el problema de encontrar la cerca más pequeña posible que rodee
 * a un conjunto de ovejas en un plano 2D. Utiliza el algoritmo de Graham Scan para 
 * construir el Convex Hull y calcular el perímetro mínimo necesario.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <set>

using namespace std;

/**
 * @struct Point
 * @brief Estructura que representa un punto en el plano 2D
 */
struct Point {
    int x, y, index;
    
    Point(int x = 0, int y = 0, int idx = 0) : x(x), y(y), index(idx) {}
    
    /**
     * @brief Calcula la distancia euclidiana entre dos puntos
     * @param other Punto al cual calcular la distancia
     * @return Distancia euclidiana
     */
    double distanceTo(const Point& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
    
    // Operadores de comparación necesarios para ordenamiento
    bool operator<(const Point& other) const {
        if (y != other.y) return y < other.y;
        if (x != other.x) return x < other.x;
        return index < other.index;
    }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

/**
 * @brief Determina la orientación de tres puntos
 * @param p Primer punto
 * @param q Segundo punto
 * @param r Tercer punto
 * @return 0 si son colineales, 1 si están en sentido horario, 2 si están en sentido antihorario
 */
int orientation(const Point& p, const Point& q, const Point& r) {
    long long val = (long long)(q.y - p.y) * (r.x - q.x) - 
                    (long long)(q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

/**
 * @brief Compara dos puntos según su ángulo polar respecto a un punto base
 * @param p0 Punto base
 * @param p1 Primer punto a comparar
 * @param p2 Segundo punto a comparar
 * @return true si p1 debe ir antes que p2 en ordenamiento polar
 */
bool compareAngle(const Point& p0, const Point& p1, const Point& p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0) {
        return p1.distanceTo(p0) < p2.distanceTo(p0);
    }
    return o == 2;
}

/**
 * @brief Implementa el algoritmo de Graham Scan para construir el Convex Hull
 * @param points Vector de puntos de entrada
 * @return Vector de puntos que forman el Convex Hull
 */
vector<Point> grahamScan(vector<Point>& points) {
    if (points.size() <= 1) return points;
    if (points.size() == 2) return points;
    
    // Encontrar el punto más bajo y más a la izquierda
    int bottomIdx = 0;
    for (int i = 1; i < points.size(); i++) {
        if (points[i].y < points[bottomIdx].y || 
            (points[i].y == points[bottomIdx].y && points[i].x < points[bottomIdx].x)) {
            bottomIdx = i;
        }
    }
    swap(points[0], points[bottomIdx]);
    
    // Ordenar por ángulo polar
    Point p0 = points[0];
    sort(points.begin() + 1, points.end(), 
         [&p0](const Point& p1, const Point& p2) { return compareAngle(p0, p1, p2); });
    
    // Construir el hull
    vector<Point> hull;
    hull.push_back(points[0]);
    
    // Para puntos colineales, mantener solo el más lejano
    for (size_t i = 1; i < points.size(); ) {
        vector<Point> colinear;
        colinear.push_back(points[i]);
        size_t j = i + 1;
        while (j < points.size() && orientation(p0, points[i], points[j]) == 0) {
            colinear.push_back(points[j]);
            j++;
        }
        // Ordenar puntos colineales por distancia y tomar el más lejano
        sort(colinear.begin(), colinear.end(), 
             [&p0](const Point& p1, const Point& p2) {
                 return p1.distanceTo(p0) > p2.distanceTo(p0);
             });
        hull.push_back(colinear[0]);
        i = j;
    }
    
    if (hull.size() <= 2) return hull;
    
    // Procesar el resto de puntos
    vector<Point> finalHull;
    finalHull.push_back(hull[0]);
    finalHull.push_back(hull[1]);
    
    for (size_t i = 2; i < hull.size(); i++) {
        while (finalHull.size() >= 2 && 
               orientation(finalHull[finalHull.size()-2], 
                         finalHull.back(), hull[i]) != 2) {
            finalHull.pop_back();
        }
        finalHull.push_back(hull[i]);
    }
    
    return finalHull;
}

/**
 * @brief Calcula el perímetro del polígono formado por los puntos del hull
 * @param hull Vector de puntos que forman el hull
 * @return Perímetro del polígono
 */
double calculatePerimeter(const vector<Point>& hull) {
    if (hull.size() <= 1) return 0.0;
    if (hull.size() == 2) return 2 * hull[0].distanceTo(hull[1]);
    
    double perimeter = 0.0;
    for (size_t i = 0; i < hull.size(); i++) {
        perimeter += hull[i].distanceTo(hull[(i + 1) % hull.size()]);
    }
    return perimeter;
}

/**
 * @brief Verifica si un conjunto de puntos son colineales
 * @param points Vector de puntos a verificar
 * @return true si todos los puntos son colineales
 */
bool areCollinear(const vector<Point>& points) {
    if (points.size() <= 2) return true;
    for (size_t i = 2; i < points.size(); i++) {
        if (orientation(points[0], points[1], points[i]) != 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<Point> points;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            points.emplace_back(x, y, i + 1);
        }
        
        // Caso especial: un solo punto
        if (n == 1) {
            cout << "0.00" << endl;
            cout << "1" << endl;
            cout << endl;
            continue;
        }
        
        // Eliminar duplicados manteniendo el primer índice
        vector<Point> unique_points;
        sort(points.begin(), points.end());
        for (const Point& p : points) {
            if (unique_points.empty() || !(unique_points.back() == p)) {
                unique_points.push_back(p);
            }
        }
        
        // Caso especial: puntos colineales
        if (areCollinear(unique_points)) {
            sort(unique_points.begin(), unique_points.end(), 
                 [](const Point& p1, const Point& p2) {
                     if (p1.x != p2.x) return p1.x < p2.x;
                     return p1.y < p2.y;
                 });
            double length = unique_points.front().distanceTo(unique_points.back());
            cout << fixed << setprecision(2) << length << endl;
            cout << unique_points.front().index << " " << unique_points.back().index << endl;
            cout << endl;
            continue;
        }
        
        // Caso general: construir el convex hull
        vector<Point> hull = grahamScan(unique_points);
        double perimeter = calculatePerimeter(hull);
        
        cout << fixed << setprecision(2) << perimeter << endl;
        
        // Imprimir índices
        for (size_t i = 0; i < hull.size(); i++) {
            cout << hull[i].index;
            if (i < hull.size() - 1) cout << " ";
        }
        cout << endl << endl;
    }
    
    return 0;
}