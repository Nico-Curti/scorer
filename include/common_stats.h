#ifndef __common_stats_h__
#define __common_stats_h__

#include <memory>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>

/// @cond DEF
constexpr float inf = std :: numeric_limits < float > :: infinity();
/// @endcond

/**
* @brief Get the array of classes.
*
* @param lbl_true array of true labels as integers
* @param lbl_pred array of predicted labels as integers
* @param n_true size of lbl_true array
* @param n_pred size of lbl_pred array
*
* @return Vector of classes found
*/
struct // Classes
{
  auto operator() (const int * lbl_true, const int * lbl_pred, const int & n_true, const int & n_pred)
  {
    assert (n_pred == n_true);

    std :: set < int > u1 (lbl_true, lbl_true + n_true);
    std :: set < int > u2 (lbl_pred, lbl_pred + n_pred);

    std :: vector < float > classes (u1.size() + u2.size());
    auto it = std :: set_union(u1.begin(), u1.end(), u2.begin(), u2.end(), classes.begin());
    classes.resize(it - classes.begin());

    return classes;
  }
} get_classes;


/**
* @brief Get the confusion matrix of the labels
*
* @details A confusion matrix, also known as an error matrix, is a specific table layout that allows visualization of the performance of an algorithm.
*
* @param lbl_true array of true labels as integers
* @param lbl_pred array of predicted labels as integers
* @param n_lbl size of label arrays
* @param classes array of classes
* @param Nclass size of classes array (aka number of classes)
*
* @return The confusion matrix as ravel array
*/
struct // Confusion Matrix
{
  auto operator() (const int * lbl_true, const int * lbl_pred, const int & n_lbl, const float * classes, const int & Nclass)
  {
    std :: unique_ptr < float[] > confusion_matrix (new float[Nclass * Nclass]);

    std :: fill_n(confusion_matrix.get(), Nclass * Nclass, 0.f);

    auto start = classes,
         end   = classes + Nclass;

    int i1 = 0;
    int i2 = 0;
    for (int i = 0; i < n_lbl; ++i)
    {
      i1 = std :: distance(start, std :: find(start, end, lbl_true[i]));
      i2 = std :: distance(start, std :: find(start, end, lbl_pred[i]));
      ++ confusion_matrix[i1 * Nclass + i2];
    }
    return confusion_matrix;
  }
} get_confusion_matrix;

