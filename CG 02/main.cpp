#include <iostream>
#include <string>

using namespace std;

#include <gui.h>
#include <vector>
#include <curva.h>
#include <CameraJogo.h>

//-------------------picking------------------
vector<Vetor3D> pontosControle;

int pontoSelecionado = 0;
bool automatico = true;
bool primeira = false;
bool origem = false;
double delta;



curva *c = new curva();
CameraJogo *jogo = new CameraJogo();
Camera *cam = new CameraDistante();



void desenhaPontosDeControle()
{
    //desenhando pontos de controle
    for (int i=0; i < pontosControle.size(); i++) {
        //definindo cor da selecao
        if (i == pontoSelecionado) {
            GUI::setColor(1,1,1,1,true);

        } else {
            GUI::setColor(0,0,1,1,true);
        }
        //desenhando (definindo nomes para o picking)
        Vetor3D p = pontosControle[i];
        glPushName(i+1); //não se deve definir name = 0!
            GUI::drawSphere(p.x,p.y,p.z,0.2);
        glPopName();
    }
}

void inserePontoControle(){
    pontosControle.push_back(Vetor3D(1,1,1));
}

void removePontoControle(){
    if(pontosControle.size() > 4){
        pontosControle.pop_back();
    }

}

//picking
int picking( GLint cursorX, GLint cursorY, int w, int h ) {
    int BUFSIZE = 512;
    GLuint selectBuf[512];

    GUI::pickingInit(cursorX,cursorY,w,h,selectBuf,BUFSIZE);

    //de acordo com a implementacao original da funcao display
    //lembrar de nao inicializar a matriz de projecao, para nao ignorar a gluPickMatrix
    GUI::displayInit();
    //só precisa desenhar o que for selecionavel
    desenhaPontosDeControle();
    //fim-de acordo com a implementacao original da funcao display

    //retornando o name do objeto (ponto de controle) mais proximo da camera (z minimo! *[matrizes de normalizacao da projecao])
    return GUI::pickingClosestName(selectBuf,BUFSIZE);
}
//-------------------picking------------------

//-------------------viewPorts------------------
bool viewports = false;
bool scissored = false;

void cenario();

//visao de duas cameras (duas viewports), viewport auxiliar sobrepondo a principal
void viewPorts() {
    float width = glutGUI::width;
    float height = glutGUI::height;

    //viewport 01 - tela inteira - Modificada pelo mouse
    glViewport(0, 0, width, height);
    glLoadIdentity();
    gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
    cenario();


    //viewport 02 - visão de frente
    if (!scissored) {
        //misturando com a principal
        glViewport(0, height - (height / 4.0), width/4.0, height/4.0);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(0, height - (height / 4.0), width/4.0, height/4.0);
    }
    glViewport(0, height - (height / 4.0), width/4.0, height/4.0);
    glLoadIdentity();
    gluLookAt(0,0,10, 0,0,0, 0,1,0);
    cenario();




    //viewport 03 - visão de lado
    if (!scissored) {
        //misturando com a principal
        glViewport(width / 4.0 , height - (height / 4.0), width/4.0, height/4.0);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(width / 4.0 , height - (height / 4.0), width/4.0, height/4.0);
    }
    glViewport(width / 4.0 , height - (height / 4.0), width/4.0, height/4.0);
    glLoadIdentity();
    gluLookAt(10,1,0, 0,0,0, 0,1,0);
    cenario();



    //viewport 04 - visão de cima
    if (!scissored) {
        //misturando com a principal
        glViewport(width - (2*(width/4.0)), height - (height / 4.0), width/4.0, height/4.0);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(width - (2*(width/4.0)), height - (height / 4.0), width/4.0, height/4.0);
    }
    glViewport(width - (2*(width/4.0)), height - (height / 4.0), width/4.0, height/4.0);
    glLoadIdentity();
    gluLookAt(0,10,0, 0,0,0, 0,0,-1);
    cenario();


//    //viewport 05 - goPro - visão acompanhando o movimento do carrinho
    if (!scissored) {
        //misturando com a principal
        glViewport(width - (width/4.0), height - (height / 4.0), width/4.0, height/4.0);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(width - (width/4.0), height - (height / 4.0), width/4.0, height/4.0);
    }
    glViewport(width - (width/4.0), height - (height / 4.0), width/4.0, height/4.0);
    glLoadIdentity();
    if(primeira){
        gluLookAt(c->goPro->e.x,c->goPro->e.y,c->goPro->e.z, c->goPro->c.x,c->goPro->c.y,c->goPro->c.z, c->goPro->u.x,c->goPro->u.y,c->goPro->u.z);
    }
    else{
        gluLookAt(c->goPro3->e.x,c->goPro3->e.y,c->goPro3->e.z, c->goPro3->c.x,c->goPro3->c.y,c->goPro3->c.z, c->goPro3->u.x,c->goPro3->u.y,c->goPro3->u.z);
//        gluLookAt(cam->e.x,cam->e.y,cam->e.z, cam->c.x,cam->c.y, cam->c.z, cam->u.x,cam->u.y,cam->u.z);
//        gluLookAt(jogo->e.x,jogo->e.y,jogo->e.z,jogo->c.x,jogo->c.y,jogo->c.z,jogo->u.x,jogo->u.y,jogo->u.z);
    }

    cenario();

}
//-------------------viewPorts------------------




