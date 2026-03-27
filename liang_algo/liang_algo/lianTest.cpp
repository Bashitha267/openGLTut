#include <iostream>
using namespace std;

bool liangBarsky(float x0, float y0, float x1, float y1,
                 float left, float right, float bottom, float top,
                 float &x_clipped, float &y_clipped,
                 float &x_clipped_end, float &y_clipped_end)
{
    float t0 = 0.0f, t1 = 1.0f;
    float dx = x1 - x0, dy = y1 - y0;
    float p, q, r;

    for (int edge = 0; edge < 4; edge++)
    {
        if (edge == 0) {         // Left edge
            p = -dx;
            q = x0 - left;
        }
        else if (edge == 1) {    // Right edge
            p = dx;
            q = right - x0;
        }
        else if (edge == 2) {    // Bottom edge
            p = -dy;
            q = y0 - bottom;
        }
        else {                  // Top edge
            p = dy;
            q = top - y0;
        }

        if (p == 0)
        {
            if (q < 0)
                return false; // Line is outside and parallel
        }
        else
        {
            r = q / p;

            if (p < 0)
            {
                if (r > t1)
                    return false;
                else if (r > t0)
                    t0 = r;
            }
            else if (p > 0)
            {
                if (r < t0)
                    return false;
                else if (r < t1)
                    t1 = r;
            }
        }
    }

    // Compute clipped points
    x_clipped = x0 + t0 * dx;
    y_clipped = y0 + t0 * dy;
    x_clipped_end = x0 + t1 * dx;
    y_clipped_end = y0 + t1 * dy;

    return true; // Line is accepted
}