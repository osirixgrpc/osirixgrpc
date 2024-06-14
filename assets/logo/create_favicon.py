""" Code for creating a favicon from an input image. """

import sys

from PIL import Image, ImageOps


def create_favicon(input_path, output_path, size=(16, 16)):
    try:
        # Open the PNG image
        img = Image.open(input_path)

        # Resize the image while maintaining its aspect ratio
        img.thumbnail(size, Image.Resampling.LANCZOS)

        # Create a new square canvas with the specified size
        squared_img = Image.new("RGBA", size, (0, 0, 0, 0))

        # Calculate the position to paste the resized image at the center
        position = ((size[0] - img.width) // 2, (size[1] - img.height) // 2)

        # Paste the resized image onto the square canvas
        squared_img.paste(img, position)

        # Save the squared image as a favicon ICO file
        squared_img.save(output_path, format="ICO", sizes=[(size[0], size[1])])

        print(f"Favicon created successfully: {output_path}")

    except Exception as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    if not len(sys.argv) == 3:
        raise ValueError("Usage: python create_favicon.py input_image.png output_favicon.ico")

    input_png_path = sys.argv[1]
    output_favicon_path = sys.argv[2]
    create_favicon(input_png_path, output_favicon_path)