void cenario() {
    GUI::setLight(3,-5,3,5,true,false);

    if(origem){
        GUI::drawOrigin(0.5);
    }

    GUI::setColor(0,0,0);

    desenhaPontosDeControle();


    if(c->getTipo() >= 1 and c->getTipo()<= 3){
        c->desenhaCurva1(pontosControle, 0.01);
    }
    else{
        c->desenhaCurva2(pontosControle, 0.01);
    }


    if(automatico){
        delta = 0.01;
        c->desenhaIronMan(pontosControle, delta, jogo);
    } else {
        c->desenhaIronMan(pontosControle, delta, jogo);
        delta = 0;
    }
}

void desenha() {
    GUI::displayInit();


    if (!viewports) {
        cenario();
    } else {
        viewPorts();
    }

    //transladando ponto selecionado atraves do picking
    if (pontoSelecionado>=0) {
        pontosControle[pontoSelecionado].x += glutGUI::dtx;
        pontosControle[pontoSelecionado].y += glutGUI::dty;
        pontosControle[pontoSelecionado].z += glutGUI::dtz;
    }

    GUI::displayEnd();
}

void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);

    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'v':
        viewports = !viewports;
        break;
    case 's':
        scissored = !scissored;
        break;


    // Altera entre primeira pessoa e terceira pessoa a visão do carrinho
    case 'k':
        primeira = !primeira;
        break;


    // Adiciona e remove um ponto de controle
    case 'P':
        inserePontoControle();
        break;
    case 'p':
        removePontoControle();
        break;


    // Altera entre as matrizes
    case 'I':
        c->setTipo(1);
        glutSetWindowTitle("Interpoladora");
        break;
    case 'H':
        c->setTipo(2);
        glutSetWindowTitle("Hermite");
        break;
    case 'B':
        c->setTipo(3);
        glutSetWindowTitle("Bezier");
        break;
    case 'C':
        c->setTipo(4);
        glutSetWindowTitle("Catmull-Room");
        break;
    case 'S':
        c->setTipo(5);
        glutSetWindowTitle("B-Spline");
        break;



    // Movimenta o ponto selecionado com o teclado
    case 'X': //move o ponto selecionado no eixo x
        pontosControle.at(pontoSelecionado).x = pontosControle.at(pontoSelecionado).x + .1;
        break;
    case 'x': //move o ponto selecionado no eixo x
        pontosControle.at(pontoSelecionado).x = pontosControle.at(pontoSelecionado).x - .1;
        break;

    case 'Y': //move o ponto selecionado no eixo y
        pontosControle.at(pontoSelecionado).y = pontosControle.at(pontoSelecionado).y + .1;
        break;
    case 'y': //move o ponto selecionado no eixo y
        pontosControle.at(pontoSelecionado).y = pontosControle.at(pontoSelecionado).y - .1;
        break;

    case 'Z': //move o ponto selecionado no eixo z
        pontosControle.at(pontoSelecionado).z = pontosControle.at(pontoSelecionado).z + .1;
        break;
    case 'z': //move o ponto selecionado no eixo z
        pontosControle.at(pontoSelecionado).z = pontosControle.at(pontoSelecionado).z - .1;
        break;

    case 'R': //reseta para o pronto de translação o ponto 0 0 0 o ponto selecionado do vetor
        pontosControle.at(pontoSelecionado).x = 0;
        pontosControle.at(pontoSelecionado).z = 0;
        pontosControle.at(pontoSelecionado).y = 0;
        break;



    // Faz alteração entre os pontos: Avançar e retornar
    case 'n': //Seleciona o proximo ponto da lista
        if (pontoSelecionado != (-1)){
            pontoSelecionado++;
            pontoSelecionado = pontoSelecionado % pontosControle.size();
        }
        break;
    case 'N': //Seleciona o anterior ponto da lista
        if (pontoSelecionado != -1){
            pontoSelecionado--;
            if(pontoSelecionado == -1) pontoSelecionado = pontosControle.size() - 1;
            pontoSelecionado = pontoSelecionado;
        }
    break;


    // Altera entre mover automaticamente e mover pelo teclado
    case 'a':
        automatico = !automatico;
        break;


    // Caso automatico desligado, controle no teclado é possível
    case '.':
        if(!automatico){
            delta = 0.01;
        }
        break;

    case ',':
        if(!automatico){
            delta = -0.01;
        }
        break;

    case 'e':
        origem = !origem;

    default:
        break;
    }
}

void mouse(int button, int state, int x, int y) {
    GUI::mouseButtonInit(button,state,x,y);

    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            //picking
            int pick = picking( x, y, 5, 5 );
            if (pick != 0) {
                pontoSelecionado = pick - 1;
                glutGUI::lbpressed = false;
            }
        }
    }
}

int main()
{
    cout << "Hello World!" << endl;

    pontosControle.push_back(Vetor3D(0,2,-2));
    pontosControle.push_back(Vetor3D(2,0,0));
    pontosControle.push_back(Vetor3D(0,2,2));
    pontosControle.push_back(Vetor3D(-2,-1,0));
    c->setTipo(1);
    GUI gui = GUI(800,600,desenha,teclado,mouse, "Interpoladora");
}
