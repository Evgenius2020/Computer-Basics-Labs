#define N 3
#define M 1000

static float A[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
static float elements[M + 1][N][N];
static float B[N][N];
static float R[N][N];
static float buf[N][N];
static float AI[N][N];
static int i, j;

void matrixMultiply(float a[N][N], float b[N][N])
{
    float s;
    int k;

    for (i = 0; i < N; i++)
    {
        for (k = 0; k < N; k++)
        {
            s = 0;
            for (j = 0; j < N; j++)
            {
                s += a[i][j] * b[j][k];
            }
            buf[i][k] = s;
        }
    }
}

void matrixAdd(float a[N][N], float b[N][N])
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            buf[i][j] = a[i][j] + b[i][j];
        }
    }
}

void clearBuf()
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            buf[i][j] = 0;
        }
    }
}

void transpose(float matrix[N][N])
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            buf[i][j] = A[j][i];
        }
    }
}

void setMatrix(float matrix[N][N])
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            matrix[i][j] = buf[i][j];
        }
    }
}

int main()
{
    int i, j;
    float q;
    // Calculating q
    float q1 = 0, qinf = 0;
    int s;
    for (i = 0; i < N; i++)
    {
        s = 0;
        for (j = 0; j < N; j++)
        {
            s += A[i][j] > 0 ? A[i][j] : -A[i][j];
        }
        if (s > q1) {
            q1 = s;
        }
    }
    transpose(A);
    for (i = 0; i < N; i++)
    {
        s = 0;
        for (j = 0; j < N; j++)
        {
            s += buf[i][j] > 0 ? buf[i][j] : -buf[i][j];
        }
        if (s > qinf) {
            qinf = s;
        }
    }
    q = q1 * qinf;

    // Calculating B
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            B[i][j] = buf[i][j] / q;
        }
    }

    // Calculating R
    matrixMultiply(B, A);
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            R[i][j] = -buf[i][j];
        }
    }
    for (i = 0; i < N; i++)
    {
        R[i][i] += 1;
    }

    // Calculating elements [1, R, R^2 ..]
    for (i = 0; i < N; i++)
    {
        elements[0][i][i] = 1;
    }
    for (i = 1; i < M; i++)
    {
        matrixMultiply(elements[i - 1], R);
        setMatrix(elements[i]);
    }

    //  (1 + R + R^2 + ..)B
    clearBuf();
    for (i = 0; i < M; i++)
    {
        matrixAdd(buf, elements[i]);
    }
    matrixMultiply(buf, B);
    setMatrix(AI);
    return 0;
}