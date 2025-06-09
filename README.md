# Kalkulator Panjang Lintasan NPC dengan Aturan Simpson

**Oleh: Hanif Nur Ilham Sanjaya**
**NPM: 2206059692**

---

### Deskripsi Program

Program ini adalah sebuah utilitas yang ditulis dalam bahasa C untuk menghitung panjang busur (panjang lintasan) dari sebuah kurva matematika yang merepresentasikan jalur *Non-Player Character* (NPC) dalam sebuah simulasi atau game. Selain menghitung total panjang lintasan, program ini juga mengestimasi waktu yang dibutuhkan NPC untuk menempuh lintasan tersebut berdasarkan kecepatan yang diberikan.

Untuk mendapatkan hasil yang akurat, program ini mengimplementasikan metode integrasi numerik, yaitu **Aturan Simpson 1/3** dan **Aturan Simpson 3/8**. Program ini juga dirancang untuk dapat menangani jumlah segmen (interval) genap maupun ganjil secara cerdas dengan mengombinasikan kedua aturan tersebut.

Sebagai tambahan, program akan menghasilkan sebuah file `path_data.csv` yang berisi kumpulan titik koordinat (x, y) dari lintasan. File ini dapat dengan mudah digunakan untuk melakukan visualisasi atau plotting kurva menggunakan perangkat lunak seperti Microsoft Excel, Gnuplot, atau pustaka Python (Matplotlib, Seaborn).

### Latar Belakang Teori

Panjang busur (L) dari sebuah fungsi kontinu $f(x)$ dari titik $a$ ke $b$ dihitung menggunakan formula integral:
$$L = \int_{a}^{b} \sqrt{1 + [f'(x)]^2} \,dx$$

Dalam program ini, fungsi yang digunakan adalah:
- **Fungsi Lintasan:** $f(x) = 2\sin(x) + 0.5x$
- **Turunan Fungsi:** $f'(x) = 2\cos(x) + 0.5$

Karena integral ini kompleks untuk diselesaikan secara analitis, maka pendekatan numerik dengan **Aturan Simpson** digunakan untuk mendapatkan nilai aproksimasinya.

### Fitur Utama

- **Perhitungan Panjang Lintasan Akurat:** Menggunakan Aturan Simpson gabungan (1/3 dan 3/8) untuk presisi yang lebih tinggi dibandingkan metode trapesium.
- **Estimasi Waktu Tempuh:** Menghitung perkiraan waktu perjalanan NPC berdasarkan panjang lintasan dan kecepatan.
- **Fleksibel:** Dapat menangani input jumlah segmen (`n`) yang genap maupun ganjil.
- **Output untuk Visualisasi:** Secara otomatis menghasilkan file `path_data.csv` untuk memudahkan plotting lintasan.
- **Interaktif:** Menerima input dari pengguna untuk menentukan parameter perhitungan (batas awal, batas akhir, jumlah segmen, dan kecepatan).

### Cara Menggunakan Program

1.  **Simpan Kode:** Simpan kode sumber dengan nama `npc_path_length.c`.

2.  **Kompilasi:** Buka terminal atau command prompt, lalu kompilasi file menggunakan GCC. Flag `-lm` diperlukan untuk me-link pustaka matematika (`math.h`).
    ```bash
    gcc npc_path_length.c -o npc_path_length -lm
    ```

3.  **Jalankan:** Eksekusi file hasil kompilasi.
    ```bash
    ./npc_path_length
    ```

4.  **Masukkan Input:** Program akan meminta Anda untuk memasukkan:
    - Titik awal lintasan (a)
    - Titik akhir lintasan (b)
    - Jumlah segmen untuk integrasi (n)
    - Kecepatan NPC (v)