/**
* @brief Get the True positive score
*
* @details A true positive test result is one that detects the condition when the condition is present (correctly identified).
*
* @param confusion_matrix the confusion matrix of the labels
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of True positive scores (lenght := Nclass)
*/
struct // TP(True positive/hit)
{
  auto operator() (const float * confusion_matrix, const int & Nclass)
  {
    std :: unique_ptr < float[] > TP (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      TP[i] = confusion_matrix[i * Nclass + i];
    return TP;
  }
} get_TP;

/**
* @brief Get the False negative score
*
* @details A false negative test result is one that does not detect the condition when the condition is present (incorrectly rejected).
*
* @param confusion_matrix the confusion matrix of the labels
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of False negative scores (lenght := Nclass)
*/
struct // FN(False negative/miss/type 2 error)
{
  auto operator() (const float * confusion_matrix, const int & Nclass)
  {
    std :: unique_ptr < float[] > FN (new float[Nclass]);
    int N;
    for (int i = 0; i < Nclass; ++i)
    {
      N = i * Nclass;
      FN[i] = std :: accumulate(confusion_matrix + N, confusion_matrix + N + i, 0.f) +
              std :: accumulate(confusion_matrix + N + i + 1, confusion_matrix + N + Nclass, 0.f);
    }
    return FN;
  }
} get_FN;

/**
* @brief Get the False positive score
*
* @details A false positive test result is one that detects the condition when the condition is absent (incorrectly identified).
*
* @param confusion_matrix the confusion matrix of the labels
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of False positive scores (lenght := Nclass)
*/
struct // FP(False positive/type 1 error/false alarm)
{
  auto operator() (const float * confusion_matrix, const int & Nclass)
  {
    std :: unique_ptr < float[] > FP (new float[Nclass]);
    std :: fill_n(FP.get(), Nclass, 0.f);
    for (int i = 0; i < Nclass; ++i)
      for (int j = 0; j < Nclass; ++j)
        FP[j] += (i != j) ? confusion_matrix[i * Nclass + j] : 0.f;

    return FP;
  }
} get_FP;

/**
* @brief Get the True negative score
*
* @details A true negative test result is one that does not detect the condition when the condition is absent (correctly rejected).
*
* @param confusion_matrix the confusion matrix of the labels
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of True negative scores (lenght := Nclass)
*/
struct // TN(True negative/correct rejection)
{
  auto operator() (const float * confusion_matrix, const int & Nclass)
  {
    std :: unique_ptr < float[] > TN (new float[Nclass]);
    switch (Nclass)
    {
      case 1:
      {
        std :: cerr << "WARNING! Nclass must be greater than 1" << std :: endl;
      } break;
      case 2:
      {
        TN[0] = confusion_matrix[3];
        TN[1] = confusion_matrix[0];
      } break;
      case 3:
      {
        TN[0] = confusion_matrix[4] + confusion_matrix[5] + confusion_matrix[7] + confusion_matrix[8];
        TN[1] = confusion_matrix[0] + confusion_matrix[2] + confusion_matrix[6] + confusion_matrix[8];
        TN[2] = confusion_matrix[0] + confusion_matrix[1] + confusion_matrix[3] + confusion_matrix[4];
      } break;
      default:
      {
        std :: fill_n(TN.get(), Nclass, 0.f);

        for (int i = 0; i < Nclass; ++i)
          for (int j = 0; j < Nclass; ++j)
            if (i != j)
              TN[j] += std :: accumulate(confusion_matrix + i * Nclass, confusion_matrix + i * Nclass + Nclass, 0.f) - confusion_matrix[i * Nclass + j];

        std :: cerr << "WARNING! Nclass greater than 3 is not supported yet!" << std :: endl;
      } break;
    }
    return TN;
  }
} get_TN;

/**
* @brief Get the Total sample size.
*
* ```python
* POP = TP + TN + FN + FP
* ```
*
* @param TP array of true positives
* @param TN array of true negatives
* @param FP array of false positives
* @param FN array of false negative
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of total samples for each class.
*/
struct // POP(Population)
{
  auto operator() (const float * TP, const float * TN, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > POP (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      POP[i] = TP[i] + TN[i] + FP[i] + FN[i];
    return POP;
  }
} get_POP;

/**
* @brief Number of positive samples.
*
* @details Also known as support (the number of occurrences of each class in y_true).
*
* ```python
* P = TP + FN
* ```
*
* @param TP array of true positives
* @param FN array of false negative
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the number of positive samples for each class.
*/
struct // P(Condition positive or support)
{
  auto operator() (const float * TP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > P (new float[Nclass]);
    std :: transform(TP, TP + Nclass, FN, P.get(), [](const float & tp, const float & fn){return tp + fn;});
    return P;
  }
} get_P;

/**
* @brief Number of negative samples
*
* ```python
* N = TN + FP
* ```
*
* @param TN array of true negatives
* @param FP array of false positives
* @param Nclass size of classes array (aka number of classes)
*
* @return The array of the number of negative samples for each class
*/
struct // N(Condition negative)
{
  auto operator() (const float * TN, const float * FP, const int & Nclass)
  {
    std :: unique_ptr < float[] > N (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i) N[i] = TN[i] + FP[i];
    std :: transform(TN, TN + Nclass, FP, N.get(), [](const float & tn, const float & fp){return tn + fp;});
    return N;
  }
} get_N;

#endif // __common_stats_h__

