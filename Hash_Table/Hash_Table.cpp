//Code a Hash table a load factor of 0.80 with the CRUD methods
//a = n/m, where n is number of entries occupied, and m is the number of bucket


#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>

using namespace std;

class HashTable {
private:
    // Vector de listas enlazadas para manejar colisiones
    vector<list<pair<string, string>>> table;
    int n; // Número de entradas ocupadas
    int m; // Número de cubetas
    const float loadFactor = 0.80; // Factor de carga máximo permitido

    // Función hash para calcular el índice de la cubeta basado en la clave
    int hashFunction(const string &key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % m;
        }
        return hash;
    }

    // Función para redimensionar la tabla hash cuando el factor de carga excede el límite
    void resize() {
        int old_m = m;
        m *= 2; // Duplicar el número de cubetas
        vector<list<pair<string, string>>> newTable(m);

        // Rehashing de todas las entradas en la nueva tabla
        for (int i = 0; i < old_m; ++i) {
            for (auto &entry : table[i]) {
                int newIndex = hashFunction(entry.first);
                newTable[newIndex].push_back(entry);
            }
        }
        table = move(newTable); // Reemplazar la tabla antigua con la nueva
    }

public:
    // Constructor para inicializar la tabla hash con un tamaño inicial
    HashTable(int size = 10) : n(0), m(size) {
        table.resize(m);
    }

    // Método para insertar un nuevo par clave-valor en la tabla hash
    void insert(const string &key, const string &value) {
        // Redimensionar si el factor de carga excede el límite
        if ((float)n / m >= loadFactor) {
            resize();
        }
        int index = hashFunction(key);
        // Verificar si la clave ya existe y actualizar el valor
        for (auto &entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        // Insertar el nuevo par clave-valor
        table[index].emplace_back(key, value);
        n++;
    }

    // Método para buscar un valor basado en la clave
    bool search(const string &key, string &value) {
        int index = hashFunction(key);
        for (auto &entry : table[index]) {
            if (entry.first == key) {
                value = entry.second;
                return true;
            }
        }
        return false;
    }

    // Método para actualizar el valor asociado a una clave existente
    void update(const string &key, const string &value) {
        int index = hashFunction(key);
        for (auto &entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        // Si la clave no existe, insertar el nuevo par clave-valor
        insert(key, value);
    }

    // Método para eliminar un par clave-valor de la tabla hash
    void remove(const string &key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                n--;
                return;
            }
        }
    }

    // Método para mostrar el contenido de la tabla hash
    void display() {
        for (int i = 0; i < m; ++i) {
            cout << "Bucket " << i << ": ";
            for (auto &entry : table[i]) {
                cout << "(" << entry.first << ", " << entry.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;

    // Insertar algunos pares clave-valor
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");
    ht.insert("key3", "value3");

    string value;
    // Buscar una clave
    if (ht.search("key2", value)) {
        cout << "Found key2: " << value << endl;
    } else {
        cout << "key2 not found" << endl;
    }

    // Actualizar el valor de una clave existente
    ht.update("key2", "new_value2");
    if (ht.search("key2", value)) {
        cout << "Updated key2: " << value << endl;
    }

    // Eliminar una clave
    ht.remove("key3");
    if (!ht.search("key3", value)) {
        cout << "key3 successfully removed" << endl;
    }

    // Mostrar el contenido de la tabla hash
    ht.display();

    return 0;
}