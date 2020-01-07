#include <array>

#include <scorer.h>

int main ()
{
  const int n_labels = 12;

  std :: array < int, n_labels > y_true = { {2, 0, 2, 2, 0, 1, 1, 2, 2, 0, 1, 2} };
  std :: array < int, n_labels > y_pred = { {0, 0, 2, 1, 0, 2, 1, 0, 2, 0, 2, 2} };

  scorer score;

#ifdef _OPENMP
#pragma omp parallel shared (score)
  {
#endif

    score.compute_score(y_true.data(), y_pred.data(), n_labels, n_labels);

#ifdef _OPENMP
  }
#endif

  score.print();

  return 0;
}
