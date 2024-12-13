#include <iostream>
#include <fstream>
#include <queue> // очередь
using namespace std;
int main()
{
    ofstream connected("связный.txt");
    ofstream nooriented("неориентированный + неполный.txt");
    ofstream loops("петли.txt");
    ofstream cycles("циклы.txt");
    ofstream suspended("взвешенный.txt");
    ofstream ribs_connected("ribs_connected.txt");
    ofstream ribs_nooriented("ribs_nooriented.txt");
    ofstream ribs_loops("ribs_loops.txt");
    ofstream ribs_cycles("ribs_cycles.txt");
    ofstream ribs_suspended("ribs_suspended.txt");

    queue<int> Queue;//connected
    queue<int> Queue1;
    queue<int> Queue2;
    queue<int> Queue3;
    queue<int> Queue4;

    setlocale(LC_ALL, "Russian");
    int n, m, node = 0;

    cout << "Введите количество вершин:"; cin >> n;
    m = n;

    int** connect = new int* [n];//создание динамического массива связного графа
    for (int i = 0; i < n; ++i)
        connect[i] = new int[m];
    int** noorient = new int* [n];//создание динамического массива для неориентированного графа
    for (int i = 0; i < n; ++i)
        noorient[i] = new int[m];
    int** cycle = new int* [n];//создание динамического массива для графа с циклами
    for (int i = 0; i < n; ++i)
        cycle[i] = new int[m];
    int** loop = new int* [n];//создание динамического массива для графа с петлями
    for (int i = 0; i < n; ++i)
        loop[i] = new int[m];
    int** suspend = new int* [n];//создание динамического массива для взвешенного графа
    for (int i = 0; i < n; ++i)
        suspend[i] = new int[m];

    for (int i = 0; i < n; i++)//связный  И неориентированный + связный + неполный И наличие циклов
    {
        for (int j = 0; j < m; j++)
        {
            suspend[i][j] = rand() % 10;

            connect[i][j] = rand() % 2;
            noorient[i][j] = rand() % 2;
            cycle[i][j] = rand() % 2;
            loop[i][j] = rand() % 2;
            if (i == j) loop[i][j] = 1;
        }
        *noorient[i] = rand() % 1;
    }

    int* nodes = new int[n];// вершины графа
    for (int i = 0; i < n; i++)
        nodes[i] = 0;// исходно все вершины равны 0
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty())
    { // пока очередь не пуста
        int node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < n; j++)
        { // проверяем для нее все смежные вершины
            if (connect[node][j] == 1 && nodes[j] == 0)
            { // если вершина смежная и не обнаружена
                Queue.push(j); // добавляем ее в очередь
                nodes[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        ribs_connected << node + 1 << '\n';
    }

    int* nodes1 = new int[n];// вершины графа
    for (int i = 0; i < n; i++)
        nodes1[i] = 0;// исходно все вершины равны 0
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty())
    { // пока очередь не пуста
        int node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes1[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < n; j++)
        { // проверяем для нее все смежные вершины
            if (loop[node][j] == 1 && nodes1[j] == 0)
            { // если вершина смежная и не обнаружена
                Queue.push(j); // добавляем ее в очередь
                nodes1[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        ribs_loops << node + 1 << '\n';
    }

    int* nodes2 = new int[n];// вершины графа
    for (int i = 0; i < n; i++)
        nodes2[i] = 0;// исходно все вершины равны 0
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty())
    { // пока очередь не пуста
        int node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes2[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < n; j++)
        { // проверяем для нее все смежные вершины
            if (cycle[node][j] == 1 && nodes2[j] == 0)
            { // если вершина смежная и не обнаружена
                Queue.push(j); // добавляем ее в очередь
                nodes2[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        ribs_cycles << node + 1 << '\n';
    }

    int* nodes3 = new int[n];// вершины графа
    for (int i = 0; i < n; i++)
        nodes3[i] = 0;// исходно все вершины равны 0
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty())
    { // пока очередь не пуста
        int node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes3[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < n; j++)
        { // проверяем для нее все смежные вершины
            if (noorient[node][j] == 1 && nodes3[j] == 0)
            { // если вершина смежная и не обнаружена
                Queue.push(j); // добавляем ее в очередь
                nodes3[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        ribs_nooriented << node + 1 << '\n';
    }

    int* nodes4 = new int[n];// вершины графа
    for (int i = 0; i < n; i++)
        nodes4[i] = 0;// исходно все вершины равны 0
    Queue.push(0); // помещаем в очередь первую вершину
    while (!Queue.empty())
    { // пока очередь не пуста
        int node = Queue.front(); // извлекаем вершину
        Queue.pop();
        nodes4[node] = 2; // отмечаем ее как посещенную
        for (int j = 0; j < n; j++)
        { // проверяем для нее все смежные вершины
            if (suspend[node][j] == 1 && nodes4[j] == 0)
            { // если вершина смежная и не обнаружена
                Queue.push(j); // добавляем ее в очередь
                nodes4[j] = 1; // отмечаем вершину как обнаруженную
            }
        }
        ribs_suspended << node + 1 << '\n';
    }

    connected << n << '\n';
    for (int i = 0; i < n; i++)//граф - 1
    {
        for (int j = 0; j < m; j++)
        {
            connected << connect[i][j] << " ";
        }
        connected << '\n';
    }

    nooriented << n << '\n';
    for (int i = 0; i < n; i++)//граф - 1
    {
        for (int j = 0; j < m; j++)
        {
            nooriented << noorient[i][j] << " ";
        }
        nooriented << '\n';
    }

    cycles << n << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cycles << cycle[i][j] << " ";
        }
        cycles << '\n';
    }

    suspended << n << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            suspended << suspend[i][j] << " ";
        }
        suspended << '\n';
    }

    loops << n << '\n';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            loops << loop[i][j] << " ";
        }
        loops << '\n';
    }

    loops.close();
    suspended.close();
    cycles.close();
    nooriented.close();
    connected.close();
    ribs_connected.close();
    ribs_nooriented.close();
    ribs_cycles.close();
    ribs_loops.close();
    ribs_suspended.close();
}
