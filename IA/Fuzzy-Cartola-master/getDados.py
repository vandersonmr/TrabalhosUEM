#!/usr/bin/python3.4

import requests
import pickle


l = []
for i in range(1,50):
    a = requests.get("http://cartolafc.globo.com/mercado/filtrar.json?page="+str(i)+"&order_by=preco")
    try:
        t = a.json()
        l.append(t)
        print(i)
    except Exception:
        pass

f = open("dadosCartola","wb+")
pickle.dump(l, f)
