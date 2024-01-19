/*За програмски јазик да се употреби C.
Од стандарден влез се внесува број n, број на кругови кои ќе се внесуваат, каде 0<n<100. Потоа во наредните n линии се внесуваат x и y кои го претставуваат центарот на кругот како и радиусот на кругот. На стандарден излез се печати плоштината и центарот само најголемиот круг (со најголема плоштина).
Напомена: Доколку има повеќе кругови со иста плоштина се печати само првиот круг со таа плоштина.
Во структурата Точка (Point) треба да се чуваат следните информации:
-x координата (int)
-y координата (int)
Во структурата Круг (Circle) треба да се чуваат следните информации:
-Центар (Point)
-Радиус (int)*/

#include <stdio.h>
#define PI 3.14
typedef struct Tocka{
    int x;
    int y;
}point;
typedef struct Krug{
    point centar;
    int radius;
}circle;
int main() {
    int n, P, i, rad;
    scanf("%d",&n);
    circle Max;
    Max.centar.x = 0;
    Max.centar.y = 0;
    Max.radius = 0;
    for(i=0;i<n;i++){
        point centar;
        scanf("%d %d %d",&centar.x,&centar.y,&rad);
        P=PI*rad*rad;
        if(P>PI*Max.radius*Max.radius){
            Max.radius=rad;
            Max.centar=centar;
        }
    }
    printf("Largest circle has area of: %.2f with centre: (%d,%d)",Max.radius*Max.radius*PI,Max.centar.x,Max.centar.y);
return 0;
}
