// LabaM2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<cmath>
const int n = 3;
const int m = 3;

void KramerMethod(int Mat[n][m],int Slau[n][1]) {
    int Det;
    double D1, D2, D3;
    double x1, x2, x3;
    Det = Mat[0][0]*(Mat[1][1]*Mat[2][2]-Mat[2][1]*Mat[1][2])-
        Mat[0][1]*(Mat[1][0]*Mat[2][2]-Mat[1][2]*Mat[2][0])+
        Mat[0][2]*(Mat[1][0] * Mat[2][1] - Mat[1][1] * Mat[2][0]);
    if (Det != 0) {
        D1 = Slau[0][0] * (Mat[1][1] * Mat[2][2] - Mat[2][1] * Mat[1][2]) -
            Mat[0][1] * (Slau[1][0] * Mat[2][2] - Mat[1][2] * Slau[2][0]) +
            Mat[0][2] * (Slau[1][0] * Mat[2][1] - Mat[1][1] * Slau[2][0]);
        D2 = Mat[0][0] * (Slau[1][0] * Mat[2][2] - Slau[2][0] * Mat[1][2]) -
            Slau[0][0] * (Mat[1][0] * Mat[2][2] - Mat[1][2] * Mat[2][0]) +
            Mat[0][2] * (Mat[1][0] * Slau[2][0] - Slau[1][0] * Mat[2][0]);
        D3 = Mat[0][0] * (Mat[1][1] * Slau[2][0] - Mat[2][1] * Slau[1][0]) -
            Mat[0][1] * (Mat[1][0] * Slau[2][0] - Slau[1][0] * Mat[2][0]) +
            Slau[0][0] * (Mat[1][0] * Mat[2][1] - Mat[1][1] * Mat[2][0]);
        x1 = D1 / Det;
        x2 = D2 / Det;
        x3 = D3 / Det;
        std::cout<<"x1= "<< x1<<" " << "x2= " << x2 << " " << "x3= " << x3<<std::endl;
    }
    else
        std::cout << "infinite solutions cause Det = "<< Det << std::endl;
}

void ItterMethod(int Mat[n][m], int Slau[n][1]) {
    double Xs[n][1];
    double ItterMat[n][m], ItterSlau[n][1];
    double summ = 0;
    for (int i = 0; i < 1; i++) {
        for (int j = 0;j < n;j++) {
            ItterSlau[i][j] = double(Slau[i][j])/double(Mat[i][i]); 
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0;j < n;j++) {
            ItterMat[i][j] = -(double(Mat[i][j]) / double(Mat[i][i]));
        }
        ItterMat[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0;j < n;j++) {
            summ += pow(ItterMat[i][j],2);
        }
    }
    if (sqrt(summ) > 1) {
        std::cout << "Sqrt of summ of pow of ItterMatrix elements equals: "<<summ<<" it means that this Matrix has no solution " << std::endl;
    }
    else {
        for (int i = 0; i < n; i++) {
            Xs[i][0] = ItterSlau[i][0];
        }

        for (int i = 0; i < n; i++) {
            double sum = 0;

            for (int j = 0; j < n; j++) {
                sum += ItterMat[i][j] * Xs[j][0];
            }
            double newX = sum + ItterSlau[i][0];

            Xs[i][0] = newX;
        }

        std::cout << "Matrix's soulution by ItterMethod: \n";
        for (int i = 0; i < n; i++) {
            std::cout <<"x"<<i<<"= " << Xs[i][0] << "\n";
        }
    }
}

int main()
{

    int Matrix[n][m];
    int SLAU[3][1];

    for (int i = 0; i < 3; i++) {
        for (int j = 0;j < 3;j++) {
            Matrix[i][j] = rand() % 25;
            
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0;j < 3;j++) {
            if (Matrix[i][j] > Matrix[i][i]) {
                Matrix[i][i] = Matrix[i][j];
                Matrix[i][j] = rand() % (Matrix[i][i] - 1);
            }
        }
    }
    for (int i = 0; i < 1; i++) {
        for (int j = 0;j < 3;j++) {
            SLAU[i][j] = rand() % 25;
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0;j < 3;j++) {
            std::cout << Matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0;j < 1;j++) {
            std::cout << SLAU[i][j] << " ";
        }
        std::cout << std::endl;
    }

    KramerMethod(Matrix,SLAU);
    ItterMethod(Matrix, SLAU);
    
}