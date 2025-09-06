import PIL
import PIL.Image
import argparse
import pathlib as pl
import re
import struct

parser = argparse.ArgumentParser(
    description="Conversor de sequências de imagens para o formato \"sbmp\"",
    epilog="Feito com <3 por Amélia O. F. S. - 190037971"
)
parser.add_argument(
    "fonte",
    help="Modelo da imagem-fonte. \"@\" será substituído por um número"
)
parser.add_argument("destino", help="Nome do arquivo de destino")

res = parser.parse_args()

src = pl.Path(res.fonte)
pat = re.compile(src.name.replace('@',r"\d+"))
arqs = [
    arq
    for arq in src.parent.iterdir()
    if pat.match(arq.name)
]

if len(arqs) == 0:
    print(f"Nennhum arquivo encontrado com o padrão {pat}")
    exit(-1)

img: PIL.ImageFile.ImageFile = PIL.Image.open(arqs[0])

with open(res.destino, 'wb') as o_f:
    o_f.write(b'SBM')
    o_f.write(struct.pack("<H", img.width))
    o_f.write(struct.pack("<H", img.height))
    o_f.write(struct.pack("<H", len(arqs)))
    img.close()
    byte = 0
    second = 0
    for arq in sorted(arqs):
        img: PIL.ImageFile.ImageFile = PIL.Image.open(arq).convert('LA')
        for p in img.getdata():
            l, a = p
            byte |= ((a > 128) * 8) | (l >> 4)
            if second:
                o_f.write(struct.pack("B", byte))
            second = 1 - second
            byte = (byte << 4) & 0xff
        if second:
            o_f.write(struct.pack("B", byte))

