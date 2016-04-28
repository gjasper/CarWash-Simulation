//Uniforme: S= Minimo + (Maximo - Minimo)*AleatorioEntre0e1
//Triangular: x(é saida da uniforme) -- SE (Min<= X < Moda) = 2(x-Min)/(Max-Min)*(Moda-Min) || SE (X = Moda) = 2/(Max-Min) || SE (Moda< X <= Max) = 2(Max-x)/(Max-Min)*(Moda-Min)
//Normal: S = (1/sqrt(2*pi*desviopadrão^2))*exp(-((x-media)^2)/(2*desviopadrao^2))
//Exponencial S = (1/media)*exp(-x/media)

#include <math.h>
#include <stdlib.h>

double dist_normal (double mu)
{
  double U1, U2, W, mult, sigma = mu*0.1;
  static double X1, X2;
  static int call = 0;

  if (call == 1)
    {
      call = !call;
      return (mu + sigma * (double) X2);
    }

  do
    {
      U1 = -1 + ((double) rand () / RAND_MAX) * 2;
      U2 = -1 + ((double) rand () / RAND_MAX) * 2;
      W = pow (U1, 2) + pow (U2, 2);
    }
  while (W >= 1 || W == 0);

  mult = sqrt ((-2 * log (W)) / W);
  X1 = U1 * mult;
  X2 = U2 * mult;

  call = !call;

  return (mu + sigma * (double) X1);
}


