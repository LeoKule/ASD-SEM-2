def make_graph(matrix):
    n = len(matrix)
    temp_graph = [[] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if matrix[i][j] == 1:
                temp_graph[i].append(j)
    return temp_graph

def dfs1(graph,v, used, stack):
    used[v] = True
    for to in graph[v]:
        if not used[to]:
            dfs1(graph, to, used, stack)
    stack.append(v)

def dfs2(graph, v, component, used):
    used[v] = True
    component.append(v)
    for neighbor in graph[v]:
        if not used[neighbor]:
            dfs2(graph, neighbor, component, used)

def scc_comps(matrix):
    n = len(matrix)  # Получаем количество вершин в графе
    g = make_graph(matrix)  # Создаем граф из матрицы смежности
    used = [False] * n  # Массив для отслеживания посещенных вершин
    stack = []  # Стек для хранения вершин в порядке завершения их обработки

    # Создаем транспонированную матрицу смежности
    matrix_t = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(n):
            matrix_t[i][j] = matrix[j][i]

    h = make_graph(matrix_t)  # Создаем граф из транспонированной матрицы смежности

    # Проводим первый обход в глубину для исходного графа
    for i in range(n):
        if not used[i]:
            dfs1(g, i, used, stack)

    scc_list = []
    used = [False] * n

    # Проводим второй обход в глубину для транспонированного графа
    while stack:
        u = stack.pop()
        if not used[u]:
            component = []
            dfs2(g, u, component, used)
            scc_list.append(component)

    return scc_list



with open("matrix.txt") as f:
    matrix = f.readlines()  # Читаем все строки из файла
    matrix = [i.strip().split() for i in matrix]  # Разделяем строки на отдельные элементы
    matrix = [list(map(int, i)) for i in matrix]  # Преобразуем элементы в целые числа

    scc = scc_comps(matrix)  # Находим компоненты сильной связности
    print(scc)  # Выводим список компонент сильной связности

