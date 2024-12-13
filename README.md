# PCOM | PROPUESTA DE PROBLEMA
<code>**LA RANITA Y LOS NENÚFARES**</code>
<hr>

**Autores**

- *Antonino Gabriel Sasu*
- *Javier Martín Fuentes*

En este archivo se recoge toda la documentación para nuestra propuesta de un problema para la asignatura de Programación Competitiva.

# Índice

1. [Estructura del directorio](#1-estructura-del-directorio)
2. [Soluciones](#2-soluciones)
   - [UFDS](#ufds)
   - [BFS](#bfs)
   - [DFS I](#dfs-i)
   - [DFS II](#dfs-ii)
   - [DFS Múltiple](#dfs-múltiple)
   - [MAX-FLOW](#max-flow)
3. [Generación de casos](#3-generación-de-casos)
   - [Casos de prueba](#20-casos-de-prueba)
   - [Casos exhaustivos](#21-casos-exhaustivos)
   - [Casos especiales](#22-casos-especiales)
   - [Casos aleatorios](#23-casos-aleatorios)
   - [Casos grandes](#24-casos-grandes)
4. [Clasificación de soluciones](#4-clasificación-de-soluciones)



## 1. Estructura del directorio
<hr>

## 2. Soluciones
<hr>

Para todas las soluciones se intepreta el estanque como un **grafo** en el que los nodos son los nenúfares conectados por aristas si la rana llega saltando de uno al otro. Asimismo, se añade un **nodo fantasma** que representa las cuatro orillas del estanque, conectado al resto de nodos por la misma regla.

### UFDS

Esta solución emplea la estructura de datos Union-Find (UF) modificada para ajustarse al problema. De este modo, se añade un vector *moscas* en el que se va acumulando la suma de moscas de cada componente conexa en el método <code>merge</code>.
Además, se implementan dos métodos nuevos:

- <code>setMoscas(int x, int m)</code> - Establece el número de moscas de un nodo x a m.
- <code>getMoscas(int x)</code> - Devuelve la suma de moscas en la componente conexa de un nodo dado x.
 
Así pues, se van añadiendo las conexiones entre los nenúfares en el UF **exceptuando las del nodo frágil**. Esto es importante ya que este nodo puede actuar como punto de articulación el cual separa conjuntos de nenúfares que se pueden quedar aislados en el medio del estanque. Por consiguiente, interesa quedarse con la suma de moscas que tiene la componente conexa que incluye el nodo fantasma de la orilla. 

Por último, se añaden las conexiones del nodo frágil al UF y se comprueba si su componente conexa coincide con la de la orilla. En tal caso, se suman las moscas del nodo frágil a las moscas obtenidas anteriormente (puesto que la rana puede saltar a este y regresar). De esta forma, evitamos que se sumen las moscas de las componentes conexas en las que la rana quedaría atrapada si accediese a ellas a través del nodo frágil.

### BFS

Esta es quizá la solución más trivial: se emplea una búsqueda primero en anchura que parte del nodo fantasma de la orilla. A continuación, se suman todas las moscas de los nodos que se van explorando. Si un nodo es el frágil, entonces no se exploran sus conexiones. La idea es que se llegará a esos nodos desde otro camino si realmente son accesibles.

### DFS I

Esta solución comparte la misma idea que la anterior (BFS): sumar todas las moscas de los caminos explorados, excepto los hijos del nodo frágil, para los cuales habrá que esperarse a llegar por otro camino para sumarlas. 


### DFS II

En esta solución se emplea la búsqueda primero en profundidad que parte del nodo fantasma que representa las orillas. Se definen tres estados para los nodos:

- <code>ACCESIBLE</code> / <code>NO ACCESIBLE</code>: si existe o no un camino **firme** desde ese nodo hasta la orilla.
- <code>NO VISITADO</code>

De este modo, se van marcando los nodos como ACCESIBLE según se van visitando desde la orilla y se suman las moscas correspondientes en función del estado del nodo anterior. Así pues, cuando se llega al nodo frágil, los nodos se empiezan a marcar como NO ACCESIBLE (incluido este). Las moscas del nenúfar frágil sí que se suman (la mosca puede entrar desde un camino firme y salir).

A partir de este momento, se van almacenando los nodos no visitados como NO ACCESIBLE en un *set* hasta llegar a un nodo ACCESIBLE. En ese momento, todos los nodos del conjunto se marcan como accesibles y se suman sus moscas.

Cada vez que se parte de un hijo del nenúfar frágil, se vacía el conjunto de nodos no accesibles, ya que esa componente conexa dejaría atrapada a la rana.

### DFS MÚLTIPLE

Se trata de una solución mucho menos inteligente: lanzar un DFS desde cada uno de los nodos y comprobar si se puede llegar a alguna de las orillas sin pasar por el nodo frágil. En tal caso, se suman las moscas de ese nodo al total.

### MAX-FLOW

La resolución del problema con max-flow se puede describir del siguiente modo: 

1. Generar un nuevo nodo fantasma que se corresponda con el nodo inicial del algoritmo. 
2. De este nodo fantasma sale una arista dirigida hacia cada uno de los nenúfares cuya capacidad es el número de moscas de cada uno. 
3. El resto de conexiones entre nenúfares son bidireccionales y tienen capacidad infinita, exceptuando el nodo frágil, cuyas aristas incidentes tienen capacidad 0 (no admite moscas, pero sí permite que salgan).
4. El nodo destino es el nodo fantasma que representa la orilla, tiene capacidad infinita de entrada pero nula de salida.


## 2. Generación de casos
<hr>

### 2.0 Casos de prueba

Estos casos **no son para probar la solución** sino para aclarar posibles dudas. Se definen los siguientes:

1. La rana no llega a ningún nenúfar. $sol=0$
2. Ejemplo de que la rana puede llegar los nenúfares desde distintas orillas. $sol=5$
3. Ejemplo con más casos: el nodo frágil está conectado a dos caminos accesibles desde la orilla y a un nenúfar que solo es accesible mediante él. Por lo tanto, se cuentan las moscas de todos los nenúfares excepto las de este último. $sol=4$

Estos tres primeros se corresponden con los casos de prueba del enunciado. Los siguientes son para clarificar alguna cuestión:

4. Las moscas del nenúfar frágil se cuentan si este es alcanzable desde alguna orilla (la rana aterriza a él y regresa a la orilla). $sol=5$ 
5. Las moscas del nenúfar frágil también se contabilizan si este se accede desde algún otro nenúfar que está conectado a la orilla. $sol=2$ 
6. El nenúfar frágil conecta un conjunto de nenúfares aislados con la orilla. $sol=0$ 
7. Mismo caso que el anterior pero ahora ese mismo conjunto también está conectado a la orilla por otro nenúfar. $sol=5$ 
8. La rana no tiene capacidad de salto (también cuenta como caso especial). $sol=0$ 

### 2.1 Casos exhaustivos

Hemos creado un solo generador para los casos exhaustivos ya que consideramos que no son tan necesarios en nuestro problema concreto.

En este, empezamos generando aleatoriamente los nenufares junto con sus coordenadas y moscas. Luego mantenemos estos valores para todos los casos, en los que iremos modificando solamente el valor de la distancia de salto: empezará desde 0.00 e irá subiendo hasta el límite (1500.00). Dentro del código se explica cómo vamos aumentando el valor del salto.

### 2.2 Casos especiales

Se han definido los siguientes casos especiales:

1. La rana no tiene capacidad de salto. $sol=0$
2. Nenúfares conectados a más de una orilla. $sol=2$
3. La capacidad de salto de la rana excede la diagonal del estanque (llega a todos los nenúfares desde cualquier orilla). $sol=9$
4. La rana sí llega al nenúfar interior por precisión decimal teniendo en cuenta $\epsilon = 10^{-6}$. $sol=2$
5. La rana no llega al nenúfar interior por precisión decimal. $sol=1$

### 2.3 Casos aleatorios

Tenemos un total de 5 generadores de casos aleatorios:

1. Crea 5.000 casos. Definimos los limites como los del enunciado (menos el máximo de nenufares que lo bajamos a 1.000) y generamos todos los valores de forma aleatoria (siguiendo una distribución uniforme).
2. Igual que el primero, pero disminuimos el valor máximo de salto para que sean menos frecuente los grupo grandes de nenúfares conexos.
3. Como el primero, pero bajamos el número de casos a 500 para así subir el número máximo de nenúfares al indicado en el enunciado (10.000) sin que el archivo de txt quede muy grande.
4. Crea 5.000 casos y a la vez mantenemos el máximo de nenúfares en 10.000. Generamos los valores igual que el resto.
*Este archivo tendrá alrededor de 25 millones de lineas*.
5. Generamos 1.000 casos con rangos más pequeños.

### 2.4 Casos grandes
Tenemos 5 generadores diferentes:

- **1 -** Creamos una fila vertical de 10.000 nenúfares conectados que llegan a conectarse por la orilla por ambos extremos. Aquí el nenúfar de abajo del todo es el frágil. Este caso nos sirve para distinguir el UFDS, DFS y BFS de un algoritmo que use un DFS por nenúfar o con otro que use MAX_FLOW.

- **1.1 -** Como el primero, pero el frágil es el de arriba de la fila. Esto se hace por si un algoritmo que se veria perjudicado por pasar primero por un nodo frágil consigue ir primero en el otro caso (el que empieza con el frágil por abajo) por el nodo no frágil. De este modo, nos aseguramos que al menos en uno de los dos pase primero por el frágil.

- **2 -** Tenemos un caso en el que la distancia de salto de la rana es mayor a la requerida para pasar de un extremo del lago a otro, luego todos los nenúfares (10.000) están conectados entre todos (orilla incluída). Con esto conseguimos excluir soluciones que no marquen de alguna manera los nenúfares por los que ya has pasado.

- **2.2 -** En este caso, tenemos 10.000 nenúfares en los que ninguno está conectado entre sí. Aquí son peores los algoritmos que empiezan desde algún nenúfar en vez de desde la orilla la exploración del grafo.

- **3 -** En este vamos a poner la distancia de salto al mínimo (0.01). Creamos una fila desde la orilla izquierda de 2.000 nenúfares conectados con distancia 0.01 entre ellos. Luego abajo de cada nenúfar de la fila colocamos de forma alternada nenufares a distancia 0.01 y 0.02 (estos últimos no están contados en la solución final). Para ampliar el número de nenúfares creamos otra fila igual un poco más abajo. El nenúfar frágil lo colocamos en la esquina inferior derecha apartado porque no nos interesa en este caso. Este caso es simplemente un caso con muchos nenúfares en el que hay que comprobar muchas veces el camino de ida y de vuelta, asi excluímos los que no hacen esto de forma eficiente.

## 3. Clasificación de soluciones

En la siguiente tabla se muestran los tiempos medios de ejecución de cada una de las soluciones con los casos grandes y los aleatorios. Cada una de las soluciones se ha ejecutado 5 veces:

| Solución    | CG 1    | CG 1.1  | CG 2     | CG 2.1   | CG 3     | CA1       | CA2       |
|-----------|---------|---------|----------|----------|----------|-----------|-----------|
| BFS       | 0.664s  | 0.659s  | 9.879s   | 0.690s   | 0.467s   | 132.619s  | 37.859s   |
| DFS I     | 0.699s  | 0.677s  | 10.892s  | 0.650s   | 0.500s   | 127.077s  | 38.998s   |
| DFS II    | 0.721s  | 0.688s  | 12.337s  | 0.631s   | 0.472s   | 136.822s  | 39.786s   |
| N DFS     | 14.653s | 7.127s  | 9.130s   | 0.846s   | 0.822s   | 236.087s  | 40.579s   |
| UFDS      | 0.765s  | 0.773s  | 3.184s   | 0.883s   | 0.567s   | 52.053s   | 24.329s   |
| MAX-FLOW  | 55.440s | 29.280s | >>>>     | 1.079s   | 14.517s  | >>>>      | >>>>      |


En vista de los valores observados, podemos determinar que claramente la solución más rápida y por lo tanto la que consideraremos como **SOLUCIÓN OFICIAL** es la que emplea la estructura de datos **UF**, la cual tiene un coste cuadrático con respecto a los datos de entrada. 

Por otro lado, podemos observar que las soluciones mediante **múltiples DFS** y **max-flow** tienen tiempos de ejecución más largos, ya que su coste temporal supera o iguala el coste cuadrático de la lectura de los datos. Por lo tanto, las clasificaremos como **soluciones 'malas' por TLE**. Se puede observar que para **generar TLE** se deben emplear los casos **GRANDE 1** o **GRANDE 2**.

Por último, depende de cuánto queramos ajustar el TLE podemos aceptar las soluciones **BFS, DFS I y DFS II** como válidas o no. En nuestro caso, hemos decidido marcarlas como **soluciones válidas alternativas**, ya que además también se ajustan al coste en tiempo cuadrático. Sin embargo, otra interpretación más exigente podría llegar a descartar estas soluciones ya que la oficial es bastante más eficiente, lo cual es un punto de vista razonable también.