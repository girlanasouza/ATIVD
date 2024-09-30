import cv2

def alterar_brilho(imagem, valor_brilho):
    imagem_resultado = cv2.convertScaleAbs(imagem, alpha=1, beta=valor_brilho)
    return imagem_resultado

def main():
    # Carregar a imagem (ajuste o caminho conforme o local onde sua imagem está armazenada)
    imagem = cv2.imread('entrada.jpg')

    if imagem is None:
        print("Erro ao carregar a imagem!")
        return

    # Solicitar o valor de brilho ao usuário
    valor_brilho = int(input("Digite o valor de brilho para alterar (-255 a 255): "))

    imagem_resultado = alterar_brilho(imagem, valor_brilho)
    cv2.imwrite("imagem_com_brilho.jpg", imagem_resultado)

if __name__ == "__main__":
    main()
