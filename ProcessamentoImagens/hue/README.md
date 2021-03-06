# Espaço de Cores HSV

HSV é um sistema de cores formada por três componentes, a saber: *hue* (H), *saturation* (S) e *value* (V).

A wikipédia define cada um desses componentes como:

* **HUE**: Verifica o tipo de cor, abrangendo todas as cores do espectro, desde o vermelho até o violeta, mais o magenta.
* **Saturation**: Também chamado de "pureza". Quanto menor esse valor, mais com tom de cinza aparecerá a imagem. Quanto maior o valor, mais "pura" é a imagem.
* **Value**: Define o brilho da cor.

Podemos representar parte do espaço de cores do HSV por meio de um círculo. Onde o ângulo representa a cor (HUE) e a distância até o centro do círculo representa o nível de pureza (saturation).

Implementamos um programa em Python utilizando as bibliotecas NumPy e OpenCV para gerar tal círculo. Primeiramente importamos as bibliotecas e então definimos três variáveis globais: height, width e r (raio). Em seguida geramos uma mátriz (img) height * width * 3, onde a terceira dimensão é a RGB.

```python
import numpy as np
import cv2
import math

height = 1024
width = 1920
r = 500

img = np.ones((height, width, 3), np.float32)
```

A matriz gerada está toda preenchida com uns, o que torna a imagem branca. Para delimitarmos um círculo nessa imagem geramos vetores (xx e yy) com os índices dessa matríz. Então geramos uma matriz circle onde cada posição dessa matriz contêm o valor da distância da posição até o centro da imagem. Por último, substituímos por [0, 0, 0] (preto) todos os pontos que estão a uma distância maior que r (raio).

```python
xx, yy = np.ogrid[:height, :width]
circle = (xx - height/2) ** 2 + (yy - width/2) ** 2

img[circle > r**2] = [0,0,0]
```

Como resultado temos uma imagem toda branca com todos os pontos que não pertecem ao círculo pintados de preto. Ou seja, temos um círculo branco.

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue/hue3.jpg)

Já sabemos como delimitar um círculo, agora precisamos colorir a imagem. Como o HUE varia de 0 a 360, temos que calcular o ângulo de todos os pontos em relação ao eixo das ordenadas de uma base posicionada em (heigth/2, widith/2). Para isso utilizamos a função arco tangente e as posições x e y de cada ponto. Note que a função arctan2 retorna valores em radianos e portanto temos que transforma-los em graus.

```python
h = np.arctan2(xx.astype(np.float32)-height/2, yy.astype(np.float32)-width/2)
h = np.degrees(h)+90
s = np.ones((height, width), np.uint32)
v = np.ones((height, width), np.uint32)
```

Feito isso, temos os valores de H. Os valores de S e V vamos deixar todos como 1 (100%).

```python
img[:,:,0] = h
img[:,:,1] = s
img[:,:,2] = v

img = cv2.cvtColor(img, cv2.COLOR_HSV2BGR)
```

Substituímos então os valores da matriz img com os valores h na primeira coordenada, s na segunda e v na terceira. Enfim, usamos a função cvtColor para converter os valores em HSV para BGR de forma que possamos visualizar a imagem.

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue/hue.jpg)

Utilizando a ideia anteriormente vista, pintamos todos os pontos que não estão no circulo como preto. O resultado é um circulo com as cores do HUE.

```python
img[circle > r**2] = [0,0,0]
```

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue/hue2.jpg)

Para gerarmos os valores do S, temos que normalizar os valores da distância entre o centro da base até a extremidade do círculo para 0 até 1. 

```python
s = circle.astype(np.float32)/(r**2)
```
![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue/hue4.jpg)

Feito isso, temos cores mais puras nas extremidades.

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue/hue1.jpg)

```python
cv2.imshow("circulo", img)
cv2.imwrite('hue.jpg', (img*256).astype(np.uint16))
```

#Licença
Todas as imagens estão sobre [Attribution-ShareAlike 4.0 International](https://creativecommons.org/licenses/by-sa/4.0/deed.en_US) e o código sobre [licença MIT](https://raw.githubusercontent.com/vandersonmr/TrabalhosUEM/master/ProcessamentoImagens/LICENSE.txt).
