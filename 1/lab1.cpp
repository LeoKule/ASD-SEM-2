#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <cmath> // Для использования функции sqrt

using namespace std;

// Структура, представляющая точку на плоскости
struct Point {
    int x, y;
};

// Функция для нахождения самой левой нижней точки
Point findLeftmostPoint(vector<Point>& points) {
    Point cur_min{ 400, 400 }; // Изначально устанавливаем максимально возможные координаты
    for (const Point& p : points) {
        // Если текущая точка имеет меньшую y-координату или такую же y-координату, но меньшую x-координату
        if (p.y < cur_min.y || (p.y == cur_min.y && p.x < cur_min.x)) {
            cur_min = p; // Обновляем самую левую нижнюю точку
        }
    }
    return cur_min;
}

// Функция для определения ориентации трех точек (по или против часовой стрелки)
int orientation(Point a, Point b, Point c) {
    int area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area < 0) return -1; // По часовой стрелке
    else if (area == 0) return 0; // Точки лежат на одной прямой
    else return 1; // Против часовой стрелки
}

// Функция для вычисления расстояния между двумя точками
double distance(Point a, Point b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

// Функция для построения выпуклой оболочки по алгоритму "обертывание подарка"
vector<Point> giftWrapping(vector<Point>& points) {
    Point start_point = findLeftmostPoint(points); // Находим самую левую нижнюю точку
    vector<Point> hull; // Сюда будем добавлять точки оболочки
    do {
        hull.push_back(start_point); // Добавляем текущую точку в оболочку
        Point next_point = points[0];
        for (const Point& p : points) {
            // Определяем, является ли p более левой точкой, чем next_point
            int orient = orientation(start_point, next_point, p);
            if (orient == -1 || (orient == 0 && distance(start_point, p) > distance(start_point, next_point))) {
                next_point = p; // Обновляем следующую точку на оболочке
            }
        }
        start_point = next_point; // Переходим к следующей точке на оболочке
    } while (!(start_point.x == hull[0].x && start_point.y == hull[0].y)); // Пока не вернемся в начальную точку
    return hull;
}

int main() {
    int num_points = 15;
    vector<Point> points;

    // Генерируем случайные точки на плоскости
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10);
    for (int i = 0; i < num_points; i++) {
        Point p;
        p.x = dis(gen); // Генерируем x-координату
        p.y = dis(gen); // Генерируем y-координату
        points.push_back(p); // Добавляем точку в вектор
    }

    // Строим выпуклую оболочку
    vector<Point> convex_hull = giftWrapping(points);

    // Выводим сгенерированные точки
    cout << "Generated points:" << endl;
    for (const Point& p : points) {
        cout << p.x << " " << p.y << endl;
    }
    cout << endl;

    // Выводим точки, составляющие выпуклую оболочку
    cout << "Convex hull points:" << endl;
    for (const Point& p : convex_hull) {
        cout << p.x << " " << p.y << endl;
    }

    return 0;
}
