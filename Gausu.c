#include<stdio.h>
#include <math.h>

int main() {
    double a = 1.0, b = 1.0 / sqrt(2.0), t = 1.0 / 4, x = 1.0, an, p; 
    int n;
    for (n = 1; n <= 100; n++) {
        an = (a + b) / 2;  // 算術平均。前の a を後で使うので、次の a を an に
        b = sqrt(a * b);   // 幾何平均。前の b はもう使わないので、書き変える
        t -= x * (an - a) * (an - a);
        x *= 2;           // 前の x はもう使わないので、ここで書き変える
        a = an;           // a の値を新しい値に変える
        p = (a + b) * (a + b) / (4 * t);        // πの近似値を計算する 
        printf("%2d %0.40lf  3.141592653589793･･･\n", n, p);
    }
}