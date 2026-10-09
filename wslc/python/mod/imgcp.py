

from PIL import Image
import subprocess

def compress_image():

    op = subprocess.run(['wslpath','-u',
                     r"D:\fold\cutpaper\x.jpg"
                    ],capture_output = True,text = True).stdout.strip()

    sv = subprocess.run(['wslpath','-u',
                         r"D:\fold\cutpaper\out.jpg"
                         ],capture_output = True,text = True).stdout.strip()

    with Image.open(op) as img:
        img.thumbnail((3510,4950))
        img.save(sv,quality = 100,optimize = False)

compress_image()