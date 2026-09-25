# Relatório - Coelinhos do Brasil

> [!CAUTION]
> - Lembre-se que você <ins>**não pode utilizar ferramentas de IA para
>   escrever este relatório**</ins>

## Dados do aluno

- **Cartão UFRGS**: <mark>Joel Soares González</mark>
- **Nome**: <mark>00550073</mark>

## Passos que eu segui para resolver o problema especificado (em formato de *"prompt"*)

> [!IMPORTANT]
> - Coloque aqui todas as informações necessárias para que alguém
>   (pessoa ou ferramenta de IA) possa reproduzir os seus passos para
>   solucionar o problema
> - Escreva em formato imperativo, como se fosse um *prompt* com as
>   instruções a serem seguidas na solução do problema
> - Seja objetivo e conciso: quanto *menos palavras* você utilizar,
>   melhor
> - Seja técnico e use terminologia adequada: assuma que quem irá ler
>   os seus passos possui conhecimento de Ciência da Computação e
>   Computação Gráfica
> - Caso você queira incluir informações "longas" (como algum *prompt*
>   grande usado com alguma ferramenta de IA), crie arquivos à parte e
>   adicione links no texto (por exemplo, crie o arquivo `PROMPTS.md`
>   e adicione um link markdown `[os prompts detalhados estão
>   aqui](PROMPTS.md)`)
> - Novamente, lembre-se que você *não pode utilizar ferramentas
>   de IA para escrever este relatório*

Crie uma estrutura Coelho3D que armazene:  
- vetor com sua posição global,  
- ângulo local de rotação em torno do eixo Y,  
- vetor direção de deslocamento,  
- distancia ao longo de um trajeto.  
Crie vetores Coelho3D <mark>[com seus tamanhos](VALORES.md)</mark>  separando os em 3 grupos por cor;  
Gere 3 classes de trajetória que definirão o deslocamento de cada grupo;  
Adicione os arquivos .cpp das classes à lista de arquivos de compilação no arquivo CMakeList.txt;  
Inclua os headers das classes na main.cpp;  
Inicialize as trajetórias <mark>[com seus valores](VALORES.md)</mark>;  
Inclua a biblioteca chrono para uso de DeltaTime;  
Implemente as variaveis de DeltaTime e sua atualização no laço principal;  
Atualize as posições de cada grupo percorrendo seus vetores;  
> [!Important] Use 'c.distancia += speed * deltaTime * retangulo.length();' para velocidade uniforme;  
Os prompts para geração das classes de trajetória são <mark>[descritos aqui](PROMPTS.md)</mark>  
Valores testados manualmente por comparação <mark>[descritos aqui](VALORES.md)</mark>  

## Principais dificuldades encontradas durante o desenvolvimento (formato livre)

Tive dificuldade de manejar o tempo para o LAB2 e testar manualmente os tamanhos, velocidades para se adequar à referência.  
Bem como de digerir o código base até entender como e onde modificálo.  
As novas classes não compilavam e estava acostumado a apertar 'F5' e o programa rodar, algo que não acontece por causa da separação em pastas.

## Você acha que conseguiu resolver o problema de forma adequada?

No geral sim, mas me atrapalhei com o tempo e não implementei o pulo.

## Se você quiser compartilhar mais alguma coisa, coloque aqui:

Achei a escolha do trabalho curiosa.

## Se você possui alguma sugestão para o professor sobre esta atividade, coloque aqui:

Continue pedindo transparência no uso de IA.
