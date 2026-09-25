## Prompt 1:
Implemente em C++ uma classe `RoundedRectangle` para representar uma trajetória fechada de retângulo com cantos arredondados no plano XZ, mantendo Y = 0.

Requisitos:

* Construtor: `RoundedRectangle(float width, float height, float radius)`.
* Representar a trajetória como 8 segmentos: 4 segmentos lineares e 4 arcos de circunferência.
* Garantir continuidade C1 entre segmentos, isto é, a direção tangente deve ser contínua nas transições linha/arco.
* Parametrizar a trajetória por distância percorrida, permitindo velocidade física constante.
* Implementar:

  * `glm::vec3 position(float distance) const`
  * `glm::vec3 direction(float distance) const`
  * `float length() const`
  * `float getWidth() const`
  * `float getHeight() const`
  * `float getRadius() const`
* `position()` deve retornar a posição correspondente à distância ao longo da trajetória.
* `direction()` deve retornar o vetor tangente normalizado na direção do percurso.
* `distance` deve ser tratado ciclicamente usando o comprimento total da trajetória.
* Usar `std::fmod` para o tratamento periódico.
* Arcos devem ser calculados analiticamente a partir de centro, raio e ângulo.
* Organizar a implementação em `RoundedRectangle.h` e `RoundedRectangle.cpp`.
* Não incluir renderização, OpenGL ou lógica de animação.
* Manter a API independente da coordenada Y.

## Prompt 2:
Implemente em C++ uma classe `Diamond` para representar uma trajetória fechada em formato de losango no plano XZ, com cantos arredondados e Y = 0.

Requisitos:

* Construtor: `Diamond(float width, float height, float radius)`.
* Vértices do losango:

  * topo: `(0, 0, -height/2)`
  * direita: `(width/2, 0, 0)`
  * baixo: `(0, 0, height/2)`
  * esquerda: `(-width/2, 0, 0)`.
* Arredondar os quatro vértices com arcos de circunferência tangentes aos segmentos adjacentes.
* Representar a trajetória como 8 segmentos alternados entre linhas e arcos.
* Garantir continuidade C1 nas transições entre linhas e arcos.
* Parametrizar a trajetória por distância percorrida, permitindo velocidade física constante.
* Implementar:

  * `glm::vec3 position(float distance) const`
  * `glm::vec3 direction(float distance) const`
  * `float length() const`
  * `float getWidth() const`
  * `float getHeight() const`
  * `float getRadius() const`
* Calcular geometricamente os pontos de tangência e centros dos arcos a partir dos ângulos internos dos vértices.
* `position()` deve calcular analiticamente a posição em segmentos lineares e arcos.
* `direction()` deve retornar a tangente normalizada na direção do percurso.
* O percurso deve seguir a ordem topo → direita → baixo → esquerda → topo.
* Os arcos devem contornar externamente os vértices, preservando a forma convexa do losango.
* Usar `std::fmod` para tornar `distance` periódico.
* Organizar a implementação em `Diamond.h` e `Diamond.cpp`.
* Não incluir renderização, OpenGL ou lógica de animação.
* Manter a API independente da coordenada Y.

## Prompt 3
Implemente em C++ uma classe `Circle` para representar uma trajetória circular fechada no plano XZ, com Y = 0.

Requisitos:

* Construtor: `Circle(float radius)`.
* Centro da circunferência em `(0, 0, 0)`.
* Implementar:

  * `glm::vec3 position(float distance) const`
  * `glm::vec3 direction(float distance) const`
  * `float length() const`
  * `float getRadius() const`
* O comprimento total deve ser `2πr`.
* Parametrizar a trajetória por distância percorrida, convertendo-a em ângulo por `theta = distance / radius`.
* `position()` deve retornar:
  `(r cos(theta), 0, r sin(theta))`.
* `direction()` deve retornar o vetor tangente normalizado:
  `(-sin(theta), 0, cos(theta))`.
* Usar `std::fmod` para permitir movimento cíclico.
* O percurso deve seguir +X → +Z → -X → -Z → +X.
* Organizar a implementação em `Circle.h` e `Circle.cpp`.
* Não incluir renderização, OpenGL ou lógica de animação.
* Manter a interface compatível com outras classes de trajetória baseadas em distância.
