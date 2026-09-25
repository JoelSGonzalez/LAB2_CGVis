# VALORES

## defines
#define COELHOS_VERDES 24  
#define COELHOS_AMARELOS 15  
#define COELHOS_AZUIS 8  

## trajetórias
#### Retangular
float a = 2.5f;  
RoundedRectangle retangulo(a * 20.0f/14.0f, a, 0.15f);  
#### Losangular
float b = 2.0f;  
Diamond diamante(b * 20.0f/14.0f, b, 0.1f);  
#### Circular
float c = 1.2f;  
Circle circulo(c/2.0f);  