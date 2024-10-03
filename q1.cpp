#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat alterarBrilho(const Mat& imagem, int valor_brilho) {
    Mat imagem_resultado;
    imagem.convertTo(imagem_resultado, -1, 1, valor_brilho); 
    return imagem_resultado;
}

int main() {
    Mat imagem = imread("input/entrada.jpg");
    if (imagem.empty()) {
        cout << "Erro ao carregar a imagem!" << endl;
        return -1;
    }

    int valor_brilho;
    cout << "Digite o valor de brilho para alterar (-255 a 255): ";
    cin >> valor_brilho;

    Mat imagem_resultado = alterarBrilho(imagem, valor_brilho);

    imwrite("output/saida_imagem_com_brilho_50.jpg", imagem_resultado);

    return 0;
}
