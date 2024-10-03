/*
Histograma global. Gerar um vetor para representar o histograma da imagem. Concatenar o histograma de cada banda RGB em 
um único vetor. Armazenar o resultado em um arquivo texto para facilitar a visualização do resultado.
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream> 

using namespace cv;
using namespace std;

void calcularHistograma(const Mat& imagem, vector<float>& histograma_concatenado) {
    int num_bins = 256;
    float range[] = { 0, 256 };  
    const float* hist_range = { range };

    Mat hist_b, hist_g, hist_r;

    calcHist(&imagem, 1, new int[1]{0}, Mat(), hist_b, 1, &num_bins, &hist_range);
    calcHist(&imagem, 1, new int[1]{1}, Mat(), hist_g, 1, &num_bins, &hist_range);
    calcHist(&imagem, 1, new int[1]{2}, Mat(), hist_r, 1, &num_bins, &hist_range);

    normalize(hist_b, hist_b, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(hist_g, hist_g, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(hist_r, hist_r, 0, 1, NORM_MINMAX, -1, Mat());

    for (int i = 0; i < num_bins; ++i) {
        histograma_concatenado.push_back(hist_b.at<float>(i));  // Canal B
        histograma_concatenado.push_back(hist_g.at<float>(i));  // Canal G
        histograma_concatenado.push_back(hist_r.at<float>(i));  // Canal R
    }
}

void salvarHistograma(const vector<float>& histograma, const string& nome_arquivo) {
    ofstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para salvar o histograma!" << endl;
        return;
    }

    for (const auto& valor : histograma) {
        arquivo << valor << endl;
    }

    arquivo.close();
    cout << "Histograma salvo em " << nome_arquivo << endl;
}

int main() {
    // Carregar a imagem (substitua o caminho pelo caminho correto da imagem)
    Mat imagem = imread("input/entrada.jpg");

    if (imagem.empty()) {
        cout << "Erro ao carregar a imagem!" << endl;
        return -1;
    }

    // Vetor para armazenar o histograma concatenado
    vector<float> histograma_concatenado;

    // Calcular o histograma global da imagem
    calcularHistograma(imagem, histograma_concatenado);

    // Salvar o histograma em um arquivo texto
    salvarHistograma(histograma_concatenado, "output/histograma.txt");

    return 0;
}
