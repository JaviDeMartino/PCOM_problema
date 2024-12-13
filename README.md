# PCOM | PROPUESTA DE PROBLEMA
<code>**LA RANITA Y LOS NENÚFARES**</code>
<hr>

<h3> Autores </h3>

- *Antonino Gabriel Sasu*
- *Javier Martín Fuentes*

En este archivo se recoge toda la documentación para nuestra propuesta de un problema para la asignatura de Programación Competitiva.

<h2> 1. Soluciones </h2>
<hr>

Para todas las soluciones se intepreta el estanque como un **grafo** en el que los nodos son los nenúfares conectados por aristas si la rana llega saltando de uno al otro. Asimismo, se añade un **nodo fantasma** que representa las cuatro orillas del estanque, conectado al resto de nodos por la misma regla.

**UFDS**

Esta solución emplea la estructura de datos Union-Find (UF) modificada para ajustarse al problema. De este modo, se añade un vector *moscas* en el que se va acumulando la suma de moscas de cada componente conexa en el método <code>merge</code>.
Además, se implementan dos métodos nuevos:

- <code>setMoscas(int x, int m)</code> - Establece el número de moscas de un nodo x a m.
- <code>getMoscas(int x)</code> - Devuelve la suma de moscas en la componente conexa de un nodo dado x.
 
Así pues, se van añadiendo las conexiones entre los nenúfares en el UF **exceptuando las del nodo frágil**. Esto es importante ya que este nodo puede actuar como punto de articulación el cual separa conjuntos de nenúfares que se pueden quedar aislados en el medio del estanque. Por consiguiente, interesa quedarse con la suma de moscas que tiene la componente conexa que incluye el nodo fantasma de la orilla. 

Por último, se añaden las conexiones del nodo frágil al UF y se comprueba si su componente conexa coincide con la de la orilla. En tal caso, se suman las moscas del nodo frágil a las moscas obtenidas anteriormente (puesto que la rana puede saltar a este y regresar). De esta forma, evitamos que se sumen las moscas de las componentes conexas en las que la rana quedaría atrapada si accediese a ellas a través del nodo frágil.

**DFS**

En esta solución se emplea la búsqueda primero en profundidad que parte del nodo fantasma que representa las orillas. Se definen tres estados para los nodos:

- <code>ACCESIBLE</code> / <code>NO ACCESIBLE</code>: si existe o no un camino **firme** desde ese nodo hasta la orilla.
- <code>NO VISITADO</code>

De este modo, los caminos desde la orilla se van marcando como accesibles.

**BFS**

Esta es quizá la solución más trivial: se emplea una búsqueda primero en anchura que parte del nodo fantasma de la orilla. A continuación, se suman todas las moscas de los nodos encontrados. Si un nodo es el frágil, entonces no se exploran sus conexiones. La idea es que se llegará a esos nodos desde otro camino.

**MAX-FLOW**

La resolución del problema con max-flow consiste en generar un nuevo nodo fantasma que se corresponda con el nodo inicial del algoritmo. De este nodo fantasma sale una arista dirigida hacia cada uno de los nenúfares cuya capacidad es el número de moscas de cada uno. Las capacidades del resto de conexiones bidireccionales entre nenúfares son infinitas y el nodo destino es el nodo fantasma que representa la orilla.

**DFS MÚLTIPLE**

<h3> 1.1 Solución oficial </h3>

<h2> 2. Generación de casos de prueba </h2>
<hr>

**Casos especiales**

Se han definido los siguientes casos especiales:

1. La rana no tiene capacidad de salto. 
$sol=0$
2. Nenúfares conectados a más de una orilla.
$sol=2$
3. La capacidad de salto de la rana excede la diagonal del estanque (llega a todos los nenúfares desde cualquier orilla).
$sol=9$
4. La rana no llega al nenúfar desde la orilla inferior por precisión decimal.
$sol=0$
5. La rana sí llega al nenúfar desde la orilla inferior por precisión decimal.
$sol=1$
6. La rana no llega al nenúfar desde la orilla izquierda por precisión decimal.
$sol=0$
7. La rana sí llega al nenúfar desde la orilla izquierda por precisión decimal.
$sol=1$
8. La rana no llega al nenúfar desde la orilla superior por precisión decimal.
$sol=0$
9. La rana sí llega al nenúfar desde la orilla superior por precisión decimal.
$sol=1$
10. La rana no llega al nenúfar desde la orilla derecha por precisión decimal.
$sol=0$
11. La rana sí llega al nenúfar desde la orilla derecha por precisión decimal.
$sol=1$
12. La rana no llega al nenúfar interior por precisión decimal.
$sol=1$
13. La rana sí llega al nenúfar interior por precisión decimal.
$sol=2$