## Prompt 1:
Implemente em C++ uma classe RoundedRectangle para representar uma trajetória fechada de retângulo com cantos arredondados no plano XZ, mantendo Y = 0.

Requisitos:

- Criar obrigatoriamente dois arquivos: RoundedRectangle.h e RoundedRectangle.cpp.
- Construtor: RoundedRectangle(float width, float height, float radius).
- Representar a trajetória como uma lista de 8 segmentos, alternando 4 segmentos lineares e 4 arcos de circunferência que suavizam os quatro cantos do retângulo.
- Os arcos devem ser tangentes aos segmentos lineares adjacentes, garantindo continuidade C1 da trajetória.
- Parametrizar toda a trajetória por distância percorrida, permitindo velocidade física constante.
- Implementar glm::vec3 position(float distance) const, glm::vec3 direction(float distance) const, float length() const, float getWidth() const, float getHeight() const e float getRadius() const.
- position() deve retornar a posição correspondente à distância percorrida na trajetória.
- direction() deve retornar o vetor tangente normalizado correspondente à direção do movimento.
- Tratar a trajetória como cíclica, fazendo distance retornar ao início após length().
- Usar std::fmod para o tratamento periódico da distância.
- Calcular analiticamente a posição e a direção nos segmentos lineares e nos arcos.
- Organizar internamente os segmentos com informações suficientes para determinar seu tipo, comprimento e geometria.
- Não incluir renderização, OpenGL ou lógica de animação.
- A interface deve ser independente da coordenada Y.

## Prompt 2:
Implemente em C++ uma classe Diamond para representar uma trajetória fechada em formato de losango no plano XZ, mantendo Y = 0.

Requisitos:

- Criar obrigatoriamente dois arquivos: Diamond.h e Diamond.cpp.
- Utilizar os vértices: topo (0, 0, -height/2), direita (width/2, 0, 0), baixo (0, 0, height/2) e esquerda (-width/2, 0, 0).
- Representar a trajetória como uma lista de 8 segmentos, alternando 4 segmentos lineares e 4 arcos de circunferência que suavizam os quatro vértices do losango.
- Os arcos devem ser tangentes aos segmentos lineares adjacentes, garantindo continuidade C1 da trajetória.
- Os arcos devem suavizar as pontas externas do losango, preservando seu formato convexo.
- O percurso deve seguir a ordem topo → direita → baixo → esquerda → topo.
- Parametrizar toda a trajetória por distância percorrida, permitindo velocidade física constante.
- Implementar glm::vec3 position(float distance) const, glm::vec3 direction(float distance) const, float length() const, float getWidth() const, float getHeight() const e float getRadius() const.
- Calcular geometricamente os pontos de tangência e os centros dos arcos a partir dos ângulos internos dos vértices.
- position() deve retornar a posição correspondente à distância percorrida na trajetória.
- direction() deve retornar o vetor tangente normalizado correspondente à direção do movimento.
- Tratar a trajetória como cíclica, fazendo distance retornar ao início após length().
- Usar std::fmod para o tratamento periódico da distância.
- Calcular analiticamente a posição e a direção nos segmentos lineares e nos arcos.
- Organizar internamente os segmentos com informações suficientes para determinar seu tipo, comprimento e geometria.
- Não incluir renderização, OpenGL ou lógica de animação.
- A interface deve ser independente da coordenada Y.

## Prompt 3
Implemente em C++ uma classe Circle para representar uma trajetória circular fechada no plano XZ, mantendo Y = 0.

Requisitos:

- Criar obrigatoriamente dois arquivos: Circle.h e Circle.cpp.
- Construtor: Circle(float radius).
- O centro da circunferência deve estar em (0, 0, 0).
- O comprimento total da trajetória deve ser 2πr.
- Parametrizar a trajetória por distância percorrida, permitindo velocidade física constante.
- Implementar glm::vec3 position(float distance) const, glm::vec3 direction(float distance) const, float length() const e float getRadius() const.
- position() deve retornar a posição correspondente à distância percorrida na circunferência.
- Converter a distância percorrida em ângulo utilizando theta = distance / radius.
- Utilizar a parametrização position = (r cos(theta), 0, r sin(theta)).
- direction() deve retornar o vetor tangente normalizado correspondente à direção do movimento, utilizando (-sin(theta), 0, cos(theta)).
- Tratar a trajetória como cíclica, fazendo distance retornar ao início após length().
- Usar std::fmod para o tratamento periódico da distância.
- O percurso deve seguir a ordem +X → +Z → -X → -Z → +X.
- Não incluir renderização, OpenGL ou lógica de animação.
- A interface deve ser independente da coordenada Y.
