import cv2
import numpy as np
import random
from collections import Counter

def add_salt_and_pepper_noise(image, noise_percentage):
    noisy_image = image.copy()
    total_pixels = image.shape[0] * image.shape[1]
    num_noise_pixels = int(total_pixels * noise_percentage)

    for _ in range(num_noise_pixels):
        row = random.randint(0, image.shape[0] - 1)
        col = random.randint(0, image.shape[1] - 1)
        noisy_image[row, col] = 0 if random.randint(0, 1) == 0 else 255
    
    return noisy_image


def mean_filter(src, kernel_size):
    return cv2.blur(src, (kernel_size, kernel_size))


def median_filter(src, kernel_size):
    return cv2.medianBlur(src, kernel_size)


def mode_filter(src, kernel_size):
    dst = src.copy()
    padded_src = cv2.copyMakeBorder(src, kernel_size // 2, kernel_size // 2, kernel_size // 2, kernel_size // 2, cv2.BORDER_REPLICATE)

    for i in range(src.shape[0]):
        for j in range(src.shape[1]):
            neighbors = []
            for m in range(-kernel_size // 2, kernel_size // 2 + 1):
                for n in range(-kernel_size // 2, kernel_size // 2 + 1):
                    neighbors.append(padded_src[i + m + kernel_size // 2, j + n + kernel_size // 2])

            mode_value = Counter(neighbors).most_common(1)[0][0]
            dst[i, j] = mode_value

    return dst

# filtro knn usando a média 
def knn_filter(src, kernel_size):
    return mean_filter(src, kernel_size)

def main():
    image = cv2.imread("input/gray.jpg", cv2.IMREAD_GRAYSCALE)
    if image is None:
        print("Erro ao carregar a imagem!")
        return

    # Adicionar ruído sal e pimenta
    noisy_image = add_salt_and_pepper_noise(image, 0.1)  # 10% de ruído

    kernel_size = 3

    mean_filtered = mean_filter(noisy_image, kernel_size)
    median_filtered = median_filter(noisy_image, kernel_size)
    mode_filtered = mode_filter(noisy_image, kernel_size)
    knn_filtered = knn_filter(noisy_image, kernel_size)

    cv2.imwrite("output/noisy_image.jpg", noisy_image)
    cv2.imwrite("output/mean_filtered.jpg", mean_filtered)
    cv2.imwrite("output/median_filtered.jpg", median_filtered)
    cv2.imwrite("output/mode_filtered.jpg", mode_filtered)
    cv2.imwrite("output/knn_filtered.jpg", knn_filtered)

if __name__ == "__main__":
    main()
