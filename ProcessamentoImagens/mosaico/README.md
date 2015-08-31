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

Vamos analisar a complexidade de tempo do algoritmo. Para facilitar, vamos considerar o tamanho de todas as imagens como quadradas. Seja N o tamanho médio das imagens no banco de imagens e M o tamanho da imagem original, e ainda, seja S a quantidade de imagens no banco. Então a linha 1 tem complexidade O(SN²). Já a segunda linha é um loop que executa O(M²) vezes as linhas 3, de complexidade O(SN²), 4, de complexidade O(N²) e 5 de complexidade O(N²). Dessa forma a complexidade total do algoritmo de forma simplificada é O(SN²M²).

Para amortizarmos a execução, vamos utilizar de programação dinâmica para poder calcular em O(1) a média de qualquer subimagem retangular da imagem original. 

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

Tendo a imagem acumulada, podemos calular a média em O(1) de qualquer subimagem retangular da seguinte forma:

```python
def getMeanFrom(xb, yb, xa, ya):
    n = ((xb - xa)+1) * ((yb - ya)+1)
    z = getW(xb, yb) - getW(xb, ya-1) - getW(xa-1, yb) + getW(xa-1, ya-1)
    return z/n
```

#Licença
Todas as imagens estão sobre [Attribution-ShareAlike 4.0 International](https://creativecommons.org/licenses/by-sa/4.0/deed.en_US) e o código sobre [licença MIT](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/LICENSE.txt).
