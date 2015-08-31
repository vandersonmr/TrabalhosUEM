# Contagem de Objetos em Uma Imagem Binária

Toda imagem que possua apenas duas cores é uma imagem binária. Normalmente essas duas cores são representadas como branco (1) e preto (0).

Para identificarmos objetos não convexos de uma mesma cor em uma imagem binária, utilizamos o mesmo algoritmo utilizado na teoria dos grafos para detecção de componentes conexos: a busca em largura. 

![alt tag](https://upload.wikimedia.org/wikipedia/commons/9/99/Breadth-first_search_Algorithm.gif)

O pseudo código para detecção de componentes conexos é o seguinte:

```
para todos os vértices V
  se V ainda não foi processado
    componente = BFS(V)
```

Agora, vamos implementar esse mesmo algoritmo em Python com o OpenCV. Primeiramente, temos que abrir a imagem em escala de cinza:

```python
img = cv2.imread(sys.argv[1], cv2.CV_LOAD_IMAGE_GRAYSCALE)
```

Em seguida garantimos que a imagem é binária:

```python
img[img > 127] = 255
img[img < 127] = 0
```

Agora vamos implementar o pseudo código a cima citado: 

```python
def count(img, toPaint = 255):
    num = 0
    color = 100
    for x in range(0, img.shape[0]):
        for y in range(0, img.shape[1]):
            if img[x, y] == toPaint:
                centroid = paint(img, (x, y), color, toPaint)
                cv2.putText(img,str(num),centroid,font,0.7,(250,250,250),2)
                color = (color + 1) % 240 + 1
                num += 1
    return num
```
Onde *num* conta a quantidade de componentes e *color* mantém a cor que será pintado cada componente. Já os dois *for* são responsáveis por iterarem por todos os vértices e o *if* checa se o vértice já não foi visitado, em seguida é chamado uma função *paint* que simula o BFS e retorna o centroid do componente; nesse centroid é escrito o *num* do componente por meio da função *putText*.

O BFS, ou *paint*, é implementado da seguinte forma:

```python
def isValid(img, x, y):
    return x >= 0 and x < img.shape[0] and y >= 0 and y < img.shape[1]

def paint(img, (x, y), color, toPaint = 255):
    centroid = (x, y)
    size = 0
    queue = deque([(x, y)])
    visited = img > 255
    while len(queue) != 0:
        a = queue.popleft()
        img[a[0], a[1]] = color
        centroid = (centroid[0] + a[0], centroid[1] + a[1])
        size += 1
        for nx, ny in [(a[0]+i, a[1]+j) for i in range(-1, 2) for j in range(-1, 2)]:
            if isValid(img, nx, ny) and img[nx, ny] == toPaint and not visited[nx][ny]:
                visited[nx][ny] = True
                queue.append((nx, ny))
    return centroid[1]/size, centroid[0]/size
```

Ou seja, uma implementação iterativa do algoritmo BFS com uma fila. 

Assim, executamos o programa para algumas imagens de teste.

![alt tag](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/counting/img1.png)

O resultado:

![alt tag](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/counting/countImg1.png)

Note que como cada componente é pintado com um valor diferente, o histograma da imagem é exatamente a área de cada componente. Como podemos ver no histograma da primeira imagem:

![alt tag](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/counting/hist.png)

Por fim, algumas outras imagens que foram usadas como teste:
* ![alt tag](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/counting/img2.png) ![alt tag](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/counting/countImg2.png)
* ![alt tag](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/counting/img3.png) ![alt tag](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/counting/countImg3.png)
* ![alt tag](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/counting/img4.jpg) ![alt tag](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/counting/countImg4.png)

#Licença
Todas as imagens estão sobre [Attribution-ShareAlike 4.0 International](https://creativecommons.org/licenses/by-sa/4.0/deed.en_US) e o código sobre [licença MIT](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/LICENSE.txt).
