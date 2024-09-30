#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>  // Para salvar em arquivo

using namespace cv;
using namespace std;

// Função para calcular o histograma de uma imagem
void calcularHistograma(const Mat& imagem, vector<float>& histograma_concatenado) {
    // Número de bins (intervalos) do histograma
    int num_bins = 256;
    float range[] = { 0, 256 };  // Valores de 0 a 255 para as cores
    const float* hist_range = { range };

    // Vetores para armazenar os histogramas dos canais B, G e R
    Mat hist_b, hist_g, hist_r;

    // Calcular histograma para cada canal
    calcHist(&imagem, 1, new int[1]{0}, Mat(), hist_b, 1, &num_bins, &hist_range);
    calcHist(&imagem, 1, new int[1]{1}, Mat(), hist_g, 1, &num_bins, &hist_range);
    calcHist(&imagem, 1, new int[1]{2}, Mat(), hist_r, 1, &num_bins, &hist_range);

    // Normalizar os histogramas para ter valores entre 0 e 1
    normalize(hist_b, hist_b, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(hist_g, hist_g, 0, 1, NORM_MINMAX, -1, Mat());
    normalize(hist_r, hist_r, 0, 1, NORM_MINMAX, -1, Mat());

    // Concatenar os três histogramas em um único vetor
    for (int i = 0; i < num_bins; ++i) {
        histograma_concatenado.push_back(hist_b.at<float>(i));  // Canal B
        histograma_concatenado.push_back(hist_g.at<float>(i));  // Canal G
        histograma_concatenado.push_back(hist_r.at<float>(i));  // Canal R
    }
}

// Função para salvar o histograma em um arquivo texto
void salvarHistograma(const vector<float>& histograma, const string& nome_arquivo) {
    ofstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo para salvar o histograma!" << endl;
        return;
    }

    // Salvar o histograma no arquivo
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
