MAXN = 1000  # Максимальное количество вершин в графе, может быть изменено на любое необходимое значение

used = [False] * MAXN  # Массив для отслеживания посещенных вершин
comp = []  # Список для хранения текущей компоненты связности

def bfs(g, v):
    queue = [v]  # Инициализируем очередь с начальной вершиной
    used[v] = True  # Отмечаем начальную вершину как посещенную
    comp.append(v)  # Добавляем начальную вершину в текущую компоненту связности

    front = 0  # Указатель на начало очереди

    while front < len(queue):
        current = queue[front]  # Извлекаем текущую вершину из очереди
        front += 1  # Сдвигаем указатель вперед

        for to in g[current]:  # Проходим по всем смежным вершинам текущей вершины
            if not used[to]:  # Если вершина еще не была посещена
                used[to] = True  # Отмечаем вершину как посещенную
                queue.append(to)  # Добавляем вершину в очередь
                comp.append(to)  # Добавляем вершину в текущую компоненту связности

def find_comps(number, g):
    n = number  # Количество вершин в графе

    for i in range(n):
        used[i] = False  # Инициализируем массив посещенных вершин как непосещенные

    for i in range(n):
        if not used[i]:  # Если вершина еще не была посещена
            comp.clear()  # Очищаем список текущей компоненты связности
            bfs(g, i)  # Запускаем BFS для нахождения всей компоненты связности, содержащей вершину i

            print("Component:", end="")  # Выводим метку компоненты связности
            for j in comp:
                print(f' {j}', end="")  # Выводим все вершины текущей компоненты связности
            print()  # Переход на новую строку для следующей компоненты

# Чтение матрицы смежности из файла "matrix.txt"
with open("matrix.txt") as f:
    matrix = f.readlines()  # Читаем все строки файла
    matrix = [i.strip().split() for i in matrix]  # Разделяем строки на отдельные элементы и удаляем пробелы
    matrix = [list(map(int, i)) for i in matrix]  # Преобразуем элементы в целые числа

    # Пример матрицы смежности:
    # matrix = [
    # [1, 0, 0, 0, 0, 0],
    # [0, 1, 0, 0, 0, 0],
    # [0, 0, 1, 0, 0, 0],
    # [0, 0, 0, 1, 0, 0],
    # [0, 0, 0, 0, 1, 0],
    # [0, 0, 0, 0, 0, 1],]

    n = len(matrix)  # Определяем количество вершин в графе на основе длины матрицы
    g = [[] for _ in range(n)]  # Создаем пустой список смежности для каждой вершины

    for i in range(n):
        for j in range(n):
            if matrix[i][j] == 1:  # Если вершины i и j соединены (матрица[i][j] == 1)
                g[i].append(j)  # Добавляем вершину j в список смежности вершины i

    find_comps(n, g)  # Находим и выводим компоненты связности графа
