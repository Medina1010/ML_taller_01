# 1. Configuración matemática común
binwidth = 0.1
bin(x, width) = width * floor(x / width)

# 2. Configuración estética común
set style fill solid 0.8 border -1
set boxwidth binwidth
set grid y

# 3. Bucle para procesar cada archivo por separado
do for [name in "logistic-list camp-list"] {
    
    # Define el formato de imagen y el nombre del archivo de salida dinámicamente
    set terminal pngcairo size 800,600 enhanced font "Arial,12"
    set output name . '.png'   # Generará 'datos_a.png' y 'datos_b.png'
    
    # Título dinámico para cada gráfico
    set title "Histograma de " . name
    
    # Comando de graficado individual
    plot name . '.csv' using (bin($1, binwidth)):(1.0) smooth frequency with boxes notitle
    
    # Cierra correctamente el archivo actual antes de pasar al siguiente
    set output
}

