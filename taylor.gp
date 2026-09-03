set terminal pngcairo size 800,600 enhanced font "Arial,12"
set output 'exp.png'  
    
set title "Aproximaciones de exponencial"
plot [-2:2] exp(x) with lines title "exp(x)", \
     for [i=0:10] sprintf("exp%d.dat", i) using 1:2 with lines title sprintf("exp%d", i)
set output 'cos.png'

set yrange [-5:5]
set title "Aproximaciones de coseno"
plot [-6:6] cos(x) with lines title "cos(x)", \
     for [i=0:10] sprintf("cos%d.dat", i) using 1:2 with lines title sprintf("cos%d", i)
set output
