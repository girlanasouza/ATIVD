import cv2
import numpy as np

# Função de Expansão de Contraste Linear
def linear_contrast_expansion(src):
    min_val, max_val = cv2.minMaxLoc(src)[:2]  # Encontra os valores mínimo e máximo
    dst = cv2.convertScaleAbs(src, alpha=255.0 / (max_val - min_val), beta=-min_val * 255.0 / (max_val - min_val))
    return dst

# Função de Compressão e Expansão (usando a função potência)
def compression_expansion(src, gamma):
    dst = np.float64(src)
    dst = cv2.normalize(dst, None, 0, 1, cv2.NORM_MINMAX)
    dst = np.power(dst, gamma)  # Aplica a função potência
    dst = cv2.convertScaleAbs(dst * 255)
    return dst

# Função de Dente de Serra
def sawtooth_transformation(src, period):
    dst = src.copy()
    for i in range(src.shape[0]):
        for j in range(src.shape[1]):
            dst[i, j] = int(255 * (src[i, j] / 255.0 % period))
    return dst

# Função de Transformada do Logaritmo
def logarithmic_transformation(src):
    dst = np.float64(src)  # Converte para double para evitar truncamento
    dst += 1  # Evita log(0)
    dst = np.log(dst)  # Aplica a transformação logarítmica
    dst = cv2.normalize(dst, None, 0, 255, cv2.NORM_MINMAX)  # Normaliza o resultado
    dst = cv2.convertScaleAbs(dst)  # Converte de volta para 8 bits
    return dst

def main():
    # Carregar a imagem em tons de cinza
    image = cv2.imread("input/entrada.jpg", cv2.IMREAD_GRAYSCALE)
    if image is None:
        print("Erro ao carregar a imagem!")
        return

    # Aplicar as transformações
    linear_contrast = linear_contrast_expansion(image)
    compression_expansion_img = compression_expansion(image, 0.5)  # Gamma < 1 para expansão
    sawtooth = sawtooth_transformation(image, 4.0)  # Período para o dente de serra
    logarithmic = logarithmic_transformation(image)

    # Exibir as imagens
    cv2.imshow("Original", image)
    cv2.imshow("Linear Contrast Expansion", linear_contrast)
    cv2.imshow("Compression & Expansion (Gamma)", compression_expansion_img)
    cv2.imshow("Sawtooth Transformation", sawtooth)
    cv2.imshow("Logarithmic Transformation", logarithmic)

    # Salvar as imagens resultantes
    cv2.imwrite("linear_contrast.jpg", linear_contrast)
    cv2.imwrite("compression_expansion.jpg", compression_expansion_img)
    cv2.imwrite("sawtooth.jpg", sawtooth)
    cv2.imwrite("logarithmic.jpg", logarithmic)

    cv2.waitKey(0)
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
