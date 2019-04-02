
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

class Opt {
public:

    Opt(){;}

    double a;
    double b;
    double c;
    double d;
    double rightBorder;
    double leftBorder;
    int n;
    double E;
    double r;

    double m;

    double minFun;
    double minX;

    double* arrayFun;
    double* arrayDensity;

    std::vector<double> vectorX;
    double* arrayX;

    double GetFun(double myX){
        return a*sin(b*myX)+c*cos(d*myX);
    }

    int GetMinId(double* myArray, double size){
        int tmpId = 0;
        double min = 0;
        for(int i = 0; i < size; i++){
            if(arrayFun[i] < min){
                min = arrayFun[i];
                tmpId = i;
            }
        }
        return  tmpId;
    }


    void SetDensity(double minVal,  int size){
        arrayDensity = new double[size];
        for(int i = 0; i < size; i++){
            arrayDensity[i] = minVal-1;
        }


    }

    void SetXBruFor(){

        arrayX = new double[n];
        vectorX.clear();

        double maxRange = 0;
        double tmp = 0;

       vectorX.push_back(leftBorder);
       vectorX.push_back(rightBorder);
       vectorX.push_back((leftBorder+rightBorder)/2);

       std::sort(vectorX.begin(), vectorX.end());


        for(int i = 3; i < n; i++){
            maxRange = 0;
            for(int j = 1; j < vectorX.size(); j++){
                if((vectorX[j]-vectorX[j-1])>maxRange){
                   maxRange = vectorX[j]-vectorX[j-1];
                   tmp = (vectorX[j]+vectorX[j-1])/2;
                }
            }

            vectorX.push_back(tmp);
            std::sort(vectorX.begin(), vectorX.end());

        }

        for(int i = 0; i < n; i++){
            arrayX[i] = vectorX[i];
        }


    }

    void BruteForce(){

        arrayFun = new double[n];

        SetXBruFor();

        for(int i = 0; i < n; i++){
           arrayFun[i] = GetFun(arrayX[i]);
        }

        int tmpId = GetMinId(arrayFun, n);
        minFun = arrayFun[tmpId];
        minX = arrayX[tmpId];

        SetDensity(minFun, n);


    }

    void SetXLe(){

        arrayX = new double[n];

        vectorX.clear();
        double maxR;
        double R = 0;
        double tmp;
        double M = 0;
        double maxM = 0;

       vectorX.push_back(leftBorder);
       vectorX.push_back(rightBorder);
       vectorX.push_back(0.5*(rightBorder+leftBorder) + (GetFun(rightBorder)-GetFun(leftBorder))/(2.0*m));

       std::sort(vectorX.begin(), vectorX.end());


        for(int i = 3; i < n; i++){
            R = 0;
            maxR = 0;
           // maxM = 0;
           // M = 0;

            /*
            for(int p = 1; p < vectorX.size(); p++){


                M = abs((GetFun(vectorX[p])+GetFun(vectorX[p-1]))/(vectorX[p]-vectorX[p-1]));
                if(M >= maxM){
                    maxM = M;
                }
            }

            if(maxM == 0){
                m = 1;
            }

            if(maxM > 0){
                m = maxM*2;
            }

            */

            for(int j = 1; j < vectorX.size(); j++){

                R = 0.5*m*(vectorX[j]-vectorX[j-1]) - 0.5*(GetFun(vectorX[j])+GetFun(vectorX[j-1]));
                if( R >= maxR){
                   maxR = R;
                   tmp = 0.5*(vectorX[j]+vectorX[j-1]) + 0.5*(GetFun(vectorX[j])-GetFun(vectorX[j-1]))/(m);
                }
            }

            vectorX.push_back(tmp);
            std::sort(vectorX.begin(), vectorX.end());

    }

        for(int i = 0; i < n; i++){
            arrayX[i] = vectorX[i];
        }



}

