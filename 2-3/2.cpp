#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <queue>
#include <algorithm> // Для использования функции remove

// Класс для представления графа
class Graph
{
    std::vector<std::vector<int>> adjacency_list; // Список смежности
    int Vertex; // Количество вершин

public:

    // Конструктор, который считывает граф из файла
    Graph(std::string s_file)
    {
        std::string str;
        std::ifstream file(s_file);

        // Считываем количество вершин из первой строки файла
        std::getline(file, str);
        Vertex = atoi(str.c_str());

        // Инициализируем векторы в списке смежности
        for (int i = 0; i < Vertex; i++)
        {
            adjacency_list.push_back({});
        }

        // Заполняем список смежности
        for (int i = 0; i < Vertex; i++)
        {
            std::getline(file, str);
            str.erase(remove(str.begin(), str.end(), ' '), str.end()); // Удаляем пробелы из строки

            for (int j = 0; j < str.size(); j++)
            {
                // Если есть ребро между вершинами i и j, добавляем j в список смежности i
                if (str[j] != '0')
                {
                    adjacency_list[i].push_back(j);
                }
            }
            str = ""; // Очищаем строку
        }
        file.close(); // Закрываем файл
    }

    // Функция обхода в ширину из заданной вершины
    std::vector<int> bfs(int start_Vertex)
    {
        std::vector<int> visited(Vertex);
        std::vector<int> distance(Vertex);
        std::queue<int> q;

        // Инициализируем массив расстояний очень большими значениями
        for (int i = 0; i < distance.size(); i++)
        {
            distance[i] = 999999;
        }

        visited[start_Vertex] = 1; // Помечаем начальную вершину как посещенную
        distance[start_Vertex] = 0; // Расстояние от начальной вершины до самой себя равно 0
        q.push(start_Vertex); // Добавляем начальную вершину в очередь

        // Обход в ширину
        while (!q.empty())
        {
            int cur_Vertex = q.front(); // Берем вершину из очереди
            q.pop();

            // Перебираем всех соседей текущей вершины
            for (int neighbor : adjacency_list[cur_Vertex])
            {
                if (visited[neighbor] == 0)
                {
                    visited[neighbor] = 1; // Помечаем соседа как посещенного
                    distance[neighbor] = 1 + distance[cur_Vertex]; // Обновляем расстояние до соседа
                    q.push(neighbor); // Добавляем соседа в очередь
                }
            }
        }
        return distance; // Возвращаем массив расстояний
    }

    // Функция для поиска компонент связности
    std::vector<int> find_connectivity_component()
    {
        int component = 0;
        std::vector<int> visited(Vertex);
        std::vector<int> component_table(Vertex);
        std::queue<int> q;

        // Обход всех вершин графа
        for (int i = 0; i < Vertex; i++)
        {
            // Если вершина не посещена, запускаем из нее поиск в ширину
            if (visited[i] != 1)
            {
                component += 1; // Увеличиваем номер текущей компоненты связности
                visited[i] = 1; // Помечаем вершину как посещенную
                q.push(i); // Добавляем вершину в очередь

                // Обход в ширину из текущей вершины
                while (!q.empty())
                {
                    int cur_Vertex = q.front();
                    q.pop();
                    component_table[cur_Vertex] = component; // Записываем номер компоненты для текущей вершины
                    // Перебираем всех соседей текущей вершины
                    for (int neighbor : adjacency_list[cur_Vertex])
                    {
                        if (visited[neighbor] == 0)
                        {
                            visited[neighbor] = 1; // Помечаем соседа как посещенного
                            q.push(neighbor); // Добавляем соседа в очередь
                        }
                    }
                }
            }
        }
        return component_table; // Возвращаем массив номеров компонент связности
    }
};

// Главная функция
int main()
{
    std::string file = "matrix.txt"; // Имя файла с матрицей смежности
    Graph gr(file); // Создаем объект класса Graph, передавая имя файла
    std::vector<int> dist = gr.bfs(0); // Запускаем поиск в ширину из вершины 0
    std::vector<int> comp = gr.find_connectivity_component(); // Находим компоненты связности
    // Выводим результаты
    std::cout << "Distances from vertex 0:" << std::endl;
    for (int i = 0; i < dist.size(); i++)
    {
        std::cout << i << " : " << dist[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Connectivity components:" << std::endl;
    for (int i = 0; i < comp.size(); i++)
    {
        std::cout << i << " : " << comp[i] << std::endl;
    }
    return 0;
}