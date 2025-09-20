import mido
import pathlib as pl
import argparse
from typing import List, Literal
import struct

parser = argparse.ArgumentParser(
    description="Conversor de MIDI para SMIDI",
    epilog="Feito com <3 por Amélia O. F. S. - 190037971"
)

parser.add_argument("destino", help="Diretório ou arquivo de destino. Se for um diretório, os arquivos criados têm o mesmo nome dos originais, alterando-se somente o sufixo")
parser.add_argument(
    "fonte",
    nargs="+", help="diretórios ou arquivos a converter. Se for um diretório, converte recursivamente todos os arquivos lá contidos"
)

res = parser.parse_args()

def arquivos(p: pl.Path) -> List[pl.Path]:
    if p.is_dir():
        return [b for a in p.iterdir() for b in arquivos(a)]
    else:
        return [p]

fontes = [
    (arq, arq.relative_to(path if path.is_dir() else path.parent))
    for fonte in res.fonte
    for path in [pl.Path(fonte)]
    for arq in arquivos(path)
]

dest = pl.Path(res.destino)

if len(fontes)>1 and not dest.is_dir():
    print("Mais de um arquivo-fonte foi encontrado, mas o destino é um arquivo!")
    exit(-1)

pares = [
    (f, dest.joinpath(rf).with_suffix('.smid') if dest.is_dir() else dest)
    for f, rf in fontes
]

BUSCATEMPO = 0
BUSCANOTA = 1

DESLIGA = 0
LIGA = 1
IDK = 2

for src, dst in pares:
    dst.parent.mkdir(exist_ok=True, parents=True)
    with open(dst, 'wb') as o_f:
        o_f.write(b'SMI')
        print(f"Processando {src}")
        estado: Literal[BUSCATEMPO, BUSCANOTA] = BUSCATEMPO
        mpt:float = 0.0 # Milissegundos por tempo MIDI
        for msg in mido.MidiFile(src):
            if estado == BUSCATEMPO:
                if isinstance(msg, mido.MetaMessage):
                    if msg.type=='set_tempo':
                        mpt:float = msg.tempo*1e-3
                        o_f.write(struct.pack("=H", int(mpt)))
                        estado = BUSCANOTA
                else:
                    print(f"Erro no arquivo {src}: Notas antes da definição do tempo")
                    break
            elif estado == BUSCANOTA:
                if isinstance(msg, mido.MetaMessage) and msg.type=='set_tempo':
                    print(f"Erro no arquivo {src}: mais de uma definição de tempo.")
                tipo: Literal = IDK
                if msg.type=="note_off":
                    tipo = DESLIGA
                elif msg.type=="note_on":
                    if msg.velocity==0:
                        tipo = DESLIGA
                    else:
                        tipo = LIGA
                if tipo<2:
                    o_f.write(struct.pack(
                        "B",
                        (tipo<<7)|(msg.note & 0x7F)
                    ))
                    o_f.write(struct.pack(
                        "B",
                        int(msg.time*(2**4))&0xFF
                    ))