    void SetXLeE(){

        //arrayX = new double[n];

        vectorX.clear();
        double maxR;
        double R = 0;
        double tmp;
        double M = 0;
        double maxM = 0;
        double tmpLast = 0;

       vectorX.push_back(leftBorder);
       vectorX.push_back(rightBorder);
       vectorX.push_back(0.5*(rightBorder+leftBorder) + (GetFun(rightBorder)-GetFun(leftBorder))/(2.0*m));

       std::sort(vectorX.begin(), vectorX.end());

       tmpLast = vectorX[2];


        for(int i = 3; i < n; i++){
            R = 0;
            maxR = 0;

           // maxM = 0;
           // M = 0;

            /*
            for(int p = 1; p < vectorX.size(); p++){


                M = abs((GetFun(vectorX[p])+GetFun(vectorX[p-1]))/(vectorX[p]-vectorX[p-1]));
                if(M >= maxM){
                    maxM = M;
                }
            }

            if(maxM == 0){
                m = 1;
            }

            if(maxM > 0){
                m = maxM*2;
            }

            */

            for(int j = 1; j < vectorX.size(); j++){

                R = 0.5*m*(vectorX[j]-vectorX[j-1]) - 0.5*(GetFun(vectorX[j])+GetFun(vectorX[j-1]));
                if( R >= maxR){
                   maxR = R;
                   tmp = 0.5*(vectorX[j]+vectorX[j-1]) + 0.5*(GetFun(vectorX[j])-GetFun(vectorX[j-1]))/(m);
                }
            }

            vectorX.push_back(tmp);

            if(abs(tmp-tmpLast) < E){
                break;
            }

            tmpLast = tmp;

            std::sort(vectorX.begin(), vectorX.end());
    }

        n = vectorX.size();

        arrayX = new double[n];

        for(int i = 0; i < n; i++){
            arrayX[i] = vectorX[i];
        }

}

    void Leech(){
        arrayFun = new double[n];

        SetXLe();

        for(int i = 0; i < n; i++){
           arrayFun[i] = GetFun(arrayX[i]);
        }

        int tmpId = GetMinId(arrayFun, n);
        minFun = arrayFun[tmpId];
        minX = arrayX[tmpId];

        SetDensity(minFun, n);

    }

    void LeechE(){


        SetXLeE();

         arrayFun = new double[n];

        for(int i = 0; i < n; i++){
           arrayFun[i] = GetFun(arrayX[i]);
        }

        int tmpId = GetMinId(arrayFun, n);
        minFun = arrayFun[tmpId];
        minX = arrayX[tmpId];

        SetDensity(minFun, n);

    }

    void SetXStr(){
        arrayX = new double[n];

        vectorX.clear();
        double maxR;
        double R = 0;
        double tmp;
        double M = 0;
        double maxM = 0;

       vectorX.push_back(leftBorder);
       vectorX.push_back(rightBorder);

       maxM = abs((GetFun(rightBorder)-GetFun(leftBorder))/(rightBorder-leftBorder));

   if(maxM == 0){
       m = 1;
   }

   if(maxM > 0){
       m = maxM*r;
   }

       vectorX.push_back(0.5*(rightBorder+leftBorder) + (GetFun(rightBorder)-GetFun(leftBorder))/(2.0*m));

       std::sort(vectorX.begin(), vectorX.end());


        for(int i = 3; i < n; i++){
            R = 0;
            maxR = 0;
            maxM = 0;
            M = 0;


            for(int p = 1; p < vectorX.size(); p++){


                M = abs((GetFun(vectorX[p])-GetFun(vectorX[p-1]))/(vectorX[p]-vectorX[p-1]));
                if(M >= maxM){
                    maxM = M;
                }
            }

            if(maxM == 0){
                m = 1;
            }

            if(maxM > 0){
                m = maxM*r;
            }



            for(int j = 1; j < vectorX.size(); j++){

                R = m*(vectorX[j]-vectorX[j-1]) -
                    2*(GetFun(vectorX[j])+GetFun(vectorX[j-1])) +
                    (GetFun(vectorX[j])-GetFun(vectorX[j-1]))*(GetFun(vectorX[j])-GetFun(vectorX[j-1]))/(m*(vectorX[j]-vectorX[j-1]));
                if( R >= maxR){
                   maxR = R;
                   tmp = 0.5*(vectorX[j]+vectorX[j-1]) + 0.5*(GetFun(vectorX[j])-GetFun(vectorX[j-1]))/(m);
                }
            }

            vectorX.push_back(tmp);
            std::sort(vectorX.begin(), vectorX.end());

    }

        for(int i = 0; i < n; i++){
            arrayX[i] = vectorX[i];
        }

    }

