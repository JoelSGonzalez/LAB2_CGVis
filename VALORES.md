# VALORES

## defines
#define COELHOS_VERDES      24  
#define COELHOS_AMARELOS    15  
#define COELHOS_AZUIS       8  

## variaveis
float proporcao = 20.0f / 14.0f;
float speed = 0.1f;  

## trajetórias
#### Retangular
float a = 2.5f;  
RoundedRectangle retangulo(a * proporcao, a, 0.15f);  
#### Losangular
float b = 2.0f;  
Diamond diamante(b * proporcao, b, 0.1f);  
#### Circular
float c = 1.2f;  
Circle circulo(c/2.0f);  

## matrizes
glm::mat4 chao = Matrix_Translate(0.0f,-0.80f,0.0f);        // posiciona os coelhos rente ao plano (coordenadas globais)
glm::mat4 chapeu = Matrix_Translate(-0.14f,0.12f,0.042f);   // posição do chapéu relativa ao centro do coelho (coordenadas locais)  
glm::mat4 escala = Matrix_Scale(0.2f, 0.2f, 0.2f);          // reduz o tamanho dos coelhos e chapeus  
glm::mat4 achatamento = Matrix_Scale(0.45f,0.13f,.45f);     // deforma a esfera para o formato de chaoeu  

