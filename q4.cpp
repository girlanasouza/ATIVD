/*
Histograma local. Defina um particionamento da imagemm com no mínimo 3 partições.
Concatenar os histogramas em um único vetor. Armazenar o resultado em um arquivo para
facilitar a visualização do resultado.
*/

#include <opencv2/opencv.hpp>
#include <fstream>
#include <vector>


using namespace std;

vector<int> calculateHistogram(const cv::Mat& imagem) {
    vector<int> histogram(256, 0);  
    for (int i = 0; i < imagem.rows; ++i) {
        for (int j = 0; j < imagem.cols; ++j) {
            int intensity = imagem.at<uchar>(i, j);
            histogram[intensity]++;
        }
    }
    return histogram;
}

vector<int> histogramaLocal(const cv::Mat& imagem, int linhas, int cols) {
    cout<<"im here\n";
    vector<int> hist;
    int partHeight = imagem.rows / linhas;
    int partWidth = imagem.cols / cols;

    for (int r = 0; r < linhas; ++r) {
        for (int c = 0; c < cols; ++c) {
            cv::Rect region(c * partWidth, r * partHeight, partWidth, partHeight);
            cv::Mat partition = imagem(region);
            vector<int> hist = calculateHistogram(partition);
            hist.insert(hist.end(), hist.begin(), hist.end());
        }
    }
    return hist;
}

void salvarHisto(const vector<int>& histogram, const string& filename) {
    ofstream file(filename);
    for (const auto& value : histogram) {
        file << value << ",";
    }
    file.close();
}

int main() {
    cv::Mat imagem = cv::imread("input/gray.jpg", cv::IMREAD_GRAYSCALE);
    if (imagem.empty()) {
        cerr << "Erro ao abrir a imagemm!" << endl;
        return -1;
    }

    vector<int> histogramas = histogramaLocal(imagem, 3, 3);
    salvarHisto(histogramas, "output/histogram_local.csv");

    return 0;
}
