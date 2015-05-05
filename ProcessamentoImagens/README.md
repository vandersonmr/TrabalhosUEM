# Espaço de Cores HSV

```python
import numpy as np
import cv2
import math

height = 1024
width = 1920
r = 500

img = np.ones((height, width, 3), np.float32)
```

```python
xx, yy = np.ogrid[:height, :width]
circle = (xx - height/2) ** 2 + (yy - width/2) ** 2

img[circle > r**2] = [0,0,0]
```

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue3.jpg)


```python
h = np.arctan2(xx.astype(np.float32)-height/2, yy.astype(np.float32)-width/2)
h = np.degrees(h)+90
s = np.ones((height, width), np.uint32)
v = np.ones((height, width), np.uint32)
```

```python
img[:,:,0] = h
img[:,:,1] = s
img[:,:,2] = v

img = cv2.cvtColor(img, cv2.COLOR_HSV2BGR)
```

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue.jpg)

```python
img[circle > r**2] = [0,0,0]
```

![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue2.jpg)

```python
s = circle.astype(np.float32)/(r**2)
```
![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue4.jpg)
![alt tag](https://github.com/vandersonmr/TrabalhosUEM/raw/master/ProcessamentoImagens/hue1.jpg)

```python
cv2.imshow("circulo", img)
cv2.imwrite('hue.jpg', (img*256).astype(np.uint16))
```
