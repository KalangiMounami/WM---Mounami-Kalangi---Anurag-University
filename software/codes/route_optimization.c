#include <stdio.h>
#include <math.h>

typedef struct {
    int id;
    float lat;
    float lon;
    float fill;
} Bin;

float distance(Bin a, Bin b)
{
    return sqrt(pow(a.lat - b.lat, 2) + pow(a.lon - b.lon, 2));
}

int main()
{
    Bin bins[] = {
        {1, 17.385, 78.486, 90},
        {2, 17.390, 78.480, 85},
        {3, 17.392, 78.490, 60}
    };

    int n = 3;
    Bin pickup[3];
    int count = 0;

    for (int i = 0; i < n; i++)
        if (bins[i].fill > 80)
            pickup[count++] = bins[i];

    for (int i = 0; i < count; i++)
        printf("Collect Bin ID: %d\n", pickup[i].id);

    return 0;
}
