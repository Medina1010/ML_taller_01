# Taller_01 - Maching Learning
- Christian Marroquín, Julian Medina
# Ejercicios
## Numeros pseudoaleatorios
- Realizar generadores de numeros pseudoaleatorios (tend map, logistic map) y calcular estadisticas (media, varianza, coeficiente de asimetria, histograma).
### Resultados:
- estadisticas para 100 valores aleatorios
``` md
# logistic map
mean=0.526487
var=0.118214
asymetry=-0.118942

# tent map
mean=0.514378
var=0.079439
asymetry=-0.041304
```
- histogramas

Se realizó el histograma usando el siguiente [script](rand.gp) de *gnuplot*.

| ![histograma mapeo logistico](logistic-list.png) | ![histograma mapeo de tienda de campaña](camp-list.png) |
| - | - |
- [codigo](rand_gen.c).
## Taylor
- Realizar aproximaciones de Taylor para la función exponencial y una función de nuestra elección (*coseno*).
### resultados
- evaluacion de funciones
```
# taylor aprox n = 10
e = 2.718282
cos(1) = 0.540303
```
- graficas

Se calcularon multiples aproximaciones de taylor de diferentes grados y se muestran en la misma grafica para la función exponencial y coseno usando el siguiente [script](taylor.gp) de *gnuplot*.

| funcion | grafico |
| - | - |
| $e^x$ | ![grafico exponencial](exp.png) |
| $\cos (x)$ | ![grafico coseno](cos.png) |
- [codigo](taylor.c)

Se realizó una función *taylor*, que recibe los coeficientes de la n-esima derivada en el punto al cual se realiza la expasión.
## Newton-Rhapson
- Implementar el metodo de Newton-Rhapson para aproximar raices y usarlo para las siguientes funciones:
    - $f\ (x)=x^2-612,\ f\ \prime(x)=2x$
    - $f\ (x)=\cos(x)-x^3,\ f\ \prime(x)=-\sin(x)-3x^2$
### resultados
``` md
# raiz de x^2 - 612
raiz: sqrt(612) = 24.738634
delta: -0.000018
epsilon: 0.010000

# raiz de cos(x) - x^3
raiz: 0.867264
delta: 0.005394
epsilon: 0.010000
```
- [codigo](newton_rhapson.c).