    void Strong(){
        arrayFun = new double[n];

        SetXStr();

        for(int i = 0; i < n; i++){
           arrayFun[i] = GetFun(arrayX[i]);
        }

        int tmpId = GetMinId(arrayFun, n);
        minFun = arrayFun[tmpId];
        minX = arrayX[tmpId];

        SetDensity(minFun, n);


    }

    void SetXStrE(){
       // arrayX = new double[n];

        vectorX.clear();
        double maxR;
        double R = 0;
        double tmp = 0;
        double M = 0;
        double maxM = 0;
        double tmpLast = 0;

       vectorX.push_back(leftBorder);
       vectorX.push_back(rightBorder);


       maxM = abs((GetFun(rightBorder)-GetFun(leftBorder))/(rightBorder-leftBorder));

   if(maxM == 0){
       m = 1;
   }

   if(maxM > 0){
       m = maxM*r;
   }

       vectorX.push_back(0.5*(rightBorder+leftBorder) - (GetFun(rightBorder)-GetFun(leftBorder))/(2.0*m));

       tmpLast = vectorX[2];

       std::sort(vectorX.begin(), vectorX.end());

        for(int i = 3; i < n; i++){
            R = 0;
            maxR = 0;
            maxM = 0;
            M = 0;
            m = 0;

            for(int p = 1; p < vectorX.size(); p++){


                M = abs((GetFun(vectorX[p])-GetFun(vectorX[p-1]))/(vectorX[p]-vectorX[p-1]));
                if(M >= maxM){
                    maxM = M;
                }
            }

            if(maxM == 0){
                m = 1;
            }

            if(maxM > 0){
                m = maxM*r;
            }



            for(int j = 1; j < vectorX.size(); j++){

                R = m*(vectorX[j]-vectorX[j-1]) -
                    2*(GetFun(vectorX[j])+GetFun(vectorX[j-1])) +
                    (GetFun(vectorX[j])-GetFun(vectorX[j-1]))*(GetFun(vectorX[j])-GetFun(vectorX[j-1]))/(m*(vectorX[j]-vectorX[j-1]));
                if( R >= maxR){
                   maxR = R;
                   tmp = 0.5*(vectorX[j]+vectorX[j-1]) - 0.5*(GetFun(vectorX[j])-GetFun(vectorX[j-1]))/m;
                }
            }


            vectorX.push_back(tmp);


            if(abs(tmp-tmpLast) < E){
                break;
            }

            tmpLast = tmp;

            std::sort(vectorX.begin(), vectorX.end());

    }


        n = vectorX.size();

        arrayX = new double[n];

        for(int i = 0; i < n; i++){
            arrayX[i] = vectorX[i];
        }

    }

    void StrongE(){


        SetXStrE();

        arrayFun = new double[n];

        for(int i = 0; i < n; i++){
           arrayFun[i] = GetFun(arrayX[i]);
        }

        int tmpId = GetMinId(arrayFun, n);
        minFun = arrayFun[tmpId];
        minX = arrayX[tmpId];

        SetDensity(minFun, n);


    }



};
// OPT_H
