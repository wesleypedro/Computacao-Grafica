# Computação Gráfica - C++ e biblioteca OpenGL

> Segundo trabalho da disciplina de Computação Gráfica pela Universidade Federal do Ceará - Campus Quixadá.

`O programa não se encontra totalmente terminado`
`Sugerido o uso do QT Creator`


## Requisitos do Trabalho

- Implementar uma curva cúbica Interpoladora paramétrica 3D
- Implementar uma curva cúbica Hermite paramétrica 3D
- Implementar uma curva cúbica Bezier paramétrica 3D

- Alternar entre as matrizes Mi, Mh, Mb e explicar a mudança do significado dos pontos de controle para cada caso

- Implementar uma spline Catmull-Rom paramétrica 3D (cúbica por partes)
- Implementar uma spline B-spline paramétrica 3D (cúbica por partes)
___________________
- Uma curva paramétrica 3D define o movimento de um sistema de coordenadas local, e não apenas de um ponto 3D
	- considerar as mudanças de orientação (e não só de translação) definidas pela curva
- Desenhar o caminho de uma montanha-russa usando a implementação de splines
	- Desenhar a montanha-russa ("trilhos" do caminho completo, com orientação)
		- Permitir o usuário modelar interativamente (em tempo real) a montanha-russa, através do ajuste (translação) dos pontos de controle
		- Permitir incluir/excluir pontos de controle
		- Permitir alterar a discretizacao da curva interativamente (deixar usuario mexer em tempo real)
		- Alternar entre as matrizes Catmull-Rom e B-Splines (analisar interpolação/aproximação vs. continuidades C1/C2)
	- Desenhar um objeto percorrendo o caminho definido pela montanha-russa ("carrinho", com orientação)
		- Definir teclas para avançar e para voltar no caminho definido
	- Mostrar a visão de uma câmera percorrendo o caminho definido pela montanha-russa (estilo uma camera gopro acoplada em um carro)
-------
- Implementar seleção dos pontos de controle através de picking (mouse)
	- Permitir transladar o ponto de controle selecionado com o teclado e também com o mouse
- Usar diferentes viewports
	- sugestão 1: 1 viewport mostrando a visao do carrinho
	- sugestão 2: 4 viewports estilo 3ds/Blender
		- Uma modificada pelo mouse, como antes/uma de frente/uma de lado/uma de cima
