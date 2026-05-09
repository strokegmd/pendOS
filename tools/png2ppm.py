from PIL import Image

def image_to_ppm(image_path: str) -> bytes:
    image = Image.open(image_path).convert('RGB')
    width, height = image.size

    header = f'P6\n{width} {height}\n255\n'.encode()

    pixel_data = image.tobytes()
    return pixel_data # TODO: header is currently unused due to bad ppm renderer in OS

def main():
    filename = input('[*] .png filename >> ')
    data = image_to_ppm(filename)

    with open('output.ppm', 'wb') as file:
        file.write(data)
    
    print('[*] saved to output.ppm.')

if __name__ == '__main__':
    main()
