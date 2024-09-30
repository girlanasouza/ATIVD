#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat inverterCores(const Mat& imagem) {
    Mat imagem_negativa;
    bitwise_not(imagem, imagem_negativa); 
    return imagem_negativa;
}

int main() {
    Mat imagem = imread("input/entrada.jpg");

    if (imagem.empty()) {
        cout << "Erro ao carregar a imagem!" << endl;
        return -1;
    }

    Mat imagem_negativa = inverterCores(imagem);

    imwrite("output/imagem_negativa.jpg", imagem_negativa);

    return 0;
}
