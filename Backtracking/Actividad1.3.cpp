//Actividad 1.3 Implementación de la técnica de programación "backtracking" y "ramificación y poda"

#include <iostream>
#include <vector>

#define WALL 0
#define PATH 1

// Direcciones de movimiento: derecha, abajo, izquierda, arriba
int rowDir[] = {0, 1, 0, -1};
int colDir[] = {1, 0, -1, 0};

// Función para imprimir el laberinto
void printMaze(const std::vector<std::vector<int>>& maze) {
    for (const auto& row : maze) {
        for (int cell : row)
            std::cout << cell << " ";
        std::cout << std::endl;
    }
}

// Función de backtracking para encontrar el camino
bool solveMazeBacktracking(std::vector<std::vector<int>>& maze, int x, int y, std::vector<std::vector<int>>& solution) {
    int M = maze.size();
    int N = maze[0].size();

    // Si llegamos al destino, marcamos la casilla y devolvemos verdadero
    if (x == M - 1 && y == N - 1) {
        solution[x][y] = PATH;
        return true;
    }

    // Verifica si la casilla actual es válida
    if (x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == PATH && solution[x][y] == WALL) {
        // Marca la casilla actual como parte del camino
        solution[x][y] = PATH;

        // Recurre por todas las direcciones posibles
        for (int dir = 0; dir < 4; ++dir) {
            int newX = x + rowDir[dir];
            int newY = y + colDir[dir];

            if (solveMazeBacktracking(maze, newX, newY, solution))
                return true;

            // Si no se encuentra solución, desmarca la casilla (backtrack)
            solution[x][y] = WALL;
        }
    }

    return false;
}

int main() {
    int M, N;
    std::cin >> M >> N;
    std::vector<std::vector<int>> maze(M, std::vector<int>(N));
    std::vector<std::vector<int>> solution(M, std::vector<int>(N, WALL));

    // Lee el laberinto
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            std::cin >> maze[i][j];

    // Resuelve el laberinto usando backtracking
    if (solveMazeBacktracking(maze, 0, 0, solution)) {
        printMaze(solution);
    } else {
        std::cout << "No hay solución" << std::endl;
    }

    return 0;
}
