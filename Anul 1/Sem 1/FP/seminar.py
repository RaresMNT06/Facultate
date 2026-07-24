import matplotlib.pyplot as plt
import numpy as np

# 1. DEFINIREA DATELOR DIN TABEL
# Frecvența (axa X)
freq = np.array([0.002, 0.005, 0.1, 0.25, 0.5, 0.75, 1, 3, 5, 20, 50,
                 100, 250, 500, 700, 1000, 1250, 1500, 1750, 2000])
# Tensiunea măsurată (axa Y)
u_out = np.array([1.48, 2.1, 3, 5.1, 9.2, 9.2, 9.4, 9.4, 9.4, 8.4, 5.5,
                  3.2, 2, 6.8, 5.4, 4, 3.2, 2.6, 2.6, 2.2])

# 2. CALCULE PRELIMINARE
# Maximul tensiunii
u_max = 9.4
# Pragul de -3dB (0.707 din maxim)
u_prag = u_max * 0.707




# 3. DETERMINAREA FRECVENȚELOR LIMITĂ (Interpolare liniară)
# Căutăm Frecvența Joasă (f_jos) - prima intersecție
idx_low = np.where(u_out >= u_prag)[0][0]
x1, x2 = freq[idx_low-1], freq[idx_low]
y1, y2 = u_out[idx_low-1], u_out[idx_low]
# Formula liniei drepte pentru a găsi exact locul unde trece prin u_prag
f_jos = x1 + (u_prag - y1) * (x2 - x1) / (y2 - y1)

# Căutăm Frecvența Înaltă (f_sus) - a doua intersecție
# Ignorăm zona de "anomalie" de la 500kHz pentru calculul corect
idx_high = np.where((freq > 5) & (u_out < u_prag))[0][0]
x1_h, x2_h = freq[idx_high-1], freq[idx_high]
y1_h, y2_h = u_out[idx_high-1], u_out[idx_high]
f_sus = x1_h + (u_prag - y1_h) * (x2_h - x1_h) / (y2_h - y1_h)

# Banda
banda = f_sus - f_jos

# 4. AFIȘAREA REZULTATELOR ÎN CONSOLĂ
print("-" * 30)
print("REZULTATE CALCULATE:")
print(f"Tensiunea Maximă (U_max): {u_max} V")
print(f"Pragul de -3dB:           {u_prag:.2f} V")
print("-" * 30)
print(f"Frecvența Joasă (f_j):    {f_jos:.3f} kHz")
print(f"Frecvența Înaltă (f_s):   {f_sus:.3f} kHz")
print(f"Banda de frecvență (B):   {banda:.3f} kHz")
print("-" * 30)



# 5. GENERAREA GRAFICULUI
plt.figure(figsize=(10, 6))

# Punctele experimentale
plt.semilogx(freq, u_out, 'bo', label='Puncte măsurate')

# Linia continuă (fără anomalie pentru claritate)
mask_anomalie = freq != 500
plt.semilogx(freq[mask_anomalie], u_out[mask_anomalie], 'b-', linewidth=2, label='Caracteristica')

# Linia de prag (roșie)
plt.axhline(y=u_prag, color='r', linestyle='--', label='Prag -3dB')

# Liniile verticale pentru f_jos și f_sus
plt.axvline(x=f_jos, color='g', linestyle=':')
plt.axvline(x=f_sus, color='g', linestyle=':')

# Etichete și titlu
plt.xlabel('Frecvența [kHz] (Scară Logaritmică)')
plt.ylabel('Tensiunea de ieșire [V]')
plt.title('Caracteristica de Frecvență')
plt.grid(True, which="both", alpha=0.5)
plt.legend()

# Salvarea imaginii (opțional)
# plt.savefig('grafic.png') 

plt.show()
