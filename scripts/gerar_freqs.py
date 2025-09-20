# temperamento igual -> 12 notas = X2
# Fator multiplicante = 2**(1/12)
# base (60) = 261.6256
fator = 2**(1/12)
print([
    (int((16000)/(261.6256*(fator**(i-60))))//2)*2+1
    for i in range(0xef)
])