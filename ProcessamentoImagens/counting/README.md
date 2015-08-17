# Contagem de Objetos em Uma Imagem Binária

Toda imagem que possua apenas duas cores é uma imagem binária. Normalmente essas duas cores são representadas como branco (1) e preto (0).

Para identificarmos objetos não convexos de uma mesma cor em uma imagem binária, utilizamos o mesmo algoritmo utilizado na teoria dos grafos para detecção de componentes conexos, a busca em largura. 

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
Onde *num* conta a quantidade de componentes e *color* mantém a cor que será pintado cada componente. Já os dois *for* são responsáveis por iterarem por todos os vérticies e o *if* checa se o vértice já não foi visitado, em seguida é chamado uma função *paint* que simula o BFS e retorna o centroid do componente; nesse centroid é escrito o *num* do componente por meio da função *putText*.

#Licença
Todas as imagens estão sobre [Attribution-ShareAlike 4.0 International](https://creativecommons.org/licenses/by-sa/4.0/deed.en_US) e o código sobre [licença MIT](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/LICENSE.txt).
