# Mosaico de Imagens

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/mosaicEb.png)

Um mosaico é uma junção de pedras ou outros objetos em um plano, geralmente parede ou chão, com objetivo de formar um desenho. No caso de um mosaico de imagens, como na figura a cima, é uma junção de imagens menores para formação de uma outra imagem.

O pseudo-código proposto para geração de um mosaico de imagens é o seguinte:

```
1 Calular média de cor de todas as imagens do banco de imagens
2 Para todo pixel P da imagem original
3   Encontrar, no banco, uma imagem A com a média mais próxima da média da subimagem retangular (P, P + tamanho de A)
4   Pintar A na imagem originial na posição P
5   Marcar todos pixels pintados como visitados
```

Para amortizarmos o tempo de execução, vamos utilizar programação dinâmica para poder calcular em O(1) a média de qualquer subimagem retangular da imagem original. 

Para isso, primeiramente calculamos uma matriz W com peso acumulado, onde cada pixel é a soma do valor de todos os pixels do retangulo ((0,0), (x, y)). Como no código a seguir:

```python
W = np.zeros((img.shape[0], img.shape[1], img.shape[2]), dtype=np.uint64)
 
def getW(self, i, j):
    if i >= W.shape[0]: i = W.shape[0]-1
    if j >= W.shape[1]: j = W.shape[1]-1
    return 0 if i < 0 or j < 0 else W[i][j]
    
for i in range(0, img.shape[0]):
    for j in range(0, img.shape[1]):
        W[i][j] += getW(i-1, j) + getW(i, j-1) + img[i][j] - getW(i-1, j-1)
```

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/pd1.png)

Tendo a imagem acumulada, podemos calular a média em O(1) de qualquer subimagem retangular da seguinte forma:

```python
def getMeanFrom(xb, yb, xa, ya):
    n = ((xb - xa)+1) * ((yb - ya)+1)
    z = getW(xb, yb) - getW(xb, ya-1) - getW(xa-1, yb) + getW(xa-1, ya-1)
    return z/n
```

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/pd2.png)

A complexidade do algoritmo é de O(S(M²/N²)*M²), logo, para N² próximos de 1 o algoritmo é de M a quarta e para N² próximos de M² a complexidade é de M a segunda. 

O pseudo-código implementado em Python:

```python
def paint(img, x, y, newImg, visited):
    for i in range(0, img.shape[0]):
        for j in range(0, img.shape[1]):
            if i + x < newImg.shape[0] and j + y < newImg.shape[1]:
                newImg[i+x][j+y] = img[i][j]
                visited[i+x][j+y] = True

def doMosaic(img, db, width, e = False):
    cimg    = CumulatedImg(img)
    visited = np.zeros((img.shape[0], img.shape[1]), dtype=bool)
    newImg  = np.zeros((img.shape[0], img.shape[1], img.shape[2]), dtype=np.uint8)
    for i in range(0, img.shape[0]):
        for j in range(0, img.shape[1]):
            if not visited[i][j]:
                paint(db.getClosestImage(cimg, i, j, width, e), i, j, newImg, visited)
    return newImg
```

# Tamanho das imagens

Para testarmos, utilizamos um banco de dados de 130 imagens para gerar a imagem da Lena, a seguir:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena.com)

Mosaico gerado com as imagens em seu tamanho original:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/3-2/mosaicE.png)

Mosaico gerado com as imagens em 1/4 do tamanho:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/3-4/mosaicE.png)

Mosaico gerado com as imagens em 1/16 do tamanho:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/3-8/mosaicE.png)

Mosaico gerado com as imagens em 1/64 do tamanho:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/3-16/mosaicE.png)

Mosaico gerado com as imagens em 1/256 do tamanho:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/3-32/mosaicE.png)

Mosaico gerado com as imagens em 1/1024 do tamanho:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/3-64/mosaicE.png)

# Métricas

Em seguida, testamos outra métrica para cálulo da distância entre duas cores, que leva em consideração um peso maior para o vermelho, baseado na forma com que percebemos as cores. Contudo, os resultados foram muito semelhantes aos obitidos com distância euclidiana. Veja o maosaico gerado com as imagens em 1/1024 do tamanho e a métrica citada:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/3-64/mosaic1.png)

# Conjunto de Imagens

Para testarmos o impacto do conjunto de imagens nos mosaicos gerados, adicionamos 190 novas imagens ao conjunto anterior. Os mosaicos resultantes:

Mosaico gerado com as imagens em 1/64 do tamanho:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/6-16/mosaic1.png)

Mosaico gerado com as imagens em 1/256 do tamanho:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/6-32/mosaic1.png)

Mosaico gerado com as imagens em 1/1024 do tamanho:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/6-64/mosaic1.png)

Note que os mosaicos se aproximaram mais dos detalhes da original e também na coloração. 

# Blend

Em seguida, para melhorarmos mais ainda o resultado, aplicamos um blend com a imagem original (20% da cor de cada pixel vem da imagem original e 80% do mosaico). Veja o código e o resultado:

```python
def blend(img1, img2):
    return (img1*0.2 + img2*0.8)/255
```
Mosaico gerado com as imagens com tamanho original:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/6-2/mosaic1b.png)

Mosaico gerado com as imagens em 1/1024 do tamanho:

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/mosaico/lena/6-64/mosaic1b.png)

# Tempo de Execução

Por último, testamos o tempo de execução

#Licença
Todas as imagens estão sobre [Attribution-ShareAlike 4.0 International](https://creativecommons.org/licenses/by-sa/4.0/deed.en_US) e o código sobre [licença MIT](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/LICENSE.txt).
