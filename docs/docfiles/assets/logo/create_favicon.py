""" Code for creating a favicon from an input image. """

import sys

from PIL import Image


def create_favicon(input_path, output_path, size=(16, 16)):
    try:
        # Open the PNG image
        img = Image.open(input_path)

        # Resize the image to the favicon size
        img = img.resize(size, Image.Resampling.LANCZOS)

        # Save the resized image as a favicon ICO file
        img.save(output_path, format="ICO", sizes=[(size[0], size[1])])

        print(f"Favicon created successfully: {output_path}")

    except Exception as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    if not len(sys.argv) == 3:
        raise ValueError("Usage: python create_favicon.py input_image.png output_favicon.ico")

    input_png_path = sys.argv[1]
    output_favicon_path = sys.argv[2]
    create_favicon(input_png_path, output_favicon_path)
