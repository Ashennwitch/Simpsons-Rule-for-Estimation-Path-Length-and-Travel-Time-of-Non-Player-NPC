/**
 * @file path_analyzer.c
 * @author (Nama Anda)
 * @brief Menganalisis konvergensi panjang lintasan NPC menggunakan Aturan Simpson.
 * @version 2.0
 * @date 2025-06-07
 *
 * @description
 * Versi 2.0 dari program ini mengotomatiskan proses analisis.
 * Program akan melakukan iterasi melalui serangkaian nilai segmen (n)
 * untuk menunjukkan bagaimana hasil perhitungan panjang lintasan konvergen ke nilai yang stabil.
 *
 * Program ini menghasilkan dua file output:
 * 1. path_data.csv: Koordinat (x,y) dari lintasan untuk visualisasi.
 * 2. convergence_analysis.csv: Hasil analisis n vs. panjang lintasan.
 *
 * Cara kompilasi:
 * gcc path_analyzer.c -o path_analyzer -lm
 *
 * Cara menjalankan:
 * ./path_analyzer
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// --- Fungsi Matematika Dasar (tidak berubah) ---

/**
 * @brief Fungsi lintasan f(x) = 2*sin(x) + 0.5*x.
 */
double path_function(double x) {
    return 2 * sin(x) + 0.5 * x;
}

/**
 * @brief Fungsi integran g(x) = sqrt(1 + (f'(x))^2).
 */
double integrand(double x) {
    double derivative = 2 * cos(x) + 0.5;
    return sqrt(1 + pow(derivative, 2));
}

// --- Implementasi Aturan Simpson (tidak berubah) ---

double simpson_one_third(double a, int n, double h) {
    double sum = 0.0;
    for (int i = 1; i < n; i += 2) sum += 4 * integrand(a + i * h);
    for (int i = 2; i < n; i += 2) sum += 2 * integrand(a + i * h);
    sum += integrand(a) + integrand(a + n * h);
    return (h / 3.0) * sum;
}

double simpson_three_eighths(double a, double h) {
    return (3.0 * h / 8.0) * (integrand(a) + 3*integrand(a + h) + 3*integrand(a + 2*h) + integrand(a + 3*h));
}

// --- Fungsi Kalkulasi Inti ---

/**
 * @brief Menghitung panjang lintasan total untuk nilai n tertentu.
 * Secara otomatis memilih aturan Simpson yang sesuai.
 *
 * @param a Batas bawah.
 * @param b Batas atas.
 * @param n Jumlah segmen.
 * @return double Panjang lintasan yang dihitung.
 */
double calculate_total_length(double a, double b, int n) {
    if (n <= 0) return 0.0;
    double h = (b - a) / n;
    
    if (n % 2 == 0) { // Kasus genap
        return simpson_one_third(a, n, h);
    } else if (n >= 3) { // Kasus ganjil
        double length = simpson_three_eighths(a + (n - 3) * h, h);
        if (n > 3) {
           length += simpson_one_third(a, n - 3, h);
        }
        return length;
    } else { // n = 1 (fallback ke trapesium)
        return (h / 2.0) * (integrand(a) + integrand(b));
    }
}


// --- Fungsi Penghasil File Output ---

/**
 * @brief Menghasilkan file CSV berisi data titik (x, y) dari lintasan.
 */
void generate_path_data_for_plotting(double a, double b, int num_points) {
    FILE *file = fopen("path_data.csv", "w");
    if (file == NULL) {
        printf("Error: Gagal membuat file path_data.csv\n");
        return;
    }
    fprintf(file, "x,y\n");
    double step = (b - a) / (num_points - 1);
    for (int i = 0; i < num_points; i++) {
        double current_x = a + i * step;
        double current_y = path_function(current_x);
        fprintf(file, "%f,%f\n", current_x, current_y);
    }
    fclose(file);
    printf("-> File 'path_data.csv' berhasil dibuat untuk visualisasi lintasan.\n");
}

/**
 * @brief Menjalankan analisis konvergensi dan menyimpan hasilnya ke CSV.
 */
void run_convergence_analysis(double a, double b) {
    // Daftar nilai n yang akan diuji
    int n_values[] = {10, 51, 100, 501, 1000, 5000, 10001};
    int num_n_values = sizeof(n_values) / sizeof(n_values[0]);

    FILE *file = fopen("convergence_analysis.csv", "w");
    if (file == NULL) {
        printf("Error: Gagal membuat file convergence_analysis.csv\n");
        return;
    }
    // Header untuk file CSV dan tabel di console
    fprintf(file, "n_segments,calculated_length\n");
    printf("\n--- Analisis Konvergensi Panjang Lintasan ---\n");
    printf("+-----------------+------------------------+\n");
    printf("| Segmen (n)      | Panjang Lintasan (L)   |\n");
    printf("+-----------------+------------------------+\n");

    for (int i = 0; i < num_n_values; i++) {
        int n = n_values[i];
        double length = calculate_total_length(a, b, n);
        printf("| %-15d | %-22.10f |\n", n, length);
        fprintf(file, "%d,%f\n", n, length);
    }
    printf("+-----------------+------------------------+\n");
    fclose(file);
    printf("-> File 'convergence_analysis.csv' berhasil dibuat untuk analisis.\n");
}


int main() {
    double a, b, v;

    printf("--- Penganalisis Panjang Lintasan NPC (v2.0) ---\n");
    printf("Program ini menganalisis lintasan f(x) = 2*sin(x) + 0.5*x\n\n");
    
    // Input pengguna hanya untuk parameter dasar
    printf("Masukkan titik awal lintasan (a): ");
    scanf("%lf", &a);

    printf("Masukkan titik akhir lintasan (b): ");
    scanf("%lf", &b);
    
    printf("Masukkan kecepatan NPC (unit/detik, v): ");
    scanf("%lf", &v);
    
    // Validasi input
    if (b <= a) {
        printf("Error: Input tidak valid. Pastikan b > a.\n");
        return 1;
    }

    // Menjalankan analisis otomatis
    run_convergence_analysis(a, b);
    
    // Menghitung hasil final dengan akurasi tinggi untuk estimasi waktu
    double final_length = calculate_total_length(a, b, 10001); // Gunakan n tertinggi dari analisis
    printf("\n--- Hasil Akhir ---\n");
    printf("Panjang Lintasan Akurat (L): %f unit\n", final_length);
    printf("Estimasi Waktu Tempuh (T = L/v): %f detik\n\n", final_length / v);
    
    // Menghasilkan file untuk plot visual lintasan
    generate_path_data_for_plotting(a, b, 200);

    return 0;
}
