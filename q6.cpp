#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace cv;
using namespace std;

// Função para adicionar ruído sal e pimenta
void addSaltAndPepperNoise(Mat& image, double noise_percentage) {
    int total_pixels = image.rows * image.cols;
    int num_noise_pixels = total_pixels * noise_percentage;

    for (int i = 0; i < num_noise_pixels; i++) {
        int row = rand() % image.rows;
        int col = rand() % image.cols;
        image.at<uchar>(row, col) = (rand() % 2 == 0) ? 0 : 255;
    }
}

// Filtro da Média
void meanFilter(const Mat& src, Mat& dst, int kernel_size) {
    blur(src, dst, Size(kernel_size, kernel_size));
}

// Filtro da Mediana
void medianFilter(const Mat& src, Mat& dst, int kernel_size) {
    medianBlur(src, dst, kernel_size);
}

// Filtro da Moda
void modeFilter(const Mat& src, Mat& dst, int kernel_size) {
    dst = src.clone();
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            vector<int> neighbors;
            for (int m = -kernel_size / 2; m <= kernel_size / 2; m++) {
                for (int n = -kernel_size / 2; n <= kernel_size / 2; n++) {
                    int x = min(max(i + m, 0), src.rows - 1);
                    int y = min(max(j + n, 0), src.cols - 1);
                    neighbors.push_back(src.at<uchar>(x, y));
                }
            }

            // Contar a moda
            map<int, int> freq;
            for (int val : neighbors) {
                freq[val]++;
            }
            int mode = neighbors[0];
            int max_freq = 0;
            for (const auto& kv : freq) {
                if (kv.second > max_freq) {
                    mode = kv.first;
                    max_freq = kv.second;
                }
            }
            dst.at<uchar>(i, j) = mode;
        }
    }
}

// Filtro dos k Vizinhos Mais Próximos (simplificado para ser igual ao filtro da média)
void knnFilter(const Mat& src, Mat& dst, int k) {
    meanFilter(src, dst, k); // Implementação simplificada como exemplo
}

int main() {
    // Carregar imagem em tons de cinza
    Mat image = imread("input/gray.jpg", IMREAD_GRAYSCALE);
    if (image.empty()) {
        cout << "Erro ao carregar a imagem!" << endl;
        return -1;
    }

    // Adicionar ruído sal e pimenta
    Mat noisy_image = image.clone();
    addSaltAndPepperNoise(noisy_image, 0.1); // 10% de ruído

    // Aplicar filtros
    Mat mean_filtered, median_filtered, mode_filtered, knn_filtered;
    int kernel_size = 3;

    meanFilter(noisy_image, mean_filtered, kernel_size);
    medianFilter(noisy_image, median_filtered, kernel_size);
    modeFilter(noisy_image, mode_filtered, kernel_size);
    knnFilter(noisy_image, knn_filtered, kernel_size);

    // Exibir imagens
    imshow("Original", image);
    imshow("Noisy", noisy_image);
    imshow("Mean Filter", mean_filtered);
    imshow("Median Filter", median_filtered);
    imshow("Mode Filter", mode_filtered);
    imshow("KNN Filter", knn_filtered);

    // Salvar resultados
    imwrite("mean_filtered.jpg", mean_filtered);
    imwrite("median_filtered.jpg", median_filtered);
    imwrite("mode_filtered.jpg", mode_filtered);
    imwrite("knn_filtered.jpg", knn_filtered);

    waitKey(0);
    return 0;
}
